#include "algorithms.h"

typedef enum {
    white, grey, black
} colors;

void print_board(GRAPH* graph, int size, int player_position, int enemy_position) {
    if(size > 10) {
        printf("The board is too big to be printed.");
        return;
    }

    int i, j, k;
    int position = 0;

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
    //Criando uma fila que irá armazenar os vértices na sequência que foram visitados
    QUEUE* queue;
    queue = queue_create();

    //Marcando o vértice como cinza (visitado)
    color[vertex] = grey;
    //Como é o primeiro vértice, a distância = 0
    distancy[vertex] = 0;

    queue_insert(queue, vertex);

    int current_vertex = -1, next_vertex = -1;

    //Enquanto a fila não está vazia, há vértices para serem visitados
    while(!queue_is_empty(queue)) {
        int initial_vertex = queue_remove(queue);
        //Verificando se ainda há vértices na lista de adjacência
        if(!graph_is_adjacency_list_empty(graph, initial_vertex)) {
            int first_vertex_list_adjacency = graph_first_vertex_list_adjacency(graph, initial_vertex);
            int is_end_vertex_list_adjacency = 0;
            //Nós inicializamos o next_vertex como o primeiro vértice da lista
            //Isso porque a função graph_next_vertex_list_adjancency irá colocar o next_vertex dentro de current_vertex
            next_vertex = first_vertex_list_adjacency;
            //Enquanto a lista de adjacência não acabou, continua percorrendo
            while(!is_end_vertex_list_adjacency) {
                //Essa função irá colocar em current_vertex o id do vértice que estamos analisando
                //E next_vertex será o valor do próximo vértices da lista de adjacência
                is_end_vertex_list_adjacency = graph_next_vertex_list_adjacency(graph, initial_vertex, &current_vertex, &next_vertex);
                if(color[current_vertex] == white) {
                    //Foi visitado então deve entrar na fila
                    color[current_vertex] = grey;
                    distancy[current_vertex] = distancy[initial_vertex] + 1;
                    queue_insert(queue, current_vertex);
                }
            }
        }
        //Quando todos os vértices adjacentes são executados, ou se não há vértices adjacentes, define como preto (processado)
        color[initial_vertex] = black;
    }
    queue_delete(&queue);
}

void bfs(GRAPH* graph, int enemy_position, int distancy[]) {
    int i;
    int vertex;
    int number_of_vertices = graph_number_of_vertices(graph);
    colors *color = (colors*) malloc (sizeof(colors) * number_of_vertices);

    //Inicializando as cores do vértice em branco
    for(i = 0; i < number_of_vertices; i++) {
        color[i] = white;
        distancy[i] = -1;
    }

    //Por ser um tabuleiro, é possível chegar em todos os vértices
    //A partir de qualquer vértices, por isso é executado apenas uma vez
    execute_bfs(graph, enemy_position, distancy, color);
    
    free(color);
}

void wavefront(GRAPH* graph, int size, int player_position, int distancy[], int* displacement) {
    if(graph != NULL) {

        //O personagem chegou ao inimigo
        if(distancy[player_position] == 0) {
            printf("The player displaced %d blocks and finded the enemy in position %d!", displacement[0], player_position);
            return;
        }

        printf("Player is in %d\n", player_position);

        (*displacement)++;
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
            
            wavefront(graph, size, player_next_position, distancy, displacement);
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

            wavefront(graph, size, player_next_position, distancy, displacement);
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

        wavefront(graph, size, player_next_position, distancy, displacement);
        return;
    }
}