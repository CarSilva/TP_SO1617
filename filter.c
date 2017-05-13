#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "readln.c"



int main(int argc, char const *argv[]) {
	char *buf = malloc(1024);
	char *tok, *aux;
	int n, i = 0, max, min;
	while((n = readln(0, buf, 1024)) > 1) {
			aux = strdup(buf);
			if(aux[0] == ':'){
				write(0, "ERROR\n", 6);
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
			
			if(!strcmp(argv[2], ">"))
					if(min > max) {
							write(1, buf, n);
							write(1, "\n", 1);
					}
					
			if(!strcmp(argv[2], "<"))
					if(min < max) {
							write(1, buf, n);
							write(1, "\n", 1);
					}
			if(!strcmp(argv[2], "="))
					if(min == max) {
							write(1, buf, n);
							write(1, "\n", 1);
					}
			if(!strcmp(argv[2],"<="))
					if(min <= max){
							write(1, buf, n);
							write(1, "\n", 1);
					}
			if(!strcmp(argv[2],">=")) 
					if(min >= max){
							write(1, buf, n);
							write(1, "\n", 1);
					}

			if(!strcmp(argv[2], "!="))
					if(min != max){
							write(1, buf, n);
							write(1, "\n", 1);
					}
	}
	return 0;
}

