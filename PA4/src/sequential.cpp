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


   int product;
   vector<int>* matrixA = generateMatrix(size, seed);
   vector<int>* matrixB = generateMatrix(size, seed+1);
   vector<int>* matrixC = new vector<int>[size];
   clock_t start = clock();
   for(int Ay = 0; Ay < size; Ay++){
      for(int Bx = 0; Bx < size; Bx++){
         product = 0;
         for(int Ax = 0; Ax < size; Ax++){
            product += matrixA[Ay][Ax]*matrixB[Ax][Bx];
         }
         matrixC[Ay].push_back(product);
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
