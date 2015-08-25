#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

float serie (int i){
	float res1 = (float)4/((2*i)+1);
	float res2 = (float)4/((2*i)+3);
	return (float)(res1 - res2);
}

int  main(int argc, char const *argv[])
{
	int pipefd[2],r;
	pid_t pid;
	float dato,mitad1,mitad2 = 0.0;
	
	r = pipe(pipefd);
	if(r == -1){
		perror("ERROR");	
	}
	pid = fork();
	if(pid == -1){
		perror("ERROR");
	}
	if(pid == 0){
		close(pipefd[1]); // Close the read end
		long iter = 1000000000;
		for (int i = 500000000; i < iter; i = i+2)
		{	
			float res1 = (float)4/((2*i)+1);
			float res2 = (float)4/((2*i)+3);
			mitad2 = mitad2 + res1 -res2; //pi + (4/((2*i)+1) - 4/((2*i)+3));
		}
		write(pipefd[1],&mitad2,sizeof(float));
		close(pipefd[0]);

	}else{
		long iter = 500000000;
		close(pipefd[0]); // Close the write end
		for (int i = 0; i < iter; i = i+2)
		{	
			float res1 = (float)4/((2*i)+1);
			float res2 = (float)4/((2*i)+3);
			mitad1 = mitad1 + res1 -res2; //pi + (4/((2*i)+1) - 4/((2*i)+3));
		}
		read(pipefd[0],&mitad2,sizeof(float));
		close(pipefd[1]);
		float pi = mitad1 + mitad2;
		printf("PI= %.10f\n", pi);
	}
	exit(0);}