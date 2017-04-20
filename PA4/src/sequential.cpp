// Jake Wheeler
// CS415 Parallel Computing Spring 2017
// PA4 - Matrix Multiplication - Sequential

#include<mpi.h>
#include<vector>
#include<ctime>
#include"matrix.cpp"
#include"arguments.cpp"

int size = 5; // -s <int> size of square matrices
int seed = time(NULL); // -e <int> seed for rng
bool collectingData = false; // -c collecting data t/f
int verbosity = 0; // -v level of verbosity
string fileA = "";
string fileB = "";

int main(int argc, char* argv[]){
   using namespace std;
   parseArgs(argc, argv); // parse command line arguments
   if(verbosity > 3){
      cout << "Size: " << size << endl;
      cout << "Seed: " << seed << endl;
   }

   // MPI boiler plate
   int numtasks, taskid, len;
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   MPI_Get_processor_name(hostname, &len);
   // end MPI boiler plate

   int** matrixA;
   int** matrixB;
   int** matrixC;

   if(!fileA.empty() && !fileB.empty()){
      int sizeB;
      matrixA = readFile(fileA, &size);
      matrixB = readFile(fileB, &sizeB);
      if(sizeB != size)
         cerr << "Matrix sizes must be the same." << endl, exit(EXIT_FAILURE);
   } else{
      matrixA = generateMatrix(size, seed);
      matrixB = generateMatrix(size, seed+1);
   }
   matrixC = new int*[size];
   for(int i = 0; i < size; i++)
      matrixC[i] = new int[size];

   int product;
   clock_t start = clock();
   for(int Ay = 0; Ay < size; Ay++){
      for(int Bx = 0; Bx < size; Bx++){
         product = 0;
         for(int Ax = 0; Ax < size; Ax++){
            product += matrixA[Ay][Ax]*matrixB[Ax][Bx];
         }
         matrixC[Ay][Bx] = product;
      }
   }
   clock_t end = clock();
   double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
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
   if(collectingData)
      cout << elapsedTime;
}
