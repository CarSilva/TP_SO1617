#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "readln.c"

typedef struct ctrl {
	int id, sizeD;
	char **cmds;
	int *sourse;
	int *destination;
} *Ctrl;

void node(Ctrl *c, int id, char **cmds);
void connect(Ctrl *c, int id, int *ids);
void disconnect(Ctrl *c, int id1, int id2);
void inject(Ctrl *c, int id, char **args); 
void removeN(Ctrl *c, int id);



int main(int argc, char const *argv[]) {
	int n, id, i = 0;
	int *ids;
	char *tok, *buffer = malloc(16834);
	char **args;
	Ctrl *ctrl;
	while((n = readln(0,buffer, 1024)) > 1) {
		buffer[n-1] = '\0';
		tok = strtok(buffer, " ");

		if(!strcmp(tok, "node")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");
			while(tok){
				args[i++] = tok;
				tok = strtok(NULL, " ");
			}
			args[i] = NULL;
			node(ctrl, id, args);
		} else

		if(!strcmp(tok, "connect")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");
			while(tok){
				ids[i++] = atoi(tok);
				tok = strtok(NULL, " ");
			}
			connect(ctrl, id, ids);
		} else

		if(!strcmp(tok, "disconnect")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");
			i = atoi(tok);
			disconnect(ctrl, id, i);
		} else

		if(!strcmp(tok, "inject")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");
			while(tok){
				args[i++] = tok;
				tok = strtok(NULL, " ");
			}
			args[i] = NULL;
			inject(ctrl, id, args);
		} else

		if(!strcmp(tok, "remove")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			removeN(ctrl, id);
		}
	}
	return 0;
}

void node(Ctrl *c, int id, char **cmds) {

}

void connect(Ctrl *c, int id, int *ids) {
	
}

void disconnect(Ctrl *c, int id1, int id2) {
	
}

void inject(Ctrl *c, int id, char **args) {
	
}

void removeN(Ctrl *c, int id) {

}
