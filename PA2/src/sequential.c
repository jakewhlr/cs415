// Jake Wheeler
// CS415 Parallel Computing
// PA2 - Mandelbrot Set - Sequential

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<mpi.h>

int cal_pixel(double, double);
void writeImage(int*, int, int, char*);

int main(int argc, char *argv[]){
  int numtasks, taskid, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  MPI_Get_processor_name(hostname, &len);

  switch(taskid){
    case 0:{
      int width = atoi(argv[2]);
      int height = atoi(argv[3]); // width and height arguments
      int* output = malloc(width * height * sizeof(int));
      double prev_real = 0;
      double prev_imag = 0; // complex named prev
      int x = 0;
      int y = 0;
      int count = 0; // loop iterators
      clock_t start = clock();
      while(y < height){
        while(x < width){
          prev_real = (x - width/2.0)*4.0/width;
          prev_imag = (y - height/2.0)*4.0/height;
          output[count] = cal_pixel(prev_real, prev_imag);
          x++;
          count++;
        }
        y++;
        x = 0;
      }
      clock_t end = clock();
      writeImage(output, width, height, argv[1]);
      free(output);
      double elapsedTime = (end - start) / (double)CLOCKS_PER_SEC;
      printf("%f", elapsedTime);
    }break;
  }
  return 0;
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
