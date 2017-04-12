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
   sizeC = sizeA;
   vector<double>* matrixC = new vector<double>[sizeC];
   for(int Cx = 0; Cx < sizeC; Cx++){
      for(int Cy = 0; Cy < sizeC; Cy++){
         product = 0;
         for(int Ax = 0; Ax < sizeA; Ax++){
            product += matrixA[Cy][Ax]*matrixB[Ax][Cy];
         }

         matrixC[Cx].push_back(product);
      }
   }

   printMatrix(sizeA, matrixA);
   cout << endl;
   printMatrix(sizeB, matrixB);
   cout << endl;
   printMatrix(sizeC, matrixC);
}
