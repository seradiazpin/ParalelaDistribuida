// Using CUDA device to calculate pi
#include <stdio.h>
#include <cuda.h>

#define NUM_BLOCK  100  // Number of thread blocks
#define NUM_THREAD 1000  // Number of threads per block
int tid;
float pi = 0;

// Kernel that executes on the CUDA device
__global__ void cal_pi(float *sum) {

	int idx = blockIdx.x*blockDim.x+threadIdx.x;  // Sequential thread index across the blocks
    
    float res1 = (float)4/(4*idx+1);
    float res2 = (float)4/(4*idx+3);
   
    sum[idx] = res1 - res2;
}

// Main routine that executes on the host
int main(void) {
	dim3 dimGrid(NUM_BLOCK,1,1);  // Grid dimensions
	dim3 dimBlock(NUM_THREAD,1,1);  // Block dimensions
	float *h_sum, *d_sum;  // Punteros

	size_t size = NUM_BLOCK*NUM_THREAD*sizeof(float);  //Tamaño del arreglo
	h_sum = (float *)malloc(size);  //  Reservar memoria en device
	cudaMalloc((void **) &d_sum, size);  //Reservar memoria en device
	// Inicializar en device
	cudaMemset(d_sum, 0, size);
	// Calculo pi
	cal_pi <<<dimGrid, dimBlock>>> (d_sum); 
	// Sumar los elementos del arreglo
	cudaMemcpy(h_sum, d_sum, size, cudaMemcpyDeviceToHost);
    for(tid=0; tid<NUM_THREAD*NUM_BLOCK; tid++){
		pi += h_sum[tid];
        //printf("h_sum[%i] = %.10f\n",tid, h_sum[tid]);
    }
	// Print results
	printf("PI = %.6f\n",pi);

	free(h_sum); 
	cudaFree(d_sum);

	return 0;
}