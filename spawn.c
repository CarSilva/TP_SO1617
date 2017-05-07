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
	int i, j, n, dolares[argc];
	char *buf = (char *) malloc(1024);
	char *tok;

	if(!argv[1]) {
		printf("ERRO\n");
		_exit(1);
	}



	for(i = 0; i < argc; i++){

		if(strstr(argv[i],"$") == NULL){
			//printf("cucu\n");
			//printf("%s\n",argv[i]);
			dolares[j++] = atoi(argv[i]);
			//printf("ola  %d\n",dolares[j]);
		}
	}

	

	while(n = readln(0,buf,1024)){
		if(buf[0] == ':'){
			printf("ERRO\n");
			_exit(1);
		}
		buf[n] = '\0';

		tok = strtok(buf,":");
		for(i = 0; i < j; i++){
			if(i == dolares[i]){
				strcpy(argv[i],tok);
			}
			tok = strtok(NULL,":");
		}
		for(i=0;i<argc;i++)
			printf("i: %d  %s\n",i, argv[i]);
		
	}


	
}