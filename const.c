#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

ssize_t readln(int fildes, char *buf, size_t nbyte){
	int i = 0;
	int rd;
	while((i<nbyte) && (rd=read(fildes,buf+i,1)) > 0 && *(buf+i) != '\n'){
		i++;
	}
	return i;
}

int main (int argc, char** argv){
	char *buf = (char *) malloc(1024);

	if(!argv[1]) {
		printf("ERRO\n");
		_exit(1);
	}

	char *aux = (char *) malloc(strlen(buf) + strlen(argv[1])+1);
	

	int n;

	while(n = readln(0,buf,1024)){
		if(buf[0] == ':'){
			printf("ERRO\n");
			_exit(1);
		}
		aux = (char *) realloc(aux, strlen(buf) + strlen(argv[1])+1);
		buf[n] = '\0';
		strcat(aux,buf);
		strcat(aux,":");
		strcat(aux,argv[1]);
		printf("%s\n",aux);
		aux[0] = '\0';
	}

	free(aux);
	free(buf);
	
	_exit(0);
	
}