#ifndef LIST_H
    #define LIST_H

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct list_ LIST;
    
    LIST* list_create();
    void list_delete(LIST** list);

    void list_insert(LIST* list, int id);
    void list_remove(LIST* list, int id);

    int list_size(LIST* list);
    int list_first_element(LIST* list);

    int list_next_element(LIST* list, int *current_vertex, int *next_vertex);
    
    void list_print_no(LIST* list, int index);
    void list_print(LIST* list);

#endif