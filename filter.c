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


int main(int argc, char const *argv[]) {
	char *buf = malloc(1024);
	char *tok, *aux;
	int n, i = 0, max, min;
	while((n = readln(0, buf, 1024)) > 1) {
			aux = strdup(buf);
			if(aux[0] == ':'){
				printf("ERRO\n");
				_exit(1);
			}
			tok = strtok(aux, ":");
			for(i = 1; tok; i++){
				if(i == atoi(argv[1])){
					min = atoi(tok);
				}
				if(i == atoi(argv[3])){
					max = atoi(tok);
				}
				tok = strtok(NULL, ":");	
			}
			
			if(strcmp(argv[2], ">") == 0)
					if(min > max) {
						printf("%s", buf);
					}
					
			if(strcmp(argv[2], "<") == 0)
					if(min < max) {
						printf("%s", buf);
					}
			if(strcmp(argv[2], "=") == 0)
					if(min == max) {
						printf("%s", buf);
					}
			if(strcmp(argv[2],"<=") == 0)
					if(min <= max){
						printf("%s", buf);
					}
			if(strcmp(argv[2],">=") == 0) 
					if(min >= max){
						printf("%s", buf);
					}

			if(strcmp(argv[2], "!=") == 0)
					if(min != max){
						printf("%s", buf);
					}
	}
	return 0;
}

