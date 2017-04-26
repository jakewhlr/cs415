// CS415 Parallel Computing Spring 2017
// PA4 - Matrix Multiplication - Sequential

#include<mpi.h>
#include<cmath>
#include"matrix.cpp"
#include"arguments.cpp"

void shiftUp(int blockSize, int** matrix, int col, int root, int taskid);
void shiftLeft(int blockSize, int** matrix, int row, int root, int taskid);

int size = 5; // -s <int> size of square matrices
int seed = time(NULL); // -e <int> seed for rng
bool collectingData = false; // -c collecting data t/f
int verbosity = 0; // -v level of verbosity
string fileA = "";
string fileB = "";

int main(int argc, char* argv[]){
   using namespace std;

   // MPI boiler plate
   int numtasks, taskid, len;
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   MPI_Get_processor_name(hostname, &len);
   // end MPI boiler plate

   parseArgs(argc, argv); // parse command line arguments
   if(verbosity > 3 && taskid == 0){
      cout << "Size: " << size << endl;
      cout << "Seed: " << seed << endl;
   }

   int** matrixA;
   int** matrixB;
   int** matrixC;

   if(sqrt(numtasks)*sqrt(numtasks) != numtasks){
      if(taskid == 0){
         cerr << "Number of processes must be square." << endl;
      }
      exit(EXIT_FAILURE);
   }
   if(!fileA.empty() && !fileB.empty()){
      int sizeB;
      matrixA = readFile(fileA, &size);
      matrixB = readFile(fileB, &sizeB);
      if(sizeB != size){
         cerr << "Matrix sizes must be the same." << endl, exit(EXIT_FAILURE);
      }
   } else{
      matrixA = generateMatrix(size, seed);
      matrixB = generateMatrix(size, seed+1);
   }

   matrixC = matrix_multiply(matrixA, matrixB, size);

   clock_t start = clock();







   //
   // int blockSize = size / sqrt(numtasks); // size of each block
   // int** sentA = new int*[blockSize]; // matrix A ints to send/recv
   // int** sentB = new int*[blockSize]; // matrix B ints to send/recv
   // for(int i = 0; i < blockSize; i++){ // initialize sentA/B
   //    sentA[i] = new int[blockSize];
   //    sentB[i] = new int[blockSize];
   // }
   // int root = sqrt(numtasks); // root for splitting up matrix
   // if(taskid == 0){ // master node
   //    for(int task = 1; task < numtasks; task++){ // for each other task
   //       for(int x = (task/root)*blockSize; x < (task/root)*blockSize+blockSize; x++){ // for each current col
   //          for(int y = (task%root)*blockSize; y < (task%root)*blockSize + blockSize; y++){ // for each current row
   //             sentA[x%blockSize][y%blockSize] = matrixA[x][y]; // store in its own array
   //             sentB[x%blockSize][y%blockSize] = matrixB[x][y]; // store in its own array
   //          }
   //          MPI_Send(sentA[x%blockSize], blockSize, MPI_INT, task, 0, MPI_COMM_WORLD); // send current col of A
   //          MPI_Send(sentB[x%blockSize], blockSize, MPI_INT, task, 1, MPI_COMM_WORLD); // send current col of B
   //       }
   //    }
   //    for(int x = (taskid / root)*blockSize; x < (taskid/root)*blockSize + blockSize; x++){ // loop for master node
   //       for(int y = (taskid % root)*blockSize; y < (taskid%root)*blockSize + blockSize; y++){
   //          sentA[x%blockSize][y%blockSize] = matrixA[x][y];
   //          sentB[x%blockSize][y%blockSize] = matrixB[x][y];
   //       }
   //    }
   // } else{ // slaves
   //    for(int col = 0; col < blockSize; col++){ // recieve each col
   //       MPI_Recv(sentA[col], blockSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   //       MPI_Recv(sentB[col], blockSize, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   //    }
   // }
   //
   // int** matrixCprev = new int*[size];
   // for(int i = 0; i < size; i++){
   //    matrixCprev[i] = new int[size];
   //    for(int j = 0; j < size; j++){
   //       matrixCprev[i][j] = 0;
   //    }
   // }
   //
   // for(int i = 0; i < size; i++){
   //    matrixCprev = matrix_add(matrixCprev, matrix_multiply(sentA, sentB, blockSize), blockSize);
   //    for(int j = 0; j < size; j++){
   //       shiftUp(blockSize, sentB, j, root, taskid);
   //    }
   // }

   clock_t end = clock();
   MPI_Barrier(MPI_COMM_WORLD);
   double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
   if(taskid == 0){
      if(verbosity > 2){
         cout << "Matrix A: " << endl;
         printMatrix(size, matrixA);
         cout << "Matrix B: " << endl;
         printMatrix(size, matrixB);
      }
      if(verbosity > 1){
         cout << "Matrix C: " << endl;
         printMatrix(size, matrixC);
      }
      if(verbosity > 0)
         cout << "Elapsed Time: " << elapsedTime << " s" << endl;
      if(collectingData){
         cout << elapsedTime;
      }
   }

   for(int i = 0; i < size; i++){
      delete[] matrixA[i];
      delete[] matrixB[i];
      delete[] matrixC[i];
   }
   delete[] matrixA;
   delete[] matrixB;
   delete[] matrixC;

   return 1;
}

// Shifts the specified column in a split matrix up by one
//
//	Input Arguments:
//    int blockSize - the size of each block that the matrix was split into
// 	int** matrix - matrix in which the operation will take place
// 	int col - column that will be shifted up
// 	int root - square root of size of master matrix
//    int taskid - id of task that this function is running as
void shiftUp(int blockSize, int** matrix, int col, int root, int taskid){
   if(taskid == -1){
      int temp = matrix[col][0];
      int i = 0;
      for(i = 0; i < size-1; i++){
         matrix[col][i] = matrix[col][i+1];
      }
      matrix[col][i] = temp;
      return;
   }

   if((col >= (taskid%root)*blockSize) && (col < (taskid%root)*blockSize + blockSize)){ // if col is within task
      int dest = taskid-root;
      if(dest < 0)
         dest += 2*root;
      MPI_Send(&matrix[0][col], 1, MPI_INT, dest, taskid, MPI_COMM_WORLD);
      int i = 0;
      for(i = 0; i < blockSize-1; i++){
         matrix[i][col] = matrix[i+1][col];
      }
      MPI_Recv(&matrix[i][col], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   }
}

// Shifts the specified row in a split matrix left by one
//
//	Input Arguments:
//    int blockSize - the size of each block that the matrix was split into
// 	int** matrix - matrix in which the operation will take place
// 	int row - row that will be shifted left
// 	int root - square root of size of master matrix
//    int taskid - id of task that this function is running as
void shiftLeft(int blockSize, int** matrix, int row, int root, int taskid){
   if(taskid == -1){
      int temp = matrix[0][row];
      int i = 0;
      for(i = 0; i < size-1; i++){
         matrix[i][row] = matrix[i+1][row];
      }
      matrix[i][row] = temp;
      return;
   }

   if((row >= (taskid%root)*blockSize) && (row < (taskid%root)*blockSize + blockSize)){ // if row is within task
      int dest = taskid-1;
      if(taskid%root == 0)
         dest += root;
      MPI_Send(&matrix[row][0], 1, MPI_INT, dest, taskid, MPI_COMM_WORLD);
      int i = 0;
      for(i = 0; i < blockSize-1; i++){
         matrix[row][i] = matrix[row][i+1];
      }
      MPI_Recv(&matrix[row][i], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   }
}
