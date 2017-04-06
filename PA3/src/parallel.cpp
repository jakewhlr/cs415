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
   vector<int> random(size); // random generated array
   vector<int> buckets[numtasks]; // buckets
   vector<int> finalBucket; // ending bucket
   int recieved[1000000]; // temp storage for recv
   MPI_Status status;
   int count = 0;
   random = generator(seed, size, &minimum, &maximum);
   int perBucket = (maximum + numtasks - 1)/ numtasks;
   clock_t start, end;
   if(taskid == 0)
      start = clock();
   MPI_Barrier(MPI_COMM_WORLD);
   for(int number = taskid*size/numtasks; number < (taskid + 1)*size/numtasks; number++){ // loop through each % of random numbers
      for(int bucket = 0; bucket < numtasks; bucket++){ // loop through buckets
         if(random[number] < (bucket + 1) * perBucket){ // place in correct bucket
            buckets[bucket].push_back(random[number]);
            break;
         }
      }
   }
   for(int bucket = 0; bucket < numtasks; bucket++){
      if(bucket != taskid){
         MPI_Send(&buckets[bucket], buckets[bucket].size(), MPI_INT, bucket, 15, MPI_COMM_WORLD); // send to correct bucket
      }
      else{
         for(int bucket = 0; bucket < numtasks; bucket++){ // for each bucket
            if(taskid != bucket){ // if not current
               MPI_Probe(MPI_ANY_SOURCE, 15, MPI_COMM_WORLD, &status); // get size
               MPI_Get_count(&status, MPI_INT, &count); // get size
               MPI_Recv(&recieved, count, MPI_INT, MPI_ANY_SOURCE, 15, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // recv numbers
               for(int number = 0; number < count; number++){ // for each number
                  finalBucket.push_back(recieved[number]); // put in final bucket
               }
            }
         }
      }
   }

   sort(finalBucket.begin(), finalBucket.end()); // sort buckets

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

// void master(int numtasks){
//    cout << "Master!" << endl;
//    int perProcess = size / numtasks;
//    for(int index = 1; index < numtasks; index++){
//       MPI_Send(&random[index * perProcess], perProcess, MPI_INT, index, 0, MPI_COMM_WORLD);
//    }
// }

void slave(int numtasks){
   int numBuckets = numtasks;
   int length = size / numtasks;
   int maximum = 0;
   vector<int> buckets[numtasks - 1];
   int recieved[length];
   cout << "Max: " << maximum << endl;
   int perBucket = (maximum + numBuckets - 1)/ numBuckets;
   MPI_Recv(&recieved, length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   for(int number = 0; number < length; number++){
      for(int bucket = 0; bucket < numBuckets; bucket++){
         if(recieved[number] < (bucket + 1) * perBucket){
            cout << "Pushing " << recieved[number] << "Onto bucket " << bucket << endl;
            buckets[bucket].push_back(recieved[number]);
            break;
         }
      }
   }
   outputBuckets(buckets, numBuckets);
}
