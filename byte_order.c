#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>

/*
struct servent{
	char *s_name;
	char **s_aliases;
	int s_port;
	char *s_proto;
};
*/


int main(){
	
	struct servent *servent;
	servent = getservbyname("echo","udp");
	struct servent *pmyservent;
	pmyservent = getservbyname("echo","udp");
	if(servent == NULL){
		printf("서비스 정보를 얻을수 없음  \n\n");
		exit(0);
	};

	printf("UDP  에코 포트 번호 네트워크 오더 : %d\n", servent->s_port);
	printf("UDP  에코 포트 번호 호스트 오더 : %d\n", ntohs(servent->s_port));
}
