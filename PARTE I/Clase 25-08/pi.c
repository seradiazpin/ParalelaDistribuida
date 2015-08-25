#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int  main()
{
	long ITER = 1000000000;
	float pi = 0;
	for (long i = 0; i < (ITER); i = i+2)
	{	
		float res1 = (float)4/(2*i+1);
		float res2 = (float)4/(2*i+3);
		pi = pi + res1- res2; //pi + (4/((2*i)+1) - 4/((2*i)+3));
	}
	printf("PI = %.10f\n",pi);
}