// Jake Wheeler
// CS415 Parallel Computing
// PA3 - Bucket Sort - Sequential

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<mpi.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstring>

#include"generator.cpp"

using namespace std;

int verbosity = 0;
bool collectingData = false;
int size = 100;
int seed = time(NULL);
int numBuckets = 8;

void outputBuckets(vector<int>*, int);
void parseArgs(int argc, char* argv[]);

int main(int argc, char *argv[]){
   parseArgs(argc, argv);
   if(verbosity > 1){
      cout << "Size: " << size << endl;
      cout << "Seed: " << seed << endl;
      cout << "Number of Buckets: " << numBuckets << endl;
   }
   // MPI boiler plate
   int numtasks, taskid, len;
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   MPI_Get_processor_name(hostname, &len);
   // end MPI boiler plate

   int min, max;
   vector<int> randgen(size);
   randgen = generator(seed, size, &min, &max);
   vector<int> buckets[numBuckets];
   vector<int> sorted;
   int perBucket = (max + numBuckets - 1) / numBuckets;

   if(verbosity > 1)
      cout << "Integers Per Bucket: " << perBucket << endl;

   if(verbosity > 3){
      cout << "Random: [ ";
      for(int number = 0; number < size; number++)
         cout << randgen[number] << " ";
      cout << "]" << endl;
   }

// bucket placement
   for(int number = 0; number < size; number++){ // for each number
      for(int bucket = 0; bucket < numBuckets; bucket++){ // for each bucket
         if(randgen[number] < (bucket + 1) * perBucket){
            buckets[bucket].push_back(randgen[number]);
            break;
         }
      }
   }

   clock_t start = clock(); // start timer
   for(int index = 0; index < numBuckets; index++){
      sort(buckets[index].begin(), buckets[index].end());
   }
   clock_t end = clock();
   double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

   if(collectingData)
      cout << elapsedTime;

   if(verbosity > 0)
      cout << "Elapsed Time: " << elapsedTime << " s" << endl;

   if(verbosity > 2)
      outputBuckets(buckets, numBuckets);

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
                     case 'b':
                        if(opt < length)
                           if(index + 1 < argc)
                              index++, numBuckets = atoi(argv[index]);
                           else
                              cerr << "Incorrect format: -b <int>" << endl, exit(EXIT_FAILURE);
                        else
                           cerr << "Incorrect format: -b <int>" << endl, exit(EXIT_FAILURE);
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
