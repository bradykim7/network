// MAC OS USER must add option " -Wno-return-type " when use the gcc
// And argv tid => must type = > pthread_t not (integer)


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_THR 2

void *thrfunc(void *arg);
void prn_data(pthread_t who);
int who_run = -1;

int main(int argc, char **argv){
	pthread_t tid[MAX_THR];
	int i,status;

	for(i=0;i<MAX_THR;i++){
		if( (status = pthread_create(&tid[i],NULL,&thrfunc, NULL)) != 0){
			printf("thread create error: %s\n",strerror(status));
			exit(0);
		}
	}
	pthread_join(tid[0],NULL);
	return 0;
}

void *thrfunc(void *arg){
	while(1){
		prn_data(pthread_self());
	}
	return NULL;
}

void prn_data(pthread_t me){
	who_run = (long)me;
	if(who_run != (long)pthread_self()){
		printf("ERROR : %ld thread is running who_run =%d\n",(long)me,who_run);
	}
	who_run = -1;
}
