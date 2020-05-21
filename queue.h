#ifndef QUEUE_H
    #define QUEUE_H

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct queue_ QUEUE;
    
    QUEUE* queue_create();
    void queue_delete(QUEUE** queue);

    void queue_insert(QUEUE* queue, int id);
    int queue_remove(QUEUE* queue);
    
    int queue_is_empty(QUEUE* queue);
    
    void queue_print(QUEUE* queue);

#endif