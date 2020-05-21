#include "list.h"

typedef struct no_ NO;

struct no_ {
    int id;
    NO* next;
};

struct list_ {
    int size;
    NO* head;
    NO* foot;
};

NO* no_create(int id) {
    NO* no = (NO *) malloc (sizeof(NO));
    if(no != NULL) {
        no->id = id;
        no->next = NULL;
    }
    return no;
}

LIST* list_create() {
    LIST* list;
    list = (LIST *) malloc(sizeof(LIST));
    if(list != NULL) {
        list->size = 0;
        list->head = no_create(-1);
        list->foot = list->head;
    }
    return list;
}

void list_delete(LIST** list) {
    NO* current = (*list)->head;
    NO* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*list);
    list = NULL;
    return;
}

void list_insert(LIST* list, int id) {
    if(list != NULL) {
        NO* aux = list->head->next;
        while(aux != NULL) {
            if(aux->id == id) return;
            aux = aux->next;
        }
        NO* new = no_create(id);
        list->foot->next = new;
        list->foot = new;
        list->size++;
    }
    return;
}

void list_remove(LIST* list, int id) {
    if(list != NULL) {
        NO* previous = list->head;
        NO* current = list->head->next;
        while(current != NULL && current->id != id) {
            previous = current;
            current = current->next;
        }
        if(current != NULL) {
            if(current == list->foot) list->foot = previous;
            previous->next = current->next;
            free(current);
            list->size--;
        }

    }
    return;
}

void list_print_no(LIST* list, int id) {
    if(list != NULL) {
        NO* aux = list->head->next;
        while(aux != NULL && aux->id != id) aux = aux->next;
        if(aux != NULL)  printf("%d", aux->id);
    }
}

int list_first_element(LIST* list) {
    if(list != NULL) {
        if(list->head->next != NULL) return list->head->next->id;
    }
    return -1;
}

int list_next_element(LIST* list, int *current_vertex, int *next_vertex) {
    if(list != NULL) {
        NO* aux = list->head->next;
        *current_vertex = *next_vertex;

        while(aux != NULL && aux->id != (*current_vertex)) aux = aux->next;
        
        if(aux != NULL) {
            if(aux->next != NULL) {
                *next_vertex = aux->next->id;
                return 0; //It's not the end of the list
            }
        }
        return 1; //The end of the list
    }
}

int list_size(LIST* list) {
    if(list != NULL) {
        return list->size;
    }
}

void list_print(LIST* list) {
    if(list != NULL) {
        int i;
        NO* aux = list->head->next;
        while(aux != NULL) {
            printf("%d ", aux->id);
            aux = aux->next;
        }
        printf("\n");       
    }
    return;
}