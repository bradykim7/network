#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 127

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	/*
		struct sockaddr{
			short sin_family
			u_short sin_port
			struct in_addr sin_addr
			char sin_zero[8]
		}
	*/

	int s, accp_sock,
		addrlen =sizeof(cliaddr),
		nbyte;
	char buf[MAXLINE +1];
	
	if(argc != 2){
		printf("usage : %s port\n", argv[0]);
		exit(0);
	}

	if((s = socket(PF_INET,SOCK_DGRAM, 0)) < 0){
		perror("SOCKET FAIL");
		exit(0);
	}

	bzero((char *)&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) <0){
		perror("BIND FAIL");
		exit(0);
	}

	
		puts("서버가 연결요청을 기다림..");
	while(1){

		puts("클라이언트 연결됨");
		nbyte = recvfrom(s, buf, MAXLINE,0, (struct sockaddr *)&cliaddr, (unsigned int*)&addrlen);
		sendto(s, buf, nbyte, 0 , (struct sockaddr *)&cliaddr, addrlen);
		close(accp_sock);
		
	}
	close(s);
	return 0;
}
