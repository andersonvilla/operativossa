#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void dijkstra_with_no_heap();

int dijkstra_no_heap_result[MAX_NODES][3]; //Saves the result like the objective table;

void dijkstra_with_no_heap(int origin_node_index){
    int visitedNodesIndexGuide=0;           //Guide for the visited nodes
    int visitedNodesIndex[MAX_NODES];       //Saves the index of the visited nodes
    for(int i=0; i<MAX_NODES; i++){         //Initializes all visited nodes index on -1
        visitedNodesIndex[i]=-1;            //So it doesn't get confused with index 0
    }

    int routedNodes[MAX_NODES]={0};             //Saves the index nodes that have been routed

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