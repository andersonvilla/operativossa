#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODES 20
#define MAX_NODE_LENGHT 20

char *nodes[MAX_NODES];//[MAX_NODE_LENGHT];
int number_of_nodes = 0;
int adj[MAX_NODES][MAX_NODES];

struct InfoNodo{
    int distancia;
    char *nodoPredecesor;
};

//Returns -1 if node is not present
int get_index_of_node(char *node_to_check){
    int value = -1;
    for(int i=0; i<number_of_nodes; i++){
        if(0 == (strcmp(nodes[i], node_to_check))){
            value = i;
            break;
        }
    }
    return value;
}

void print_adj(){
    printf("  ");
    for(int i=0; i<number_of_nodes; i++){
        fputs(nodes[i],stdout);
        printf(" ");
    }
    printf("\n");
    for(int i=0; i<number_of_nodes; i++){
        printf("%s ", nodes[i]);
        for(int j=0; j<number_of_nodes; j++){
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}