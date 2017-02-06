#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "julia.h"
#include <omp.h>
int julia(const double *x, int xres, const double *y, int yres, const double *c, 
	  int flag, int maxIterations, int *iterations)
{
	int threadcount = 8;
	int maxIterationCount = 0, i,j;
  
	double xi, yi, xgap, ygap, savex, savey, radius;
	int count;
	xgap = (x[1] - x[0]) / xres;
	ygap = (y[1] - y[0]) / yres;
// double time;
//   time = omp_get_wtime();
// #pragma omp parallel for num_threads(threadcount) \
//         default(none) shared(xgap, ygap,xres,x,y,yres,flag,iterations,c,maxIterations,maxIterationCount) private(xi,yi,savex,savey,radius,i,j,count)
	for (j = 0; j < yres; j++)
	{
	  //int myrank = omp_get_thread_num();
	  	//printf("myrank = %d\n", myrank);

		//#pragma omp for
		for (i = 0; i < xres; i++)
		{
			/* pixel to coordinates */
			xi = x[0] + i * xgap;
			yi = y[0] + j * ygap;

			/* initial value for the iteration */
			savex = flag*c[0] + (1-flag)*xi;
			savey = flag*c[1] + (1-flag)*yi;

			radius = 0.0;
			count = 0;
			
			while ( radius <= 4.0 && count < maxIterations )
			{
				double savex2 = xi;
				xi = xi * xi - yi * yi + savex;
				yi = 2.0f * savex2 * yi + savey;
				radius = xi * xi + yi * yi;
				count++;
			}
		  
		  if(count > maxIterationCount )
		    maxIterationCount = count;
		  
		  int *p = iterations + j*xres+i;

		  /* If radius <= 4.0, we have hit maxIterations. The point is
		     likely in the set. */
			if (radius <= 4.0)
		    {
				if(count!=maxIterations)
				{
					break;
				}
				//  assert(count==maxIterations);
				*p = 0;
		    }
			/* radius > 4.0. The point tends to infinity. We recognize
			this at iteration number count */
			else
		    {
		      *p = count;
		    }
		}
    }
  // time = omp_get_wtime()-time;
  // printf("time %f\n",time);
  return maxIterationCount;
  
}
