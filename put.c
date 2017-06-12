#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define NR PIPE_BUF

void put(char *buf, int n){
	int len = strlen(buf);
	char *aux2, aux[NR];
	aux2 = strdup(buf);
	aux2[len-1] = '\0';
	snprintf(aux, NR, "%s:%d\n", aux2, n);
	write(1, aux, strlen(aux));
}