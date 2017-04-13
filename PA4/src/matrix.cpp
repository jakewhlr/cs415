#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

vector<int>* generateMatrix(int size, int seed){
   srand(seed); // initialize RNG
   vector<int>* output = new vector<int>[size]; // allocate output
   for(int n = 0; n < size; n++){
      for(int m = 0; m < size; m++){
         output[n].push_back(random() % 1000); // push random int
      }
   }
   return output;
}

vector<int>* readFile(string filename, int* size){
   vector<int>* output;
   string buffer;
   int intBuffer;
   int bufferCounter = 0;
   ifstream input(filename.c_str());
   getline(input, buffer);
   *size = atoi(buffer.c_str());
   int n = 0;
   int m = 0;
   output = new vector<int>[*size];
   for(n = 0; n < *size; n++){
      for(m = 0; m < *size; m++){
         input >> intBuffer;
         output[n].push_back(intBuffer);
      }
   }
   return output;
}

void printMatrix(int size, vector<int>* matrix){
   using namespace std;
   for(int i = 0; i < size; i++){
      for(int j = 0; j < matrix[i].size(); j++){
         cout << matrix[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
}
