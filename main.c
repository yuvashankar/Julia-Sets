#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "julia.h"

// #ifdef _OPENACC
// #include <openacc.h>
// #endif

int main(int argc, char *argv[])
{
  int width, height, maxiter, flag;
  double x[2], y[2], c[2];
  char *image, *stats;
	double time;  
  getParams(argv, &flag, c, x, y, &width, &height, &maxiter, &image, &stats);
  	int *iterations = (int*)malloc( sizeof(int) * width * height );
//  FILE *f = fopen(stats, "w");
//if(f == NULL)
//	printf("Error creating file\n");

assert(iterations);

  /* compute set */
// #ifdef _OPENACC
//	struct timeval start, end;
//	gettimeofday(&start, NULL);
// double start  = clock();  	
	int maxCount = julia(x, width, y, height, c, flag, maxiter, iterations);	
// double end = (double)(clock() - start)/CLOCKS_PER_SEC;
//	gettimeofday(&end, NULL);
//	time = end.tv_sec-start.tv_sec+(end.tv_usec - start.tv_usec)*1e-6;
// #endif

// printf("run time = %f\n",end);  

 // printf("max iterations hit: %d /%d\n", maxCount, maxiter);

  /* save our picture for the viewer */
  saveBMP(image, iterations, width, height);
//fclose(f);

  free(iterations);
  return 0;
}




