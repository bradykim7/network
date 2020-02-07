#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


#define MAXLINE  1023

int main(int argc ,char *argv[]){

	int send_s, recv_s;
	int n;
	unsigned int len;


	pid_t pid;

	unsigned int  yes =1; //
	struct sockaddr_in mcast_group;
	struct ip_mreq mreq;
	/*
	   typedef struct ip_mreq {
		  IN_ADDR imr_multiaddr;
		 IN_ADDR imr_interface;
		 } IP_MREQ, *PIP_MREQ;
	   */
	char name[10];

	if(argc != 4){
		printf(" 사용법 : %s multicast_address port My_name \n", argv[0]);
		exit(0);
	}

	sprintf(name,"[%s]", argv[3]);

	bzero(&mcast_group, sizeof(mcast_group));
	//memset(&mcast_group,0,sizeof(mcast_group));

	mcast_group.sin_family = AF_INET;
	mcast_group.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &mcast_group.sin_addr);

	// 멀티캐스트 수신용 소켓 개설
	if( (recv_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("ERROR : CAN'T CREATE RECEIVE SOCKET");
		exit(0);
	}	
	// 멀티캐스트 그룹에가입
	mreq.imr_multiaddr = mcast_group.sin_addr;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if( (setsockopt(recv_s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) < 0){
		perror("ERROR : ADD MEMBERSHIP");
		exit(0);
	}
	// 소켓 재사용 옵션 지정
	if( (setsockopt(recv_s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) <0){
		perror("ERROR : REUSE SETSOCKOPT");
		exit(0);
	}
	
	if( (bind(recv_s, (struct sockaddr *)&mcast_group, sizeof(mcast_group))) < 0){
		perror("ERROR : BIND RECEIVE SOCKET");
		exit(0);
	}
	
	// 멀티캐트스 송신용 소캣 개설
	if( (send_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("ERROR : CAN'T CREATE SEND SOCKET");
		exit(0);
	}

	if( (pid= fork()) < 0){
		perror("ERROR : FORK");
		exit(0);

	}
	// child process for Receiving Message ..
	else if(pid == 0){
		struct sockaddr_in from;
		char message[MAXLINE+1];
		for(;;){
			printf("Receiving Message.. \n");
			len = sizeof(from);
			if( ( n = recvfrom(recv_s, message, MAXLINE, 0, (struct sockaddr*)&from,&len)) <0){
				perror("ERROR : RECVFROM");
				exit(0);
			}
			message[n] =0;
			printf("Receiced Message : %s\n", message);
		}
	}
	// parent process for Sending message 
	else{
		char message [MAXLINE+1], line[MAXLINE +1];
		printf("Send Message : ");
		while(fgets(message, MAXLINE, stdin) != NULL){
			sprintf(line, "%s %s", name, message);
			len =  strlen(line);

			if(sendto(send_s, line, strlen(line),0,(struct sockaddr*)&mcast_group,sizeof(mcast_group)) < len){
			perror("ERROR : SENDTO");
			exit(0);
			}
		}

	}

	return 0;
}
