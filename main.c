#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list.h"
#include "algorithms.h"

int main(void) {
    GRAPH* graph;
    int i;
    int size, number_of_vertices;
    int next_position;
    int enemy_position, player_position;
    int *distancy;

    printf("Enter the number that will represent the height and width of the board (number * number): ");
    scanf("%d", &size);
    number_of_vertices = size * size;
    graph = graph_create(number_of_vertices);

    for(i = 0; i < number_of_vertices; i++) {
        //Neste caso, são os da lateral esquerda do tabuleiro
        if(i % size == 0) {
            graph_insert(graph, i, i+1); //Direita

            //Em cima
            if(i-size >= 0) graph_insert(graph, i, i-size);          
        
            //O valor da cédula abaixo deve ser menor que o número de vértices, pois se não saiu do tabuleiro
            if(i+size < (number_of_vertices)) graph_insert(graph, i, i+size); //Embaixo
            continue;
        }
        //Neste caso, são os da lateral direita do tabuleiro
        if(i % size == (size-1)) {
            graph_insert(graph, i, i-1); //Esquerda

            //Em cima
            if(i-size >= 0) graph_insert(graph, i, i-size); 

            //O valor da cédula abaixo deve ser menor que o número de vértices, pois se não saiu do tabuleiro
            if(i+size < (number_of_vertices)) graph_insert(graph, i, i+size); //Embaixo
            continue;
        }

        //Em cima
        next_position = i-size;
        //Se for maior que 0, está dentro do tabuleiro, se não, saiu para cima
        if(next_position >= 0) graph_insert(graph, i, next_position);

        //A direita
        next_position = i+1;
        //Aqui não é necessária validação, pois todos os vértices laterais não chegam aqui, são executados 
        //No if acima. Logo, temos garantia que a lateral dessa posição existe
        graph_insert(graph, i, next_position);

        //Em baixo
        next_position = i+size;
        //O valor da cédula abaixo deve ser menor que o número de vértices, pois se não saiu do tabuleiro por baixo
        if(next_position < number_of_vertices) graph_insert(graph, i, next_position);

        //A esquerda
        next_position = i-1;
        //Aqui não é necessária validação, pois todos os vértices laterais não chegam aqui, são executados 
        //No if acima. Logo, temos garantia que a lateral dessa posição existe
        graph_insert(graph, i, next_position);
    }

    printf("Player position: ");
    scanf("%d", &player_position);

    if(player_position >= number_of_vertices || player_position < 0) {
        printf("Invalid position.\n");
        return 0;
    }

    printf("Enemy position: ");
    scanf("%d", &enemy_position);

    if(enemy_position >= number_of_vertices || player_position < 0) {
        printf("Invalid position.\n");
        return 0;
    }

    print_board(graph, size, player_position, enemy_position);

    printf("\n");

    //Esse vetor irá marcar a distância de cada bloco do tabuleiro a partir da posição do inimigo
    distancy = (int*) malloc (sizeof(int) * number_of_vertices);
    bfs(graph, enemy_position, distancy);

    wavefront(graph, size, player_position, distancy);
    
    printf("\n");
    free(distancy);
    graph_delete(&graph);

    return 0;
}

