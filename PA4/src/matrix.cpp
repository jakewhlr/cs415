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
