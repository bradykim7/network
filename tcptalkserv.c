#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

char *EXIT_STRING = "exit";
int recv_and_print(int sd);
int input_and_send(int sd);

#define MAXLINE 511

int main(int argc, char *argv[]){

	struct sockaddr_in cliaddr, servaddr;
	/*
		struct sockaddr_in{
			short sin_family;
			u_short sin_port;
			struct in_addr sin_addr;
			char sin_zero[8];
		}
	*/
	int listen_sock, accp_sock;

	unsigned int addrlen = sizeof(cliaddr);
	pid_t pid;

	if(argc != 2){
		printf("사용법 %s port \n",argv[0]);
		exit(0);
	}

	if( (listen_sock = socket(PF_INET, SOCK_STREAM, 0)) <0){
		perror("SOCKET FAIL");
		exit(0);
	}

	bzero((char *)&servaddr, addrlen);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));

	if(bind(listen_sock,(struct sockaddr *)&servaddr, sizeof(servaddr)) <0){
		perror("BIND FAIL");
		exit(0);
	}

	puts("SERVER WAITING ..... ");
	listen(listen_sock,1);

	if((accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen)) <0){
		perror("ACCEPT FAIL");
		exit(0);
	}

	puts("CLIENT CONNECT ! ");
	
	if( (pid= fork())>0)
		input_and_send(accp_sock);
	else if( pid == 0)
		recv_and_print(accp_sock);

	
	close(listen_sock);
	close(accp_sock);
	
	return 0;
}

int input_and_send(int sd){

	char buf[MAXLINE +1];
	
	while(fgets(buf, sizeof(buf), stdin) != NULL){
		write(sd, buf, strlen(buf));

		if(strstr(buf, EXIT_STRING) != NULL ){
			puts("GOOD BYE ! ");
			close(sd);
			exit(0);
		}
	}

	return 0;
}

int recv_and_print(int sd){

	char buf[MAXLINE +1];
	int nbyte;
	
	while(1){
		if((nbyte = (read(sd,buf,MAXLINE))) < 0){
			perror("READ FAIL");
			close(sd);
			exit(0);
		}

		buf[nbyte] = 0;
		
		if(strstr(buf, EXIT_STRING) != NULL)
			break;
		printf("%s",buf);
	}
	return 0;
}
