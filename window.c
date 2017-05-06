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

void put(char *buf, int n){
	int len = strlen(buf);
	char *aux2, aux[2];
	aux2 = strdup(buf);
	snprintf(aux, len+2, ":%d", n);
	aux2[len-1] = '\0';
	strcat(aux2, aux);
	printf("%s\n",aux2 );
}


int main(int argc, char const *argv[]) {
	char *tmp, *tok, *buf = malloc(1024);
	int *ops = malloc(sizeof(int)*1024);
	int n, i, k = 0, nL = 0, j = 0, tp = 0;
	while((n = readln(0, buf, 1024)) > 1){
		tmp = strdup(buf);
		tok = strtok(tmp, ":");
		for(i = 1; tok; i++){
			if(i ==  atoi(argv[1]))
				ops[k] = atoi(tok);
			tok = strtok(NULL, ":");
		}
		if(nL == 0){
			put(buf, 0);
		}else{
			if(!strcmp("avg", argv[2])){
				int media, sum = 0, nargs = atoi(argv[3]);
				for(i = nL - nargs; i < nL; i++){
					while(i < 0 ){
						i++;
						nargs--;
					}
					sum += ops[i];
				}
				media = sum/nargs;
				put(buf, media);
			}
			if(!strcmp("min", argv[2])){
				int curr, min;
				for(i = nL - atoi(argv[3]); i < nL; i++){
					while(i < 0 ){
						i++;
					}
					curr = ops[i];
					if(i == 0)
						min = curr;
					if(curr < min)
						min = curr;
				}
				put(buf, min);
			}
			if(!strcmp("max", argv[2])){
				int curr, max = -1;
				for(i = nL - atoi(argv[3]); i < nL; i++){
					while(i < 0 ){
						i++;
					}
					curr = ops[i];
					if(curr > max)
						max = curr;
				}
				put(buf, max);
			}
			if(!strcmp("sum", argv[2])){
				int sum = 0;
				for(i = nL - atoi(argv[3]); i < nL; i++){
					while(i < 0 ){
						i++;
					}
					sum += ops[i];
				}
				put(buf, sum);
			}
		}
	nL++;
	k++;
	}
	return 0;
}

