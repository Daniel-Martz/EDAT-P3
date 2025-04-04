#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_QUEUE 100

/* Private function */

Bool queue_is_full(const Queue *pq);

/***************************************/
struct _Queue{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new(void){
    Queue *q = NULL;
    int i;

    if(!(q =(Queue *)calloc(1, sizeof(Queue)))){
        return NULL;
    }

    for(i = 0; i<MAX_QUEUE; i++){
        q->data[i] = NULL;
    }

    q->front = &(q->data[0]);
    q->rear = &(q->data[0]);
    return q;
}

void queue_free(Queue *q){
    free(q);
}

Bool queue_isEmpty(const Queue *q){
    if (!q){
        return TRUE;
    }
    if (q->front == q->rear){
        return TRUE; 
    }
    return FALSE; 
}

Status queue_push(Queue *q, void *ele){
    if((!q) || (!ele) || (queue_is_full(q) == TRUE)){
        return ERROR;
    }
    *(q->rear) = ele;
    q->rear = q->data + ((q->rear + 1 - q->data) % MAX_QUEUE);

    return OK;
}

void *queue_pop(Queue *q){
    void *ele = NULL;
    if ((!q) || (queue_isEmpty(q) == TRUE)){
        return NULL; 
    }

    ele = *(q->front);
    q->front = q->data + ((q->front + 1 - q->data) % MAX_QUEUE);

    return (void*)ele;
}

void *queue_getFront(const Queue *q){
    if ((!q) || (queue_isEmpty(q) == TRUE)) {
        return NULL; 
    }
    return *(q->front); 
}

void *queue_getBack(const Queue *q){
    if ((!q) || (queue_isEmpty(q) == TRUE)) {
        return NULL; 
    }
    if (q->rear == q->data) {
        return (void*)*(q->data + MAX_QUEUE - 1);
    } 
    else {
        return (void*)*(q->rear - 1); 
    }
}

size_t queue_size(const Queue *q){
    if(!q){
        return 0;
    }

    if(q->rear >= q->front){
        return q->rear - q->front;
    }

    return MAX_QUEUE - (q->front - q->rear);
}

/**
 * @brief  This function prints the queue content to an output stream.
 * 
 * @param fp A pointer to the stream.
 * @param q A pointer to the queue to be printed. 
 * @param f A pointer to the function that must be used to print the queue elements.
 *
 * @return On success this function returns the number of characters printed. In 
 * case of error it returns a negative value.
 *  */
int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
    int counter = 0;
    int i;

    if((!fp) || (!q) || (!f)){
        return -1;
    }
    
    for(i=0; i<queue_size(q); i++){
        counter += f(stdout, (void*) *(q->data + ((q->front +i -q->data) % MAX_QUEUE)));
    }

    return counter;
}


Bool queue_is_full(const Queue *pq){ 
    if (!pq){
        return FALSE; 
    }

    if ((pq->rear + 1 - pq->front) % MAX_QUEUE == 0){
    return TRUE;
    }

    return FALSE; 
}
