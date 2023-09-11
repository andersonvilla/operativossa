#include "grafo.c"
#include "dijkstraNoHeap.c"
#include "dijkstraMinHeap.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int origin_node_index;

char * trimwhitespace(char *str){
  char *end;
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;
  if(*str == 0)  // All spaces?
    return str;
  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  // Write new null terminator character
  end[1] = '\0';
  return str;
}

char *ask_origin_node(){
    char *org = malloc(1);
    printf("\n\nIngrese el nodo de origen: ");
    scanf(" %c",org);
    return org;
}

int main(int argc, char *argv[]){

    //Getting a pointer to the opened file and check possible error
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("The file doesn't exist");
        exit(EXIT_FAILURE);
    }

    size_t len = 0;     //This is ised to have an indication of how many characters we want to read using the  getline() function (Read documentation)
    ssize_t read;       //This is used to store the returned value. the double ss means signed size (To indicate error typically returning -1)
    char *line = NULL;
    char *s = NULL;
    int read_line = 0;
    int is_directed = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if(read_line == 0){
            s = line;
            //This while is to replace the \n by \0 to have a proper comparison using strcmp
            while(*s != '\n') {
                ++s;
            }
            *s = '\0';
            if(0 == (strcmp("true", line))){
                is_directed = 1;
            }
        }else{

            char *end_str;
            char *token = strtok_r(line, ";", &end_str);

   		    while (token !=NULL) {

                int i=0;
                int source = -1;
                int destination = -1;
                int weight = -1;
                char *end_token;
                char *token_inner = strtok_r(token, ",", &end_token);

   		        while (token_inner != NULL && i < 3) {
                    if(i == 0){
                        token_inner = trimwhitespace(token_inner);
                        token_inner+=1;
                        source = get_index_of_node(token_inner);
                        if(source == -1){
                            source = number_of_nodes;
                            nodes[source] = malloc(sizeof(char)*(strlen(token_inner) +1));
                            strcpy(nodes[source], token_inner);
                            number_of_nodes++;
                        }
                    }else if(i == 1){
                        token_inner = trimwhitespace(token_inner);
                        destination = get_index_of_node(token_inner);
                        if(destination == -1){
                            destination = number_of_nodes;
                            nodes[destination] = malloc(sizeof(char)*(strlen(token_inner) +1));
                            strcpy(nodes[destination], token_inner);
                            number_of_nodes++;
                        }
                    }else if(i == 2){
                        token_inner = trimwhitespace(token_inner);
                        s = token_inner;
                        //This while is to erase the the character ) and replace it by \n in order of no affect the atoi cast!
                        while(*s != ')') {
                            ++s;
                        }
                        *s = '\0';
                        weight = atoi(token_inner);
                    }else{
                        printf("Parsing error. Not possible four values for edege\n");
                    }
                    i++;
                    token_inner = strtok_r(NULL, ",", &end_token);
                }
                adj[source][destination] = weight;
                if(is_directed == 0){
                    adj[destination][source] = weight;
                }
                token = strtok_r(NULL, ";", &end_str);
            }
        }
        read_line++;
    }
    printf("\nMatriz de adyacencia:\n");
    print_adj();
    char *orgin_node = ask_origin_node();
    origin_node_index = get_index_of_node(orgin_node); 
    printf("\n\nSolución usando un algoritmo SIN el uso de HEAP:\n");
    dijkstra_with_no_heap(origin_node_index);
    printf("\n\nSolución usando un algoritmo CON el uso de HEAP:\n");
    dijkstra(origin_node_index);
}