#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 127

int main(int argc,char * argv[]){

	struct sockaddr_in servaddr;
	int s, nbyte;
	char buf[MAXLINE +1];
	
	if(argc !=2){
		printf("USAGE : %s ipadress \n ",argv[0]);
		exit(0);
	}

	if( (s = socket(PF_INET, SOCK_STREAM, 0)) <0){
		perror("SOCKET FAIL");
		exit(0);
	}

	bzero((char *)&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(20743);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	// 프로토콜, 10진수 아이피 주소 (사람이 쓴거 ) , 저장될 곳 

	if((connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))) <0){
		perror("CONNECT FAIL");	
		exit(0);
	}
	
	printf("입력: " );
	if(fgets(buf, sizeof(buf), stdin) == NULL)
		exit(0);
	nbyte = strlen(buf);
		
	if(write(s,buf,nbyte)<0){
		printf("WRITE ERROR\n");
		exit(0);
	}

	printf("수신:");
	if(nbyte == read(s,buf,MAXLINE) < 0){
		perror("READ FAIL");
		exit(0);
	}

	buf[nbyte] =0;
	printf("%s \n", buf);
	close(s);
		
	return 0;
}
