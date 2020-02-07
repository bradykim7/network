#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#define BUF_LEN 128
#include <arpa/inet.h>
#include<unistd.h>

int main (int argc, char *argv[]){

	int s,  n;
	char *haddr;
	struct sockaddr_in server_addr;
	char buf[BUF_LEN+1];
	
	if(argc <2){
		printf("사용법 : %s ip_address \n", argv[0]);
		exit(0);
	}
	
	haddr = argv[1];
	s = socket(PF_INET, SOCK_STREAM, 0);
	bzero((char *)&server_addr, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(haddr);
	server_addr.sin_port = htons(13);
	inet_pton(AF_INET, haddr, &server_addr.sin_addr);

	if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0){
		printf("Err\n");
	};

	while(	(n = read(s,buf,sizeof(BUF_LEN))) >0){
		buf[n] ='\0';
		printf("%s",buf);
	}
	close(s);

	return 0;
}
