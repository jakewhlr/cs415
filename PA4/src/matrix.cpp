#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

vector<double>* readFile(string filename, int* size){
   vector<double>* output;
   string buffer;
   double doubleBuffer;
   int bufferCounter = 0;
   ifstream input(filename.c_str());
   getline(input, buffer);
   *size = atoi(buffer.c_str());
   int n = 0;
   int m = 0;
   output = new vector<double>[*size];
   for(n = 0; n < *size; n++){
      for(m = 0; m < *size; m++){
         input >> doubleBuffer;
         output[n].push_back(doubleBuffer);
      }
   }
   return output;
}

void printMatrix(int size, vector<double>* matrix){
   for(int i = 0; i < size; i++){
      for(int j = 0; j < matrix[i].size(); j++){
         cout << matrix[i][j] << " ";
      }
      cout << endl;
   }
}
