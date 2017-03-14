// Jake Wheeler
// CS415 Parallel Computing
// PA2 - Mandelbrot Set - Dynamic

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<mpi.h>

#define NUM_ROWS 10

int cal_pixel(double, double);
void writeImage(int*, int, int, char*);

int main(int argc, char *argv[]){
  int numtasks, taskid, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  MPI_Get_processor_name(hostname, &len);

  int width = atoi(argv[2]); // width of image
  int height = atoi(argv[3]); // height of image
  int row; // current row

  switch(taskid){
    case 0:{
      int* output = malloc(width * height * sizeof(int));
      int counter = 1;
      row = 0;
      int recieved[2];
      clock_t start = clock();
      while(counter < numtasks){
        MPI_Send(&row, 1, MPI_INT, counter, 0, MPI_COMM_WORLD);
        counter++;
        row += NUM_ROWS;
      }
      int i = 0;
      while(row < height){
        MPI_Recv(&recieved, 2, MPI_INT, MPI_ANY_SOURCE, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&output[height * recieved[1]], NUM_ROWS * width, MPI_INT, recieved[0], recieved[0], MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&row, 1, MPI_INT, recieved[0], recieved[0], MPI_COMM_WORLD);
        row += NUM_ROWS;
      }
      clock_t end = clock();
      writeImage(output, width, height, argv[1]);
      double elapsedTime = (end - start) / (double)CLOCKS_PER_SEC;
      printf("%f", elapsedTime);
    }break;
    case !0:
      MPI_Recv(&row, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int response[2], x, y;
      int count;
      double prev_real, prev_imag;
      int output[width * NUM_ROWS];
      while(row + NUM_ROWS < height){
        response[0] = taskid;
        response[1] = row;
        count = 0;
        for(y = row; y < row + NUM_ROWS && y < height; y++){
          for(x = 0; x < width; x++){
            prev_real = (x - width/2.0)*4.0/width;
            prev_imag = (y - height/2.0)*4.0/height;
            output[count] = cal_pixel(prev_real, prev_imag);
            count++;
          }
        }
        MPI_Send(&response, 2, MPI_INT, 0, 50, MPI_COMM_WORLD);
        MPI_Send(&output, NUM_ROWS*width, MPI_INT, 0, taskid, MPI_COMM_WORLD);
        MPI_Recv(&row, 1, MPI_INT, 0, taskid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
  }
  MPI_Finalize();
}


// Function calculates a single pixel with the Mandelbrot equation given a
// previous z
int cal_pixel(double c_real, double  c_imag){
  int count, max;
  double z_real = 0;
  double z_imag = 0;
  float temp, lengthsq;
  max = 256;
  count = 0;
  do{
    temp = z_real * z_real - z_imag * z_imag + c_real;
    z_imag = 2 * z_real * z_imag + c_imag;
    z_real = temp;
    lengthsq = z_real * z_real + z_imag * z_imag;
    count++;
  } while ((lengthsq < 4.0) && (count < max));
  return count;
}

// Function writes an array of unsigned chars to a .ppm file for visuializing
// Mandelbrot set
void writeImage(int* pixels, int width, int height, char* outFile){
	int x, y;
	FILE* fp = fopen(outFile, "wb");
	fprintf(fp, "P5\n# \n%d %d\n255\n", width, height);
	for(y = 0; y < height; y++){
	   for(x = 0; x < width; x++){
	      fprintf(fp, "%c", (unsigned char) pixels[y * width + x]);
	   }
	}
	fclose(fp);
}
