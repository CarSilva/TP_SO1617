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
	return ++i;
}


int main (int argc, char** argv){
	char *buf = (char *) malloc(1024);
	char *aux = (char *) malloc(strlen(buf) + strlen(argv[1])+1);
	
	aux[0]='\0';
	
	int n = 1,a;
	int sn;
	

	while((a = readln(0,buf,1024))>1){
		aux = (char *) realloc(aux, strlen(buf) + strlen(argv[1])+1);
		strcat(aux,buf);
		strcat(aux,":");
		strcat(aux,argv[1]);
		printf("%s",aux);
		
	}
	free(aux);
	free(buf);

	return 0;
	
}