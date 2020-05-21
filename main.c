#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"
#include "algorithms.h"

#define INSERT_EDGE 1
#define REMOVE_EDGE 2
#define SHOW_LIST 3
#define BFS 4
#define DFS 5

int main(void) {
    GRAPH* graph;
    int i;
    int number_of_vertices, number_of_edges;
    int convergent, divergent;
    int number_of_operations, operation;

    scanf("%d", &number_of_vertices);
    graph = graph_create(number_of_vertices);

    scanf("%d",&number_of_edges);
    for(i = 0; i < number_of_edges; i++) {
        scanf("%d", &convergent);
        scanf("%d", &divergent);
        graph_insert(graph, convergent, divergent);
    }

    scanf("%d", &number_of_operations);
    printf("\n");
    for(i = 0; i < number_of_operations; i++) {
        scanf("%d", &operation);
        switch(operation) {
            case INSERT_EDGE: 
                scanf("%d", &convergent);
                scanf("%d", &divergent);
                graph_insert(graph, convergent, divergent);
                break;
            case REMOVE_EDGE:
                scanf("%d", &convergent);
                scanf("%d", &divergent);
                graph_remove(graph, convergent, divergent);
                break;
            case SHOW_LIST:
                graph_print(graph);
                break;
            case BFS:
                bfs(graph);
                printf("\n");
                break;
            case DFS:
                dfs(graph);
                printf("\n");
                break;
        }
    }

    graph_delete(&graph);

    return 0;
}

