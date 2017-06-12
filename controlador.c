#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "readln.c"

#define GRAPH_SIZE 30

typedef struct node {
	int id, size_dest;
	char **cmds;
	int *destination_ids;
	int *source_pfd;
	int *destination_pfd;
} *Node;

void node(Node *graph, int id, char **cmds);
void connect(Node *graph, int id, int *ids, int size);
void disconnect(Node *graph, int id1, int id2);
void inject(Node *graph, int id, char **cmds); 
void remove_node(Node *graph, int id);

void update_graph(Node *graph, char *buffer);
void traverse(Node *graph, int id, int *pipefd);



int main(int argc, char const *argv[]) {
	int n = 2;
	char *buffer = malloc(1024);
	Node *graph = malloc(sizeof(Node*)*GRAPH_SIZE);

	while((n = readln(0, buffer, 1024)) > 1) {
		buffer[n-1] = '\0';

		update_graph(graph, buffer);
	}
	return 0;
}

void update_graph(Node *graph, char *buffer){
	int i = 0, id;
	char *tok, **args = malloc(sizeof(char*)*10);
	
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

			node(graph, id, args);
		} else

		if(!strcmp(tok, "connect")) {
			int *ids = malloc(sizeof(int)*10);

			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");

			while(tok){
				ids[i++] = atoi(tok);
				tok = strtok(NULL, " ");
			}

			connect(graph, id, ids, i);
			free(ids);
		} else

		if(!strcmp(tok, "disconnect")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);
			tok = strtok(NULL, " ");
			i = atoi(tok);

			disconnect(graph, id, i);
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
		
			inject(graph, id, args);
		} else

		if(!strcmp(tok, "remove")) {
			tok = strtok(NULL, " ");
			id = atoi(tok);

			remove_node(graph, id);
		}
}

void node(Node *graph, int id, char **cmds) {
	Node node = (Node) malloc(sizeof(struct node));
	node->id = id;
	node->cmds = (char**) malloc(sizeof(char*)*5);
	node->destination_ids = (int*) malloc(sizeof(int*)*10);
	node->source_pfd = (int*) malloc(sizeof(int*)*10);
	node->destination_pfd = (int*) malloc(sizeof(int*)*10);
	node->size_dest = 0;

	int i;
	for(i = 0; cmds[i]; i++){
		node->cmds[i] = (char*) malloc(strlen(cmds[i])+1);
		strcpy(node->cmds[i], cmds[i]);
	}

	//inserir nodo no array/grafo
	graph[id-1] = node;

	
}

void connect(Node *graph, int id, int *ids, int size) {
	int i, j, flag = 0, pipefd[2];

	//percorrer o array ids
	for(i = 0; i < size; i++){

		//verificar se o nodo a adicionar e o proprio nodo
		if (id == ids[i])
			flag = 1;
		
		for (j = 0; j < graph[id-1]->size_dest; j++)
			//verificar se o nodo a inserir ja esta conectado
			if (graph[id-1]->destination_ids[j] == ids[i])
				flag = 1;

		if (!flag){
			pipe(pipefd);

			graph[id-1]->destination_ids[graph[id-1]->size_dest] = ids[i];
			graph[id-1]->source_pfd[graph[id-1]->size_dest] = pipefd[0];
			graph[id-1]->destination_pfd[graph[id-1]->size_dest++] = pipefd[1];
		}

		flag = 0;
	}
}

void disconnect(Node *graph, int id1, int id2) {
	int i, flag = 0;

	for (i = 0; i < graph[id1-1]->size_dest; i++){
		
		//encontrar o elemento a retirar
		if(graph[id1-1]->destination_ids[i] == id2){
			flag = 1;
			i++;
		}
		
		//retira o elemento, movendo os elementos da frente para a posicao anterior
		if (flag && i != graph[id1-1]->size_dest){
			graph[id1-1]->destination_ids[i-1] = graph[id1-1]->destination_ids[i];
			graph[id1-1]->source_pfd[i-1] = graph[id1-1]->source_pfd[i];
			graph[id1-1]->destination_pfd[i-1] = graph[id1-1]->destination_pfd[i];
		}
	}

	//decrementar o nr de destinos
	if (flag)
		graph[id1-1]->size_dest--;
}

void inject(Node *graph, int id, char **cmds) {
	int i, n, pp_a, pp_s[2], pp[2];
	pipe(pp_s);

	if (fork() == 0) {
		close(pp_s[0]);
		dup2(pp_s[1], 1);
		close(pp_s[1]);

		execvp(cmds[0], cmds);
		perror("Exec");
		exit(-1);

	} else {

		traverse(graph, id, pp_s);

	}
}

void traverse(Node *graph, int id, int *pp_s){
	
	int i, n, pp[2], pp_a;
	char *buffer = malloc(1024);

		close(pp_s[1]);
		pp_a = pp_s[0];

		pipe(pp);

		if(fork() == 0) {
			dup2(pp_a, 0);
			close(pp_a);
			
			//if(graph[id-1]->size_dest > 0){
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);
			//}

			execvp(graph[id-1]->cmds[0], graph[id-1]->cmds);
			perror("Exec");
			exit(-1);
		}
		close(pp[1]);
		close(pp_a);


	while ((n = readln(pp[0], buffer, 1024)) > 1){
			for (i = 0; i < graph[id-1]->size_dest; i++){
				write(graph[id-1]->destination_pfd[i], buffer, n);
			}
		}

		close(pp[0]);

		for (i = 0; i < graph[id-1]->size_dest; i++) {
			int auxpp[2] = {graph[id-1]->source_pfd[i],graph[id-1]->destination_pfd[i]};
			traverse(graph, graph[id-1]->destination_ids[i], auxpp);

		}
		for (i = 0; i < graph[id-1]->size_dest; i++)
			wait(NULL);

}

void remove_node(Node *graph, int id) {
	int i, j, flag = 0;

	for (i = 0; i < GRAPH_SIZE; i++)
		if (graph[i])
			for (j = 0; j < graph[i]->size_dest; j++)
				if (graph[i]->destination_ids[j] == id){
					disconnect(graph, i+1, id);
					connect(graph, i+1, graph[id-1]->destination_ids, graph[id-1]->size_dest);
				}

	graph[id-1] = NULL;


}
