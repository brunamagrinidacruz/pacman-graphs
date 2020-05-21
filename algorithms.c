#include "algorithms.h"

typedef enum {
    white, grey, black
} colors;

void execute_bfs(GRAPH* graph, int vertex, int distancy[], int ancestor[], colors color[]) {
    //Creating a queue that will stored the adjacents vertex in sequence of visited. 
    //The BFS will be execute to all vertex inside the queue
    QUEUE* queue;
    queue = queue_create();

    //Initializing vertex as grey (visited)
    color[vertex] = grey;
    //Because this vertex is the initial vertex, distancy = 0
    distancy[vertex] = 0;

    queue_insert(queue, vertex);
    printf("vertex: %d | distancy: %d | ancestor: %d\n", vertex, distancy[vertex], ancestor[vertex]);

    int current_vertex = -1, next_vertex = -1;

    //While queue is not empty, there is still vertex to be visited
    while(!queue_is_empty(queue)) {
        int initial_vertex = queue_remove(queue);
        //Verify if there is vertex in adjacency list
        if(!graph_is_adjacency_list_empty(graph, initial_vertex)) {
            int first_vertex_list_adjacency = graph_first_vertex_list_adjacency(graph, initial_vertex);
            int is_end_vertex_list_adjacency = 0;
            //We also initializing the next_vertex as the first vertex of the list,
            //This because the function graph_next_vertex_list_adjacency will put the next_vertex
            //In current_vertex
            next_vertex = first_vertex_list_adjacency;
            //While the adjacency list of the vertex doesn't end, continue to visited their adjacencys
            while(!is_end_vertex_list_adjacency) {
                //This function will put in current_vertex the id of the vertex we are analizing
                //And in next_vertex, it will put the value of the next_vertex to be executed
                is_end_vertex_list_adjacency = graph_next_vertex_list_adjacency(graph, initial_vertex, &current_vertex, &next_vertex);
                if(color[current_vertex] == white) {
                    //It's visited and now we have to put in queue to be processed
                    color[current_vertex] = grey;
                    distancy[current_vertex] = distancy[initial_vertex] + 1;
                    ancestor[current_vertex] = initial_vertex;
                    queue_insert(queue, current_vertex);
                    printf("vertex: %d | distancy: %d | ancestor: %d\n", current_vertex, distancy[current_vertex], ancestor[current_vertex]);
                }
            }
        }
        //When all vertices in adjacency list are executed (or if there is no adjacency vertext)
        color[initial_vertex] = black;
    }
    queue_delete(&queue);
}

void bfs(GRAPH* graph) {
    int i;
    int vertex;
    int number_of_vertices = graph_number_of_vertices(graph);
    int *distancy, *ancestor;
    colors *color;
    distancy = (int*) malloc (sizeof(int) * number_of_vertices);
    ancestor = (int*) malloc (sizeof(int) * number_of_vertices);
    color = (colors*) malloc (sizeof(colors) * number_of_vertices);

    //Initializing
    //color: as white because any vertex was visited
    //distancy: as -1 because any vertex had its distancy calculeted
    //ancestor: as -1 because any vertex has a ancestor yet
    for(i = 0; i < number_of_vertices; i++) {
        color[i] = white;
        distancy[i] = -1;
        ancestor[i] = -1;
    }

    //Verifing if some vertex is still white. If it's, execute bfs to it
    for(i = 0; i < number_of_vertices; i++) {
        if(color[i] == white)
            execute_bfs(graph, i, distancy, ancestor, color);
    }

    free(distancy);
    free(ancestor);
    free(color);
}

void execute_dfs(int *index, GRAPH* graph, int vertex, colors color[], int visited[], int processed[], int ancestor[]) {
    int current_vertex = -1, next_vertex = -1;
    color[vertex] = grey;
    (*index) = (*index) + 1;
    visited[vertex] = (*index);

    //Verify if there is vertex in adjacency list
     if(!graph_is_adjacency_list_empty(graph, vertex)) {
        int first_vertex_list_adjacency = graph_first_vertex_list_adjacency(graph, vertex);
        int is_end_vertex_list_adjacency = 0;

        //We also initializing the next_vertex as the first vertex of the list,
        //This because the function graph_next_vertex_list_adjacency will put the next_vertex
        //In current_vertex
        next_vertex = first_vertex_list_adjacency;
        //While the adjacency list of the vertex doesn't end, continue to visited their adjacencys
        while(!is_end_vertex_list_adjacency) {
            //This function will put in current_vertex the id of the vertex we are analizing
            //And in next_vertex, it will put the value of the next_vertex to be executed
            is_end_vertex_list_adjacency = graph_next_vertex_list_adjacency(graph, vertex, &current_vertex, &next_vertex);
            //If the current_vertex is white, its need to be visited
            if(color[current_vertex] == white) {
                ancestor[current_vertex] = vertex;
                execute_dfs(index, graph, current_vertex, color, visited, processed, ancestor); 
            }
        }
     }

    //If the adjacency list was all visited, the vertex now is black
    (*index) = (*index) + 1;
    processed[vertex] = (*index);
    printf("%d | by ancestor %d | grey in %d | black in %d\n", vertex, ancestor[vertex], visited[vertex], processed[vertex]);
    color[vertex] = black;
}

void dfs(GRAPH* graph) {
    if(graph != NULL) {
        int i;
        int index = 0; //Count
        int number_of_vertices = graph_number_of_vertices(graph);

        colors *color = (colors*) malloc (sizeof(colors) * number_of_vertices); //Store the color of each vertex
        int *visited = (int *) malloc (sizeof(int) * number_of_vertices); //Store when the vertex was visited
        int *processed = (int *) malloc (sizeof(int) * number_of_vertices); //Store when the vertex was processed
        int *ancestor = (int *) malloc (sizeof(int) * number_of_vertices); //Store who is the ancestor to each vertex

        for(i = 0; i < number_of_vertices; i++) {
            color[i] = white;
            visited[i] = -1;
            processed[i] = -1;
            ancestor[i] = -1;
        }

        //To each vertex that is equal to white, call execute_dfs
        //This is useful if it is a disconnected graph
        for(i = 0; i < number_of_vertices; i++) {
            if(color[i] == white)
                execute_dfs(&index, graph, i, color, visited, processed, ancestor);
        }

        free(color);
        free(visited);
        free(processed);
    }
}