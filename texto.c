#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODES 20
#define MAX_NODE_LENGHT 20

char *nodes[MAX_NODES];//[MAX_NODE_LENGHT];
int number_of_nodes = 0;
int adj[MAX_NODES][MAX_NODES];

int origin_node_index;
int dijkstra_no_heap_result[MAX_NODES][3]; //Saves the result like the objective table;

void dijkstra_with_no_heap(){
    int visitedNodesIndexGuide=0;           //Guide for the visited nodes
    int visitedNodesIndex[MAX_NODES];       //Saves the index of the visited nodes
    for(int i=0; i<MAX_NODES; i++){         //Initializes all visited nodes index on -1
        visitedNodesIndex[i]=-1;            //So it doesn't get confused with index 0
    }

    int routedNodes[MAX_NODES];             //Saves the index nodes that have been routed

    dijkstra_no_heap_result[0][0]=origin_node_index;    //Origin node is always the first row of the result
    dijkstra_no_heap_result[0][1]=0;                    //And always has cost 0 to itself

    visitedNodesIndex[visitedNodesIndexGuide] = origin_node_index;  //Origin node is always visited by default
    visitedNodesIndexGuide++;

    for(int i=0; i<number_of_nodes; i++){
        int visitedNodesIndexToRoute=0;           //Index to the node to be routed
        int minRouteCost = -1;
        for(int x=0; x<number_of_nodes; x++){                               //Look for the next node to route
            if(routedNodes[x]==0){                                          //If the node hasn't been routed and
                if(visitedNodesIndex[x]!=-1){                               //If the node was visited and
                    if(minRouteCost == -1){                                 //If is the first option
                        visitedNodesIndexToRoute=x;                         //Save it to route it and
                        minRouteCost= dijkstra_no_heap_result[x][1];        //Save it's cost
                    }else{                                                  //If is not the first option and
                        if(minRouteCost>dijkstra_no_heap_result[x][1]){     //The previous cost is bigger
                            visitedNodesIndexToRoute=x;                     //Save it to route it
                            minRouteCost= dijkstra_no_heap_result[x][1];    //Save it's cost
                        }
                    }
                }
            }
        }

        for(int j=0; j<number_of_nodes; j++){
            if(adj[visitedNodesIndex[visitedNodesIndexToRoute]][j]!=0){     //If the matrix has a cost different from 0
                int visited=0;
                int resultIndex;
                for(int k=0; k<number_of_nodes; k++){   //Checks if destination node was visited
                    if(visitedNodesIndex[k]==j){
                        visited=1;
                        resultIndex=k;                  //If was visited save de index
                        break;
                    }
                }
                if(visited==0){                                     //If it wasn't
                    visitedNodesIndex[visitedNodesIndexGuide] = j;  //Add it to the visited list
                    dijkstra_no_heap_result[visitedNodesIndexGuide][0] = j; //Save it in the result
                    dijkstra_no_heap_result[visitedNodesIndexGuide][1] = dijkstra_no_heap_result[visitedNodesIndexToRoute][1] + adj[visitedNodesIndex[visitedNodesIndexToRoute]][j]; //Save the total cost
                    dijkstra_no_heap_result[visitedNodesIndexGuide][2] = visitedNodesIndex[visitedNodesIndexToRoute];                                                                //And it's previous node index
                    visitedNodesIndexGuide++;
                }else{
                    if(dijkstra_no_heap_result[resultIndex][1]>dijkstra_no_heap_result[visitedNodesIndexToRoute][1] + adj[visitedNodesIndex[visitedNodesIndexToRoute]][j]){          //If prev cost is bigger than the new cost
                        dijkstra_no_heap_result[resultIndex][1] = dijkstra_no_heap_result[visitedNodesIndexToRoute][1] + adj[visitedNodesIndex[visitedNodesIndexToRoute]][j]; //Save the total cost
                        dijkstra_no_heap_result[resultIndex][2] = visitedNodesIndex[visitedNodesIndexToRoute];                                                                //And it's previous node index
                    }
                }
            }
        }
        routedNodes[visitedNodesIndexToRoute]=1;      //The node in the index visitedNodesIndexToRoute of visitedNodesIndex has been routed
    }

    printf("\n\n");
    printf("Node - From - Prev\n");             //Print the result
    for(int i=0; i<visitedNodesIndexGuide; i++){
        printf(" ");
        fputs(nodes[dijkstra_no_heap_result[i][0]],stdout);
        printf("  -  %d   -  ",dijkstra_no_heap_result[i][1]);
        if(i!=0){
            fputs(nodes[dijkstra_no_heap_result[i][2]],stdout);
        }
        printf("\n");
    }
}

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

//Returns -1 if node is not present
int get_index_of_node(char *node_to_check){
    int value = -1;
    for(int i=0; i<number_of_nodes; i++){
        if(0 == (strcmp(nodes[i], node_to_check))){
            value = i;
            break;
        }
    }
    //printf("Index: %d\n", value);
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
    print_adj();
    char *orgin_node = ask_origin_node();
    origin_node_index = get_index_of_node(orgin_node);
    dijkstra_with_no_heap();


}