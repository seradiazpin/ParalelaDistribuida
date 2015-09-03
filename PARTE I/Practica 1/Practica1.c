#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

int N;

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

void initMatriz(int row, int col, int **matrix){
//printf("matrix %i X %i:\n",row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix[i][j]= rand() % 256;
//printf("%i ", matrix[i][j]);
		}
//printf("\n");
	}
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

int filaXcolum (int N,int fil,int col,int **M, int **M1){
	int res = 0;
	for(int k=0;k<N;k++){
		res =(res +(M[fil][k]* M1[k][col]));
//printf("%i * %i +",A[i][k],B[k][j]);
	}
//cprintf("res -> %i\n",res );
	return res;
}






int main(int argc, char* const argv[]){
	if(argv[1]==NULL){
		perror("Digite el tamaño de la matrix N");
		exit(-1);
	}
	N = atoi(argv[1]);
	if (N != 2 && N != 4 && N != 8 && N != 16 && N != 32 && N != 64 && N != 128 && N != 256 && N != 512 && N!= 1024)
	{
		perror("El tamaño debe ser un numero de estos [2,4,8,16,32,64,128, 256, 512, 1024]");
		exit(-1);
	}
	int p;

	if(argv[2]!=NULL){
		p = atoi(argv[2]);
	}
	else{
		perror("Digite ademas el numero de procesos: 2 o 4");
		exit(-1);}
		if(p != 2 && p != 4){
			perror("Debe elegir entre 2 o 4 procesos");
			exit(-1);
		}


		time_t inicio,fin;
		double timediff;
//static int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE] = {0};
/*
for(int x = 0; x < 9; x++){
int N = arregloN[x];*/
	printf("Tamano matriz: %i\n", N);
	printf("Numero procesos: %i\n", p);
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

	int *MATRIZD[N];
	for (int i=0; i<N; i++)
		MATRIZD[i] = (int *)malloc(N * sizeof(int));
//printf("res 1X1 => %i\n", filaXcolum(N,1,1,MATRIZA,MATRIZB));

	pid_t pid;
	int pipefd1[2];
	pipe(pipefd1);

	int pipefd2[2],pipefd3[2];
	pipe(pipefd2);
	pipe(pipefd3);

	int dato[(N*N)/p];
	clock_t begin, end;
	double time_spent;
	begin = clock();

	for (int proceso=0; proceso<p-1; proceso++) {
		pid = fork();
		if (pid == 0) {

			if(proceso==0){
				close(pipefd1[0]);
				int dato[(N*N)/p];

				int k=0;

				for (int i = N/p; i < 2*N/p; i++)
				{
					for (int j = 0; j < N; j++)
					{
						dato[k] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
//printf("DATOp2:%i\n",dato[k] );
						k++;
					}
				}

				write(pipefd1[1],&dato,sizeof(int[(N*N)/p]));
				close(pipefd1[1]);
				exit(0);
			}

			if(proceso==1){
				close(pipefd2[0]);
				int dato[(N*N)/4];
				int k=0;
				for (int i = N/2; i < N*3/4; i++)
				{
					for (int j = 0; j < N; j++)
					{
						dato[k] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
//printf("DATOp3:%i\n",dato[k] );
						k++;
					}
				}
				write(pipefd2[1],&dato,sizeof(int[(N*N)/4]));
				close(pipefd2[1]);
				exit(0);

			}
			if(proceso==2){
				close(pipefd3[0]);
				int dato[(N*N)/4];
				int k=0;
				for (int i = N*3/4; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						dato[k] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
//printf("DATOp4:%i\n",dato[k] );
						k++;
					}
				}
				write(pipefd3[1],&dato,sizeof(int[(N*N)/4]));
				close(pipefd3[1]);
				exit(0);

			}
			exit(0);

		} else if (pid == -1) {
			perror("fallo en fork");
			exit(EXIT_FAILURE);
		}
	}
	close(pipefd1[1]);

	if(p==4){
		close(pipefd2[1]);
		close(pipefd3[1]);}

		for (int i = 0; i < N/p; i++)
		{
			for (int j = 0; j < N; j++)
			{
				MATRIZC[i][j] = filaXcolum(N,i,j,MATRIZA,MATRIZB);
//printf("DATOp1:%i\n",MATRIZC[i][j] );
			}
		}

		read(pipefd1[0],&dato,sizeof(int [(N*N)/p]));
		int k = 0;
		for (int i = N/p; i < 2*N/p; i++)
		{
			for (int j = 0; j < N; j++)
			{
				MATRIZC[i][j] = dato[k];
				k++;
			}
		}
		close(pipefd1[0]);

		if(p==4){
			read(pipefd2[0],&dato,sizeof(int [(N*N)/4]));
			k = 0;
			for (int i = N/2; i < N*3/4; i++)
			{
				for (int j = 0; j < N; j++)
				{
					MATRIZC[i][j] = dato[k];
					k++;
				}
			}
			close(pipefd2[0]);

			read(pipefd3[0],&dato,sizeof(int [(N*N)/4]));
			k = 0;
			for (int i = N*3/4; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					MATRIZC[i][j] = dato[k];
					k++;
				}
			}
			close(pipefd3[0]);
		}

		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("CON %i PROCESOS\n",p);

		printf("---------------\n");
		printf("Elapsed time: %.2lf seconds.\n", time_spent);
//imprimirMatriz(N,N,MATRIZC);

		exit(0);
	}