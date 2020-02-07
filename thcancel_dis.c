// MAC OS USER must add option " -Wno-return-type " when use the gcc 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>
#include<errno.h>

void *thrfunc(void *arg);

void cancel_and_join(pthread_t tid);
int max_loop = 20000000;
int cnt=0;
pthread_t curthd;

int main(int argc, char **argv){
	pthread_t tid;
	// 최신 리눅스 에서는 pthread 의 구조체를 리턴 (단순 정수값을 리턴하지않음 : 이식성문제)
	int status, i ;
	struct timespec micro_sec = {0,100000};

	// cancel disable test
	printf("** PTHREAD_CANCEL_DISABLE\n");
	if((status = pthread_create(&tid, NULL, &thrfunc, NULL) != 0)){
			printf("thread create error : %s \n", strerror(status));
			exit(0);
	}


	nanosleep(&micro_sec,NULL);

	cancel_and_join(tid);
	return 0;
}

void *thrfunc(void *arg){
	int status;

	curthd= pthread_self();

	if((status = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL)) !=0){
		printf("pthread_setcancelstate fail: %s \n",strerror(status));
		exit(0);
	}

	for(cnt =1;cnt<max_loop;cnt++){
		if( cnt%50000 ==0 )
			pthread_testcancel();
	}
}
	//cancel able setting 
	/*
	   if( (status = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) != 0){
		printf("pthread_setcancelstate fail: %s\n"strerror(status));
		exit(0);
	   }
		cancel request postpone to cancelltaion point 
		pthread_setcnaceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	*/

void cancel_and_join(pthread_t tid){
	void *result;
	int status;

	if((status=pthread_cancel(tid)) != 0){
		printf("pthread_cancel error: %s \n",strerror(status));
		exit(0);
	}

	if((status=pthread_join(tid, &result) != 0)){
			printf("pthread join error: %s\n",strerror(status));
			exit(0);
	}

	if(result == PTHREAD_CANCELED)
		printf("[Thread ID = %d] thread is canceled \n", (unsigned int)tid);
	else 
		printf("[Thread ID = %d] thread is not canceled \n",(unsigned int)tid);

	printf("총 %d 번의 루프중 %d번의 루프를 돌았음 \n\n",max_loop,cnt);
	return;
}
