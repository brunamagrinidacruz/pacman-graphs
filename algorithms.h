#ifndef ALGORITHMS_H
    #define ALGORITHMS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "adjacency_list.h"
    #include "queue.h"

    void bfs(GRAPH* graph, int enemy_position, int distancy[]);
    void wavefront(GRAPH* graph, int size, int player_position, int distancy[], int* displacement);
    void print_board(GRAPH* graph, int size, int player_position, int enemy_position);

#endif