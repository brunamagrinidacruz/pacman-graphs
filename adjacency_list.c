#include "adjacency_list.h"
#include "list.h"

struct graph_ {
    int number_of_vertices;
    LIST** adjacency_list;
};

GRAPH* graph_create(int number_of_vertices) {
    int i;
    GRAPH* graph;
    graph = (GRAPH *) malloc(sizeof(GRAPH));
    if(graph != NULL) {
        graph->adjacency_list = (LIST **) malloc(sizeof(LIST *) * number_of_vertices);
        for(i = 0; i < number_of_vertices; i++) {
            graph->adjacency_list[i] = list_create();
        }
        graph->number_of_vertices = number_of_vertices;
    }
    return graph;
}

void graph_delete(GRAPH** graph) {
    if((*graph) != NULL) {
        int i;
        for(i = 0; i < (*graph)->number_of_vertices; i++) 
            list_delete(&(*graph)->adjacency_list[i]);
        free((*graph)->adjacency_list);
        free(*graph);
    }
    graph = NULL;
    return;
}

void graph_insert(GRAPH* graph, int convergent, int divergent) {
    if(graph != NULL) {
        list_insert(graph->adjacency_list[convergent], divergent); 
        list_insert(graph->adjacency_list[divergent], convergent); 
    }
    return;
}

void graph_remove(GRAPH* graph, int convergent, int divergent) {
    if(graph != NULL) {
        list_remove(graph->adjacency_list[convergent], divergent); 
        list_remove(graph->adjacency_list[divergent], convergent); 
    }
    return;
}

int graph_number_of_vertices(GRAPH* graph) {
    if(graph != NULL) {
        return graph->number_of_vertices;
    }
}

void graph_print_element(GRAPH* graph, int vertex, int adjacent_vertex) {
     if(graph != NULL) {
        return list_print_no(graph->adjacency_list[vertex], adjacent_vertex);
    }
}

int graph_is_adjacency_list_empty(GRAPH* graph, int vertex) {
    if(graph != NULL) {
        return list_size(graph->adjacency_list[vertex]) == 0;
    }
}

int graph_first_vertex_list_adjacency(GRAPH* graph, int vertex) {
    if(graph != NULL) {
        return list_first_element(graph->adjacency_list[vertex]);
    }
}

int graph_next_vertex_list_adjacency(GRAPH* graph, int vertex, int *current_vertex, int *next_vertex) {
    if(graph != NULL) {
        return list_next_element(graph->adjacency_list[vertex], current_vertex, next_vertex);
    }
}

void graph_print(GRAPH* graph) {
    if(graph != NULL) {
        int i;
        for(i = 0; i < graph->number_of_vertices; i++) {
            printf("%d: ", i);
            list_print(graph->adjacency_list[i]);
        }
        printf("\n");
    }
    return;
}