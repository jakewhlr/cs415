// Jake Wheeler
// CS415 Parallel Computing
// PA3 - Bucket Sort - Parallel

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

#include"generator.cpp"

using namespace std;

int verbosity = 0;
bool collectingData = false;
int size = 100;
int seed = time(NULL);

void outputBuckets(vector<int>*, int);
void parseArgs(int argc, char* argv[]);
void master(int numtasks);
void slave(int numtasks);

int main(int argc, char *argv[]){
   parseArgs(argc, argv);

   int numtasks, taskid, len;
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   MPI_Get_processor_name(hostname, &len);

   int minimum, maximum; // min, max for bucket sort
   vector<int> randgen(size); // randgen generated array
   vector<int> buckets[numtasks]; // buckets
   int count = 0;
   randgen = generator(seed, size/numtasks, &minimum, &maximum);
   int perBucket = (maximum + numtasks - 1)/ numtasks;
   clock_t start, end;
   if(taskid == 0)
      start = clock();
   MPI_Barrier(MPI_COMM_WORLD);
   for(int number = 0; number < (taskid + 1)*size/numtasks; number++){ // loop through each % of randgen numbers
      for(int bucket = 0; bucket < numtasks; bucket++){ // loop through buckets
         if(randgen[number] < (bucket + 1) * perBucket){ // place in correct bucket
            buckets[bucket].push_back(randgen[number]);
            break;
         }
      }
   }
   sort(buckets[taskid].begin(), buckets[taskid].end());// sort correct bucket
   MPI_Barrier(MPI_COMM_WORLD); // wait
   if(taskid == 0){
      end = clock();
      double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
      cout << elapsedTime;
   }
   return 0;
}

void outputBuckets(vector<int>* buckets, int size){
   for(int i = 0; i < size; i++){
      cout << "Bucket " << i << ": [ ";
      if(buckets[i].size() != 0)
         for(int j = 0; j < buckets[i].size(); j++)
            cout << buckets[i][j] << " ";
      cout << "]" << endl;
   }
}

void parseArgs(int argc, char* argv[]){
   int length = 0;
   for(int index = 1; index < argc; index++){
      length = strlen(argv[index]); // get length of argument
      if(argv[index][0] == '-'){ // if option
         if(length >= 2){
            if(argv[index][1] == '-'){ // if long option
               // long opts
            } else{ // short option
               for(int opt = 1; opt < length; opt++){
                  switch(argv[index][opt]){
                     case 'v':
                        if(verbosity < 4)
                           verbosity++;
                     break;
                     case 'c':
                        collectingData = true;
                     break;
                     case 's':
                        if(opt < length) // if s is not last opt
                           if(index + 1 < argc)
                              index++, size = atoi(argv[index]);
                           else
                              cerr << "Incorrect format: -s <int>" << endl, exit(EXIT_FAILURE);
                        else
                           cerr << "Inorrect format: -s <int>" << endl, exit(EXIT_FAILURE);
                     break;
                     case 'e':
                        if(opt < length)
                           if(index + 1 < argc)
                              index++, seed = atoi(argv[index]);
                           else
                              cerr << "Incorrect format: -e <int>" << endl, exit(EXIT_FAILURE);
                        else
                           cerr << "Incorrect format: -e <int>" << endl, exit(EXIT_FAILURE);
                     break;
                  }
               }
            }
         }
      }
   }
   if(collectingData)
      verbosity = 0;
}
