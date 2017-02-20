#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
  int maxSamples = atoi(argv[1]);
  int maxCount = atoi(argv[2]);
  int numtasks, taskid, len;
  int tag, dest, src, currentCount, currentSample;
  int data[maxCount];
  double startTime, endTime, deltaT, totalTime, averageTime;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  MPI_Get_processor_name(hostname, &len);
  switch(taskid){
    case 0:
      for(currentCount = 1; currentCount < maxCount + 1; currentCount++){
        totalTime = averageTime = 0;
        for(currentSample = 0; currentSample < maxSamples; currentSample++){ // number of maxSamples per # of ints
          startTime = MPI_Wtime();
          MPI_Send(&data, currentCount, MPI_INT, 1, 1, MPI_COMM_WORLD);
          MPI_Recv(&data, currentCount, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          endTime = MPI_Wtime();
          deltaT = endTime - startTime;
          totalTime += deltaT;
        }
        averageTime = totalTime / maxSamples;
        printf("%f\n", averageTime);
      }
      printf("Samples: %d, Integers: %d\n", maxSamples, maxCount);
    break;
    case 1:
      for(currentCount = 1; currentCount < maxCount + 1; currentCount++){
        for(currentSample = 0; currentSample < maxSamples; currentSample++){ // number of maxSamples per # of ints
          MPI_Recv(&data, currentCount, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Send(&data, currentCount, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }
      }
    break;
    default:
      printf("Unused task, ID: %d Host: %s\n", taskid, hostname);
    break;
  }
  MPI_Finalize();
}
