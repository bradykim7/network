#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int global_var =0;
int main(){
	pid_t pid;
	int local_var = 0;
	printf("%d\t",pid);
	printf("%d\n",getpid());
	if((pid =fork()) < 0){
		printf("fork error\n");
		exit(0);
	}
	else if(pid == 0){
		global_var++;
		local_var++;
		printf("CHILD - my pid is %d and parent's pid is %d \n",getpid(), getppid());
		printf("%d\n",pid);
	}
	else{
		sleep(2);
		printf("%d \n",pid);
		global_var +=5;	
		local_var +=5;
		printf("PARENT - my pid is %d child's pid is %d\n",getpid(),pid);
	}

	printf("\t global var : %d\n",global_var);
	printf("\t local var : %d\n",local_var);
	printf("%d",pid);
	return 0;
}
