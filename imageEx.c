#include<stdio.h>
#include<stdlib.h>

extern char **environ;

int init_global_var =3;
int uinit_global_var;


int main(int argc, char *argv[]){
	int auto_var;
	static int static_var;
	register int reg_var;
	char *auto_ptr;
		
	auto_ptr = malloc(10);
	return 0;
	
}
