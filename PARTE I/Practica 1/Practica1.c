#include <stdio.h>
#include <stdlib.h>

#define INCERO  1


void multiplicar(int row, int col, int A[row][col],int B[row][col],int C[row][col]){ 

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			C[i][j]=0;
      		for(int k=0;k<col;k++){
            	C[i][j]=(C[i][j]+(A[i][k]*B[k][j]));
            	printf("%i * %i +",A[i][k],B[k][j]);
        	}
        	printf("= %i\n", C[i][j]);
      	}
  	}
}

void initMatriz(int row, int col, int matrix[row][col],int initCero){ 
     printf("matrix %i X %i:\n",row,col);

     for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
	        matrix[i][j]= rand() % 256;
	        printf("[%i]", matrix[i][j]);
        }
        printf("\n");
     }
}



void imprimirMatriz(int row, int col, int matrix[row][col]){
	printf("--------------------------\n");
	printf("matrix %i X %i:\n",row,col);
	for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("[%i]", matrix[i][j]);
        }
        printf("\n");
     }
}

int main(){

	int arregloN [2] = {2,4};//,8};//,16,32,64};//,128, 256, 512, 1024}

	for(int x = 0; x < 2; x++){
		int N = arregloN[x];
		printf("N: %i\n", N);
		srand(time(NULL));

		int MATRIZA[N][N];
		initMatriz(N,N,MATRIZA,!INCERO);

		int MATRIZB [N][N];
		initMatriz(N,N,MATRIZB,!INCERO);
		
		int MATRIZC[N][N];
		multiplicar(N,N,MATRIZA,MATRIZB,MATRIZC);
		imprimirMatriz(N,N,MATRIZC);

	}
}