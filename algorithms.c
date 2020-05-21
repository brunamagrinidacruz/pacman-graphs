#include "algorithms.h"

typedef enum {
    white, grey, black
} colors;

void print_board(GRAPH* graph, int size, int player_position, int enemy_position) {
    int i, j, k;
    int position = 0;

    printf("\n");
    printf("+");
    for(k = 0; k < size; k++)
        printf("-----");

    for(i = 0; i < size; i++) {
        printf("\n| ");
        for(j = 0; j < size; j++) {
            if(player_position == position) 
                printf("PN | ");
            else if(enemy_position == position)
                printf("EN | ");
            else if(position < 10)
                printf("0%d | " , position);
            else 
                printf("%d | " , position);
            position++;
        }
        printf("\n");
        printf("+");
        for(k = 0; k < size; k++)
            printf("-----");
    }
}

void execute_bfs(GRAPH* graph, int vertex, int distancy[], colors color[]) {
    //Creating a queue that will stored the adjacents vertex in sequence of visited. 
    //The BFS will be execute to all vertex inside the queue
    QUEUE* queue;
    queue = queue_create();

    //Initializing vertex as grey (visited)
    color[vertex] = grey;
    //Because this vertex is the initial vertex, distancy = 0
    distancy[vertex] = 0;

    queue_insert(queue, vertex);

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
                    queue_insert(queue, current_vertex);
                }
            }
        }
        //When all vertices in adjacency list are executed (or if there is no adjacency vertext)
        color[initial_vertex] = black;
    }
    queue_delete(&queue);
}

void bfs(GRAPH* graph, int enemy_position, int distancy[]) {
    int i;
    int vertex;
    int number_of_vertices = graph_number_of_vertices(graph);
    colors *color = (colors*) malloc (sizeof(colors) * number_of_vertices);

    //Initializing
    //color: as white because any vertex was visited
    //distancy: as -1 because any vertex had its distancy calculeted
    //ancestor: as -1 because any vertex has a ancestor yet
    for(i = 0; i < number_of_vertices; i++) {
        color[i] = white;
        distancy[i] = -1;
    }

    //Por ser um tabuleiro, é possível chegar em todos os vértices
    //A partir de qualquer vértices, por isso é executado apenas uma vez
    execute_bfs(graph, enemy_position, distancy, color);
    
    free(color);
}

void wavefront(GRAPH* graph, int size, int player_position, int distancy[]) {
    if(graph != NULL) {

        //O personagem chegou ao inimigo
        if(distancy[player_position] == 0) {
            printf("The player finded the enemy in position %d!", player_position);
            return;
        }

        printf("Player is in %d\n", player_position);

        int number_of_vertices = graph_number_of_vertices(graph);
        int analyzed_position, player_next_position; 
        int min_distancy = -1;

        //Neste caso, são os da lateral esquerda do tabuleiro
        if(player_position % size == 0) {
            analyzed_position = player_position+1; //Direita
            min_distancy = distancy[analyzed_position]; 
            player_next_position = analyzed_position;

            analyzed_position = player_position-size;  //Em cima
            if(analyzed_position >= 0)             
                if(distancy[analyzed_position] < min_distancy) {
                    min_distancy = distancy[analyzed_position]; 
                    player_next_position = analyzed_position;
                }    

            analyzed_position = player_position+size; //Embaixo
            if(analyzed_position < number_of_vertices) 
                //Se a distância da posição abaixo até o inimigo for menor que o da posição a direita, esse é o vértice no qual devemos ir
                if(distancy[analyzed_position] < min_distancy) {
                    min_distancy = distancy[analyzed_position]; 
                    player_next_position = analyzed_position;
                }
            
            wavefront(graph, size, player_next_position, distancy);
            return;
        }

        //Neste caso, são os da lateral direita do tabuleiro
        if(player_position % size == (size-1)) {
            analyzed_position = player_position-1; //Esquerda
            min_distancy = distancy[analyzed_position]; 
            player_next_position = analyzed_position;

            analyzed_position = player_position-size;  //Em cima
            if(analyzed_position >= 0)             
                if(distancy[analyzed_position] < min_distancy) {
                    min_distancy = distancy[analyzed_position]; 
                    player_next_position = analyzed_position;
                }    

            analyzed_position = player_position+size; //Embaixo
            if(analyzed_position < number_of_vertices) 
                //Se a distância da posição abaixo até o inimigo for menor que o da posição a esquerda, esse é o vértice no qual devemos ir
                if(distancy[analyzed_position] < min_distancy) {
                    min_distancy = distancy[analyzed_position]; 
                    player_next_position = analyzed_position;
                }

            wavefront(graph, size, player_next_position, distancy);
            return;
        }

        //Inicializamos com o valor a direita pois sempre temos garantia que esse bloco existe para esse conjunto de vértices
        analyzed_position = player_position+1; //Direita
        min_distancy = distancy[analyzed_position];
        player_next_position = analyzed_position;

        analyzed_position = player_position+size; //Em baixo
        if(analyzed_position < number_of_vertices) 
            if(distancy[analyzed_position] < min_distancy) {
                min_distancy = distancy[analyzed_position]; 
                player_next_position = analyzed_position;
            }

        analyzed_position = player_position-1; //A esquerda
        if(distancy[analyzed_position] < min_distancy) {
            min_distancy = distancy[analyzed_position]; 
            player_next_position = analyzed_position;
        }

        analyzed_position = player_position-size;  //Em cima
        if(analyzed_position >= 0)             
            if(distancy[analyzed_position] < min_distancy) {
                min_distancy = distancy[analyzed_position]; 
                player_next_position = analyzed_position;
        }

        wavefront(graph, size, player_next_position, distancy);
        return;
    }
}