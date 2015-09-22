// Using CUDA device to calculate pi
#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>

#define NUM_BLOCK  100  // Number of thread blocks
#define NUM_THREAD 1000  // Number of threads per block
#define nHilos 2
#define N 2


void imprimirMatriz(int row, int col, int **matrix){
	printf("--------------------------\n");
	printf("matrix %i X %i:\n",row,col);
	for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
     }
}

void initMatriz(int row, int col, int **matrix){ 
     
     printf("matrix %i X %i:\n",row,col);

     for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
	        matrix[i][j]= rand() % 256;
	        //printf("%i ", matrix[i][j]);
        }
        //printf("\n");
     }
     printf("MATOK\n");
}


// Kernel that executes on the CUDA device
__global__ void matMul(int **M,int **M1, int **M2, int particiones) {

	int idx = blockIdx.x*blockDim.x+threadIdx.x;  // Sequential thread index across the blocks
    
	//printf("hilo->%i\n",hiloInfo->hil);
	int inicioParte = idx*(particiones);
	int finParte = (idx+1)*(particiones);
	//printf("inicioParte->%i, finParte->%i\n", inicioParte,finParte);
			for (int i = inicioParte; i < finParte; i++)
			{
				for (int j = 0; j < N; j++)
				{
					int res = 0;
					for(int k=0;k<N;k++){
					    res =(res +(M[i][k] * M1[k][j]));
					    //printf("%i * %i +",A[i][k],B[k][j]);
					} 
					M2[i][j] = res;
				}
			}
}

// Main routine that executes on the host
int main(void) {
	dim3 dimGrid(NUM_BLOCK,1,1);  // Grid dimensions
	dim3 dimBlock(NUM_THREAD,1,1);  // Block dimensions
	size_t size = N*N*sizeof(int);  //Tamaño del arreglo

    printf("HOLA\n");
	int **h_MATRIZA;
	int **h_MATRIZB;
	int **h_MATRIZC;


	h_MATRIZA = (int **)malloc(size);  //  Reservar memoria en device
	h_MATRIZB = (int **)malloc(size);
	h_MATRIZC = (int **)malloc(size);


	initMatriz(N,N,h_MATRIZA);
    imprimirMatriz(N,N,h_MATRIZA);
	initMatriz(N,N,h_MATRIZB);
    imprimirMatriz(N,N,h_MATRIZB);

	int **d_MATRIZA;
	int **d_MATRIZB;
	int **d_MATRIZC;

	
	d_MATRIZA = (int **)malloc(size);  //  Reservar memoria en device
	d_MATRIZB = (int **)malloc(size);
	d_MATRIZC = (int **)malloc(size);
	cudaMalloc((void **) &d_MATRIZA, size);  //Reservar memoria en device
	cudaMalloc((void **) &d_MATRIZB, size);
	cudaMalloc((void **) &d_MATRIZC, size);
	// Inicializar en device
	cudaMemset(d_MATRIZA, 0, size);
	cudaMemset(d_MATRIZB, 0, size);
	cudaMemset(d_MATRIZC, 0, size);

	cudaMemcpy(d_MATRIZA, h_MATRIZA, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_MATRIZA, h_MATRIZA, size, cudaMemcpyHostToDevice);
	int particiones = N/nHilos;
	// Calculo pi
	matMul <<<dimGrid, dimBlock>>> (d_MATRIZA, d_MATRIZB, d_MATRIZC,particiones); 
	// Sumar los elementos del arreglo
	cudaMemcpy(h_MATRIZC, d_MATRIZC, size, cudaMemcpyDeviceToHost);


	free(h_MATRIZA);
	free(h_MATRIZB); 
	free(h_MATRIZC); 
	cudaFree(d_MATRIZA);
	cudaFree(d_MATRIZB);
	cudaFree(d_MATRIZC);

	return 0;
}

