#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

void multiplicar(int row, int col, int A[row][col],int B[row][col],int C[row][col]){ 

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

void initMatriz(int row, int col, int matrix[row][col]){ 
     
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


int filaXcolum (int N,int fil,int col,int M[N][N], int M1[N][N]){
	int res = 0;
	for(int k=0;k<N;k++){
    	res =(res +(M[fil][k]* M1[k][col]));
    	//printf("%i * %i +",A[i][k],B[k][j]);
	} 

	//cprintf("res -> %i\n",res );
	return res;
}

int main(){

	int arregloN [9] = {2,4,8,16,32,64,128, 256, 512};

	int pipefd[2],r;
	pid_t pid;
	float dato;
	time_t inicio,fin;
	double timediff;

	for(int x = 0; x < 9; x++){
		int N = arregloN[x];
		printf("N: %i\n", N);
		srand(time(NULL));

		int MATRIZA[N][N];
		initMatriz(N,N,MATRIZA);
		printf("size: %lu\n",sizeof(int) );
		printf("size: %lu\n",sizeof(MATRIZA) );

		int MATRIZB [N][N];
		initMatriz(N,N,MATRIZB);

		int MATRIZC[N][N];
		int MATRIZD[N][N];

		//printf("res 1X1 => %i\n", filaXcolum(N,1,1,MATRIZA,MATRIZB)); 
		time(&inicio);
		int dato[(N*N)/2];
		r = pipe(pipefd);
		if(r == -1){
			perror("ERROR");	
		}
		pid = fork();
		if(pid == -1){
			perror("ERROR");
		}
		if(pid == 0){
			close(pipefd[0]); // Close the write end
			int k=0;
			for (int i = N/2; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					dato[k] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
					//printf("DATO:%i\n",dato );
					k++;
				}
			}
			write(pipefd[1],&dato,sizeof(int[(N*N)/2]));
			close(pipefd[1]);
			exit(0); 
		}else{
			for (int i = 0; i < N/2; i++)
			{
				for (int j = 0; j < N; j++)
				{
					MATRIZC[i][j] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
				}
			}
			close(pipefd[1]); // Close the write end
			read(pipefd[0],&dato,sizeof(int [(N*N)/2]));
			int k = 0;
			for (int i = N/2; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					MATRIZC[i][j] = dato[k];
					k++;
				}
			}
			
			close(pipefd[0]);

		}
		time(&fin);
		timediff = difftime(fin,inicio);
		printf("CON PROCESOS\n");
		//imprimirMatriz(N,N,MATRIZC);
		printf("---------------\n");
		printf("tiempo %f\n",timediff);

		printf("NORMAL\n");
		time(&inicio);
		multiplicar(N,N,MATRIZA,MATRIZB,MATRIZD);
		time(&fin);
		//imprimirMatriz(N,N,MATRIZD);
		printf("---------------\n");
		timediff = difftime(fin,inicio);
		printf("tiempo %f\n",timediff);

	}

	exit(0);
}


/*
1 0 1 0
1 0 1 0
1 0 1 0
1 0 1 0
*/

