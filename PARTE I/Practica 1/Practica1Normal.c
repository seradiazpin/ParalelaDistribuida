#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int N, nHilos;

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

void multiplicar(int row, int col, int **A,int **B,int **C){ 

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			C[i][j]=0;
      		for(int k=0;k<col;k++){
            	C[i][j]=(C[i][j]+(A[i][k]*B[k][j]));
            	//printf("%i * %i +",A[i][k],B[k][j]);
        	}
        	//printf("= %i\n", C[i][j]);
      	}
  	}
}

int main(int argc, char* const argv[]){

	if(argv[1]== NULL){
  		perror("Digite el tamaño de la matriz N");
  		exit(-1);
	}
	
	N = atoi(argv[1]);
	if (N != 2 && N != 4 && N != 8 && N != 16 && N != 32 && N != 64 && N != 128 && N != 256 && N != 512 && N!= 1024)
	{
		perror("El tamaño debe ser un numero de estos [2,4,8,16,32,64,128, 256, 512, 1024]");
  		exit(-1);
	}

	srand(time(NULL));	
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

	multiplicar(N,N,MATRIZA,MATRIZB,MATRIZC);

}


