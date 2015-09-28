#include <stdio.h>
#include<time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void matrixMultGPU(int *a, int *b, int *c, int N, int particiones ) {
 int col = threadIdx.x + blockDim.x * blockIdx.x;

 int inicioParte = col*(particiones);
 int finParte = (col+1)*(particiones);

			for (int i = inicioParte; i < finParte; i++)
			{	
				for (int j = 0; j < N; j++)
				{
					int res = 0;
					for(int k=0;k<N;k++){
					    res =(res + a[i* N + k] * b[k * N + j]);
					    //printf("%i * %i +",A[i][k],B[k][j]);
					} 
					c[ i* N + j] = res;
				}
				
			}
  
 
}


int main(int argc, char* const argv[]) {

	if(argv[1]== NULL){
  		perror("Digite el tamaño de la matriz N");
  		exit(-1);
	}
	if(argv[2] == NULL){
		perror("Digite el numero de hilos ");
  		exit(-1);
	}
	if(argv[3] == NULL){
		perror("Digite el numero de Bloques ");
  		exit(-1);
	}
	int N = atoi(argv[1]);
	int nHilos = atoi(argv[2]);
	int bloq = atoi(argv[3]);
	printf("N = %i, numero hilos= %i\n", N, nHilos);
	if (N != 2 && N != 4 && N != 8 && N != 16 && N != 32 && N != 64 && N != 128 && N != 256 && N != 512 && N!= 1024)
	{
		perror("El tamaño debe ser un numero de estos [2,4,8,16,32,64,128, 256, 512, 1024]");
  		exit(-1);
	}
	if(nHilos > N){
		perror("Los hilos deben ser menores o iguales a el tamaño");
  		exit(-1);
	}
	if(bloq != 1 && bloq !=2 && bloq != 4 && bloq != 8 && bloq*nHilos > N){
		perror("Los bloques deben ser 1 2 4 8");
  		exit(-1);
	}
    
 int block = bloq ;
 int thread = nHilos;
 
    
 int *a = (int *)malloc(N*N*sizeof(int));

 int *b= (int *)malloc(N*N*sizeof(int));
	    
 int *c= (int *)malloc(N*N*sizeof(int));
    
 int *dev_a, *dev_b, *dev_c;
 int i,j;

  /* inicializando variables con datos*/
    
	for (i = 0; i<N; i++){
		for (j = 0; j<N; j++){
			a[(N*i)+j] = rand() & 0xf;
          
			b[(N*i)+j] = rand() & 0Xf;
		}
	}
    
  
  int size = N * N * sizeof(int);

 cudaMalloc((void **) &dev_a, size);
 cudaMalloc((void **) &dev_b, size);
 cudaMalloc((void **) &dev_c, size);

 cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
 cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);

 dim3 dimGrid(block);
 dim3 dimBlock(thread);

 int particiones = N/thread;
 clock_t start = clock();
 matrixMultGPU<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c,N, particiones);
    

 cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

 clock_t end = clock();
 float ans = (float)(end - start) / CLOCKS_PER_SEC;
 printf("Duracion hilos CUDA Tamaño %d: %.20f \n", N , ans);

 
 cudaFree(dev_a);
 cudaFree(dev_b);
 cudaFree(dev_c);
 

  return 0;

}


