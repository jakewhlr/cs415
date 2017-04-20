#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

int** generateMatrix(int size, int seed){
   srand(seed); // initialize RNG
   int** output = new int*[size]; // allocate output
   for(int i = 0; i < size; i++)
      output[i] = new int[size];
   for(int n = 0; n < size; n++){
      for(int m = 0; m < size; m++){
         output[n][m] = (random() % 1000); // push random int
      }
   }
   return output;
}

int** readFile(string filename, int* size){
   int** output;
   string buffer;
   int intBuffer;
   int bufferCounter = 0;
   ifstream input(filename.c_str());
   getline(input, buffer);
   *size = atoi(buffer.c_str());
   int n = 0;
   int m = 0;
   output = new int*[*size];
   for(int i = 0; i < *size; i++)
      output[i] = new int[*size];
   for(n = 0; n < *size; n++){
      for(m = 0; m < *size; m++){
         input >> intBuffer;
         output[n][m] = (intBuffer);
      }
   }
   return output;
}

void printMatrix(int size, int** matrix){
   using namespace std;
   for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
         cout << matrix[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

int** matrix_multiply(int** matrixA, int** matrixB, int size){
   int** matrixC = new int*[size];
   int product = 0;
   for(int i = 0; i < size; i++)
      matrixC[i] = new int[size];
   for(int Ay = 0; Ay < size; Ay++){
      for(int Bx = 0; Bx < size; Bx++){
         product = 0;
         for(int Ax = 0; Ax < size; Ax++){
            product += matrixA[Ay][Ax]*matrixB[Ax][Bx];
         }
         matrixC[Ay][Bx] = product;
      }
   }
   return matrixC;
}

int** matrix_add(int** matrixA, int** matrixB, int size){
   int** matrixC = new int*[size];
   for(int i = 0; i < size; i++){
      matrixC[i] = new int[size];
   }
   for(int x = 0; x < size; x++){
      for(int y = 0; y < size; y++){
         matrixC[x][y] = matrixA[x][y] + matrixB[x][y];
      }
   }
   return matrixC;
}
