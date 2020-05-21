#include "queue.h"

typedef struct no_ NO;

struct no_ {
    int id;
    NO* next;
};

struct queue_ {
    int size;
    NO* head;
    NO* foot;
};

NO* queue_no_create(int id) {
    NO* no = (NO *) malloc (sizeof(NO));
    if(no != NULL) {
        no->id = id;
        no->next = NULL;
    }
    return no;
}

QUEUE* queue_create() {
    QUEUE* queue;
    queue = (QUEUE *) malloc(sizeof(QUEUE));
    if(queue != NULL) {
        queue->size = 0;
        queue->head = queue_no_create(-1);
        queue->foot = queue->head;
    }
    return queue;
}

void queue_delete(QUEUE** queue) {
    NO* current = (*queue)->head;
    NO* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*queue);
    queue = NULL;
    return;
}

void queue_insert(QUEUE* queue, int id) {
    if(queue != NULL) {
        NO* new = queue_no_create(id);
        queue->foot->next = new;
        queue->foot = new;
        queue->size++;
    }
    return;
}

int queue_remove(QUEUE* queue) {
    int id = -1;
    if(queue != NULL) {
        NO* no = queue->head->next;
        if(no != NULL) {
            id = no->id;
            if(queue->foot == no) queue->foot = queue->head;
            queue->head->next = no->next;
            free(no);
            queue->size--;
        }
    }
    return id;
}

int queue_is_empty(QUEUE* queue) {
    return queue->size == 0;
}

void queue_print(QUEUE* queue) {
    if(queue != NULL) {
        int i;
        NO* aux = queue->head->next;
        while(aux != NULL) {
            printf("%d ", aux->id);
            aux = aux->next;
        }
        printf("\n");       
    }
    return;
}