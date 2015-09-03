#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int N, nHilos;


struct hilosInfo{
	int N,fila, columna, hil;
	int **A,**B,**C;
};


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


void filaXcolum (int N,int fil,int col,int **M,int **M1,int **M2){
	int res = 0;
	for(int k=0;k<N;k++){
    	res =(res +(M[fil][k]* M1[k][col]));
    	//printf("%i * %i +",A[i][k],B[k][j]);
	} 
	M2[fil][col] = res;

	//printf("res -> %i\n",res );

}


void *test (void * info) {
	int particiones = N/nHilos;
	struct hilosInfo  *hiloInfo = info;
	//printf("hilo->%i\n",hiloInfo->hil);
	int inicioParte = hiloInfo->hil*(particiones);
	int finParte = (hiloInfo->hil+1)*(particiones);
	int k=0;
	//printf("inicioParte->%i, finParte->%i\n", inicioParte,finParte);
			for (int i = inicioParte; i < finParte; i++)
			{
				for (int j = 0; j < N; j++)
				{
					filaXcolum(N,i,j,hiloInfo->A,hiloInfo->B,hiloInfo->C);
					//printf("DATO:%i\n",dato );
					//printf("res %i %i el [%i]\n",i,j,hiloInfo->C[i][j]);
					k++;
				}
			}
			
			
	
			return NULL;
}


int main(int argc, char* const argv[]){

	if(argv[1]== NULL){
  		perror("Digite el tamaño de la matriz N");
  		exit(-1);
	}
	if(argv[2] == NULL){
		perror("Digite el numero de hilos ");
  		exit(-1);
	}
	N = atoi(argv[1]);
	nHilos = atoi(argv[2]);
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

	srand(time(NULL));

	int hilosErr;
	struct hilosInfo hilosArray[nHilos];
	pthread_t hilos [nHilos];


	
	int *MATRIZA[N];
	    for (int i=0; i<N; i++)
	         MATRIZA[i] = (int *)malloc(N * sizeof(int));

	initMatriz(N,N,MATRIZA);
	//imprimirMatriz(N,N,MATRIZA);

	int *MATRIZB[N];
	    for (int i=0; i<N; i++)
	         MATRIZB[i] = (int *)malloc(N * sizeof(int));
	    
	initMatriz(N,N,MATRIZB);
	//imprimirMatriz(N,N,MATRIZB);

	int *MATRIZC[N];
	    for (int i=0; i<N; i++)
	         MATRIZC[i] = (int *)malloc(N * sizeof(int));
	    
	printf("nhilos %i\n",nHilos );
	clock_t begin, end;
	double time_spent;
	begin = clock();

	for (int i = 0; i < nHilos; i++)
	{
		hilosArray[i].fila = N;
		hilosArray[i].columna = N;
		hilosArray[i].A = MATRIZA;
		hilosArray[i].B = MATRIZB;
		hilosArray[i].C = MATRIZC;
		hilosArray[i].hil = i;

		hilosErr= pthread_create(&hilos[i],NULL,test,&hilosArray[i]);
		if(hilosErr!=0){
			perror("ERROR CREAR HILO");
		}
	}
	for (int i = 0; i < nHilos; ++i)
	{
		hilosErr = pthread_join(hilos[i],NULL);
		if(hilosErr!=0){
			perror("ERROR CERRAR HILO");
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("---------------\n");
	printf("Elapsed time: %.2lf seconds.\n", time_spent);
	//imprimirMatriz(N,N,MATRIZC);
}


/*
1 0 1 0
1 0 1 0
1 0 1 0
1 0 1 0
*/

