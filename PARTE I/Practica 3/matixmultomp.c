#include "omp.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void filaXcolum (int N,int fil,int col,int **M,int **M1,int **M2){
	int res = 0;
	int k = 0;
	for(k=0;k<N;k++){
    	res =(res +(M[fil][k]* M1[k][col]));
    	//printf("%i * %i +",A[i][k],B[k][j]);
	} 
	M2[fil][col] = res;

	//printf("res -> %i\n",res );

}

void initMatriz(int row, int col, int **matrix){ 
     
     printf("matrix %i X %i:\n",row,col);
	int i=0;
	int j=0;
     for(i=0;i<row;i++){
        for(j=0;j<col;j++){
	        matrix[i][j]= rand() % 256;
	        //printf("%i ", matrix[i][j]);
        }
        //printf("\n");
     }
     printf("MATOK\n");
}

void imprimirMatriz(int row, int col, int **matrix){
	printf("--------------------------\n");
	printf("matrix %i X %i:\n",row,col);
	int i=0;
	int j=0;
	for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
     }
}



void  main(int argc, char* const argv[])
{

	if(argv[1]== NULL){
  		perror("Digite el tamaño de la matriz N");
  		exit(-1);
	}
	if(argv[2] == NULL){
		perror("Digite el numero de hilos ");
  		exit(-1);
	}
	int N = atoi(argv[1]);
	int nHilos = atoi(argv[2]);
	printf("N = %i, numero hilos= %i\n", N, nHilos);
	if (N != 2 && N != 4 && N != 8 && N != 16 && N != 32 && N != 64 && N != 128 && N != 256 && N != 512 && N!= 1024)
	{
		perror("El tamaño debe ser un numero de estos [2,4,8,16,32,64,128, 256, 512, 1024]");
  		exit(-1);
	}
	if(nHilos > N){
		perror("Los hilos deven ser menores o iguales a el tamaño");
  		exit(-1);
	}
	int i=0;
	int *MATRIZA[N];
	    for (i=0; i<N; i++)
	         MATRIZA[i] = (int *)malloc(N * sizeof(int));

	initMatriz(N,N,MATRIZA);
	//imprimirMatriz(N,N,MATRIZA);

	int *MATRIZB[N];
	    for (i=0; i<N; i++)
	         MATRIZB[i] = (int *)malloc(N * sizeof(int));
	    
	initMatriz(N,N,MATRIZB);
	//imprimirMatriz(N,N,MATRIZB);

	int *MATRIZC[N];
	    for (i=0; i<N; i++)
	         MATRIZC[i] = (int *)malloc(N * sizeof(int));


	int particiones = N/nHilos;
	#pragma omp parallel num_threads(nHilos)
	{
	   int ID = omp_get_thread_num();
	   
	   int inicioParte = ID*(particiones);
		int finParte = (ID+1)*(particiones);
		int k=0;
		//printf("inicioParte->%i, finParte->%i\n", inicioParte,finParte);
		int i = 0;
		for (i = inicioParte; i < finParte; i++)
		{
			int j = 0;
			for (j = 0; j < N; j++)
			{
				filaXcolum(N,i,j,MATRIZA,MATRIZB,MATRIZC);
				//printf("DATO:%i\n",dato );
				//printf("res %i %i el [%i]\n",i,j,hiloInfo->C[i][j]);
				k++;
			}
		}
	}
	imprimirMatriz(N,N,MATRIZA);
	imprimirMatriz(N,N,MATRIZB);
	imprimirMatriz(N,N,MATRIZC);
	
}

	
