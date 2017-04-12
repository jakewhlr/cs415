// Jake Wheeler
// CS415 Parallel Computing Spring 2017
// PA4 - Matrix Multiplication - Sequential

#include<mpi.h>
#include<vector>
#include"matrix.cpp"

using namespace std;

int main(int argc, char* argv[]){
   int sizeA, sizeB, sizeC;
   double product;
   vector<double>* matrixA = readFile(argv[1], &sizeA);
   vector<double>* matrixB = readFile(argv[2], &sizeB);
   if(sizeA != sizeB){
      cerr << "Square matrices must be of same size." << endl;
      return 1;
   }
   sizeC = sizeA;
   vector<double>* matrixC = new vector<double>[sizeC];
   for(int Ay = 0; Ay < sizeA; Ay++){
      for(int Bx = 0; Bx < sizeB; Bx++){
         product = 0;
         for(int Ax = 0; Ax < sizeA; Ax++){
            product += matrixA[Ay][Ax]*matrixB[Ax][Bx];
         }
         matrixC[Ay].push_back(product);
      }
   }

   printMatrix(sizeA, matrixA);
   cout << endl;
   printMatrix(sizeB, matrixB);
   cout << endl;
   printMatrix(sizeC, matrixC);
}
