#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// BIBLIOGRAFíA AL FINAL DE ESTE ARCHIVO

void dijkstra();

void dijkstra(int indexNodoInicio){
    /* 
    Creamos el vector donde guardamos información del nodo 
    (Distancia al nodo inicial y predecesor para llevar el camino)
    */
    struct InfoNodo path[number_of_nodes];

    /*
    Creamos la cola de prioridad (min_heap = 1) con la
    cantidad de nodos  igual a nodos de nuestro grafo
    */
    PQ *colaPrioridad = pq_create(number_of_nodes, 1);
    
    /*
    Se inicializan las distanciad con "infinito"
    (En este caso nuestro "infinto"=INT_MAX); además se llena la cola de
    prioridad, todos con la misma prioridad 
    (La prioridad en este caso se refiere a la distancia con respecto al nodo inicial,
    en el tope tenemos al nodo con  menor distancia al nodo inicial - menor prioridad)
    */
    for (int i = 0; i < number_of_nodes; i++){
        path[i].distancia = INT_MAX;
        pq_insert(colaPrioridad, i, INT_MAX);
    }

    /* 
    La distancia del nodo inicial es 0, hacemos el ajuste en el path
    y en la cola de prioridad
    */
    path[indexNodoInicio].distancia = 0;
    path[indexNodoInicio].nodoPredecesor = " ";
    pq_change_priority(colaPrioridad, indexNodoInicio, 0);

    // Mientras hayan distancias por determinar
    while (pq_size(colaPrioridad) > 0){

        /*
        En el tope de la cola de prioridad encontramos el nodo
        con distancia mínima en ese instante, a quien le analizaremos los vecinos
        */
        int indexNodoDistanciaMinima, distanciaMinima;
        pq_delete_top(colaPrioridad, &indexNodoDistanciaMinima,(double*) &distanciaMinima);

        // Analizamos los adyacentes del nodo con distancia mínima
        for (int i=0; i < number_of_nodes; i++){

            // Si el nodo indexNodoDistanciaMinima es adyacente a i
            if (adj[indexNodoDistanciaMinima][i] != 0){
                // Calculamos la distancia entre el nodo indexNododistanciaMinima y el nodo adyacente que estamos analizando
                int distancia = adj[indexNodoDistanciaMinima][i];

                // Si la distancia mínima parcial es mayor a la distancia acumulada hasta el nodo
                // indexNodoDistanciaMinima + distancia entre ambos nodos, actualizamos la información del nodo adyacente
                // que se está analizando tanto en el path como en la cola de prioridad
                if (path[i].distancia > path[indexNodoDistanciaMinima].distancia + distancia){
                    path[i].distancia = path[indexNodoDistanciaMinima].distancia + distancia;
                    path[i].nodoPredecesor = nodes[indexNodoDistanciaMinima];
                    pq_change_priority(colaPrioridad, i, path[i].distancia);
                }
            }
        }
        
        
    }

    // IMPRIMIMOS LA TABLA
    char nombreCol2[] = "Shortest distance from ";
    strcat(nombreCol2, nodes[indexNodoInicio]);

    printf("Distancias mínimas desde el nodo %s:\n", nodes[indexNodoInicio]);
    printf("| %-6s | %-24s | %-15s |\n", "Vertex", nombreCol2, "Previous vertex");
    for (int i = 0; i < number_of_nodes; i++) {
        printf("| %-6s | %-24d | %-15s |\n", nodes[i], path[i].distancia, path[i].nodoPredecesor);
        //printf("Nodo %s: %s\n", nodes[i], path[i].nodoPredecesor);
    }

}

/* 
BIBLIOGRAFíA 
- colaboradores de Wikipedia. (2023). Matriz de Adyacencia. Wikipedia, la enciclopedia libre. https://es.wikipedia.org/wiki/Matriz_de_adyacencia
- 7.20. El algoritmo de Dijkstra — solución de problemas con algoritmos y estructuras de datos. (s. f.). https://runestone.academy/ns/books/published/pythoned/Graphs/ElAlgoritmoDeDijkstra.html
- Navone, E. C. (2022). Dijkstra's Shortest Path Algorithm - A detailed and visual introduction. freeCodeCamp.org. https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/#:~:text=You%20need%20to%20follow%20these,%3E%204%20%2D%20%3E%206%20automatically.
- GeeksforGeeks. (2023). How to find shortest paths from source to all vertices using Dijkstra s algorithm. GeeksforGeeks. https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
*/