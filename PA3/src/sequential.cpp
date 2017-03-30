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

#define NUM_BUCKETS 8

using namespace std;

int main(int argc, char *argv[]){
// MPI boiler plate
  int numtasks, taskid, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  MPI_Get_processor_name(hostname, &len);
// end MPI boiler plate

  int numInts = 0;
  int bucketCounter = 0;
  int* list;
  int counter = 0;
  ifstream input;
  string line;
  vector<int> buckets[8];
  vector<int> sorted;
  int perBucket = 0;
  int largest = 0;

  // file reading
  input.open(argv[1]);

  if(input.is_open()){
    getline(input, line);
    numInts = atoi(line.c_str());
    list = new int[numInts];
    while(getline(input, line)){
      list[counter] = atoi(line.c_str());
      if(list[counter] > largest){
        largest = list[counter];
      }
      counter++;
    }
  }
  input.close();
  // end file reading

  clock_t start = clock(); // start timer

// bucket placement
  perBucket = largest / NUM_BUCKETS;
  counter = 0;
  while(counter < numInts){
    if(0 < list[counter] && list[counter ] < perBucket){
      // go to bucket one
      buckets[0].push_back(list[counter]);
    }
    else if(perBucket < list[counter] && list[counter] < 2*perBucket){
      // 2nd bucket
      buckets[1].push_back(list[counter]);
    }
    else if(2*perBucket < list[counter] && list[counter] < 3*perBucket){
      // 3rd
      buckets[2].push_back(list[counter]);
    }
    else if(3*perBucket < list[counter] && list[counter] < 4*perBucket){
      // 4th bucket
      buckets[3].push_back(list[counter]);
    }
    else if(4*perBucket < list[counter] && list[counter] < 5*perBucket){
      // 5th bucket
      buckets[4].push_back(list[counter]);
    }
    else if(5*perBucket < list[counter] && list[counter] < 6*perBucket){
      // 6th bucket
      buckets[5].push_back(list[counter]);
    }
    else if(6*perBucket < list[counter] && list[counter] < 7*perBucket){
      // 7th bucket
      buckets[6].push_back(list[counter]);
    }
    else if(7*perBucket < list[counter]){
      // 8th bucket
      buckets[7].push_back(list[counter]);
    }
    counter++;
  }
// end bucket placement

// sorting and reconstructing
  counter = 0;
  while(counter < NUM_BUCKETS){
    sort(buckets[counter].begin(), buckets[counter].end());
    while(bucketCounter < buckets[counter].size()){
      sorted.push_back(buckets[counter][bucketCounter]);
      bucketCounter++;
    }
    bucketCounter = 0;
    counter++;
  }
// end sorting and reconstructing

clock_t end = clock(); // end timer
double elapsedTime = (end - start) / (double)CLOCKS_PER_SEC;
// output
  // counter = 0;
  // cout << "Sorted: [ ";
  // while(counter < sorted.size()){
  //   cout << sorted[counter] << " ";
  //   counter++;
  // }
  // cout << "]" << endl;
// end output

  delete[] list;
  cout << "elapsed time: " << elapsedTime << "s" << endl;
  return 0;
}
