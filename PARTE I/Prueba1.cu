#include <stdio.h>
#include<time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void matrixMultGPU(int *a, int *b, int *c, int N) {
 int k, sum = 0;
 int col = threadIdx.x + blockDim.x * blockIdx.x;
 int fil = threadIdx.y + blockDim.y * blockIdx.y;

  if (col < N && fil < N) {
  for (k = 0; k < N; k++) {
   sum += a[fil * N + k] * b[k * N + col];
  }
  c[fil * N + col] = sum;
 }
}


int main() {
    
 const int N = 2;
 int block = 1;
 int thread = 2;
    
 int *a = (int *)malloc(N*N*sizeof(int));

 int *b= (int *)malloc(N*N*sizeof(int));
	    
 int *c= (int *)malloc(N*N*sizeof(int));
    
 int *dev_a, *dev_b, *dev_c;
 int i,j;

  /* inicializando variables con datos*/
    printf("LOL\n");
	for (i = 0; i<N; i++){
		for (j = 0; j<N; j++){
			a[(N*i)+j] = rand() & 0xf;
          
			b[(N*i)+j] = rand() & 0Xf;
		}
	}
    
    for(int i = 0;i< N;i++){
        for(int j = 0;j< N;j++){
            printf("%i ",a[(N*i)+j]);
        }
            printf("\n");
    }

  clock_t start = clock();
  int size = N * N * sizeof(int);

 cudaMalloc((void **) &dev_a, size);
 cudaMalloc((void **) &dev_b, size);
 cudaMalloc((void **) &dev_c, size);

 cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
 cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);

 dim3 dimGrid(block);
 dim3 dimBlock(thread);


 matrixMultGPU<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c,N);
    
for (i = 0; i<N; i++){
		for (j = 0; j<N; j++){
			a[(N*i)+j] = 0;
          
		}
	}
 cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

 clock_t end = clock();
 float ans = (float)(end - start) / CLOCKS_PER_SEC;
 printf("Duracion hilos CUDA Tamaño %d: %f \n", N , ans);

    
    for(int i = 0;i< N;i++){
        for(int j = 0;j< N;j++){
            printf("%i ",a[(N*i)+j]);
        }
            printf("\n");
    }
    for(int i = 0;i< N;i++){
        for(int j = 0;j< N;j++){
            printf("%i ",b[(N*i)+j]);
        }
            printf("\n");
    }
    for(int i = 0;i< N;i++){
        for(int j = 0;j< N;j++){
            printf("%i ",c[(N*i)+j]);
        }
            printf("\n");
    }
 cudaFree(dev_a);
 cudaFree(dev_b);
 cudaFree(dev_c);


  return 0;

}

