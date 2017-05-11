#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "readln.c"

#define NR PIPE_BUF

int main (int argc, char** argv){
	char *buf = (char *) malloc(1024);

	if(!argv[1]) {
		write(0, "ERROR\n", 6);
		_exit(1);
	}

	char *aux = (char *) malloc(strlen(buf) + strlen(argv[1])+1);

	int n;

	while((n = readln(0,buf,1024))>1){
		if(buf[0] == ':'){
			write(0, "ERROR\n", 6);
			_exit(1);
		}
		aux = (char *) realloc(aux, strlen(buf) + strlen(argv[1])+1);
		buf[n-1] = '\0';
		snprintf(aux, NR, "%s:%s\n",buf,argv[1]);
		write(0, aux, strlen(aux));
	}

	free(aux);
	free(buf);
	
	_exit(0);
	
}