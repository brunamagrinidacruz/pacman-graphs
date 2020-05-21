#ifndef ADJACENCY_LIST_H 
    #define ADJACENCY_LIST_H

    #include <stdlib.h>

    typedef struct graph_ GRAPH;

    GRAPH* graph_create(int number_of_vertices);
    void graph_delete(GRAPH** graph);

    void graph_insert(GRAPH* graph, int convergent, int divergent);
    void graph_remove(GRAPH* graph, int convergent, int divergent);

    void graph_print_element(GRAPH* graph, int vertex, int adjacent_vertex);
    
    int graph_number_of_vertices(GRAPH* graph);
    int graph_is_adjacency_list_empty(GRAPH* graph, int vertex);
    int graph_first_vertex_list_adjacency(GRAPH* graph, int vertex);
    int graph_next_vertex_list_adjacency(GRAPH* graph, int vertex, int *current_vertex, int *next_vertex);

    void graph_print(GRAPH* graph);
    
#endif