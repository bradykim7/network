#include<sys/socket.h>
struct sockaddr{
	u_short sa_family; // 2byte
	char sa_data[14];  // 14byte  all = 16byte
};
// 이과정이 불편하여, <netinet/in.h> 사용
#include<netinet/in.h>

struct in_addr{
	u_long s_addr;	//32
};

struct sockaddr_in{
	short sin_family;	//2
	u_short sin_port;	//2	
	struct in_addr sin_addr;	//4
	char sin_zero[8];	//8
};
// total : 16 bytes

#include<sys/socket.h>
AF_INET;	// 2
AF_UNIX;	// 유닉스 파일 주소 체계 1
AF_NS;		// XEROX주소 체계 6
AF_IFNET6;	// IPV6 26


