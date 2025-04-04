#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 2 /* init stack capacity*/
#define FCT_CAPACITY 2  /* multiply the stack capacity*/

struct _Stack
{
    void **item;  /*!<Static array of elements*/
    int top;      /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};


Stack *stack_init()
{
    Stack *s = NULL;
    int i = 0;

    if (!(s = (Stack *)calloc(1, sizeof(Stack))))
    {
        return NULL;
    }

    if (!(s->item = (void **)calloc(INIT_CAPACITY, sizeof(void *))))
    {
        free(s);
        return NULL;
    }
    for (i = 0; i < INIT_CAPACITY; i++)
    {
        s->item[i] = NULL;
    }
    s->top = 0;
    s->capacity = INIT_CAPACITY;

    return s;
}

void stack_free(Stack *s)
{   
    free((void*)s);
}

Status stack_push(Stack *s, const void *ele) {
    int i;
    int new_capacity = 0;
    void **new_items = NULL;

    if (s == NULL || ele == NULL) {
        return ERROR;
    }

    if (s->top == s->capacity - 1) {
        new_capacity = s->capacity * FCT_CAPACITY;
        new_items = realloc(s->item, new_capacity * sizeof(void *));
        
        if (new_items == NULL) {
            return ERROR; 
        }
        
        for (i = s->capacity; i < new_capacity; i++) {
            new_items[i] = NULL;
        }
        
        s->item = new_items;
        s->capacity = new_capacity;
    }
    
    s->top++;
    s->item[s->top] = (void *)ele;
    
    return OK;
}

void *stack_pop(Stack *s)
{
    void *e = NULL;
    if (!s)
        return NULL;
    if(stack_isEmpty(s) == TRUE){
        return NULL;
    }

    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;
    return (void *)e;
}

void *stack_top(const Stack *s)
{
    if (!s)
        return NULL;

    return (void *)s->item[s->top];
}

Bool stack_isEmpty(const Stack *s)
{
    if (!s)
    {
        return TRUE;
    }
    if (s->top == 0)
        return TRUE;

    return FALSE;
}

size_t stack_size(const Stack *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->top + 1;
}


int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f) {
    int total = 0;
    int i;

    if (!fp || !s || !f) return -1;

    for (i = 0; i <= s->top; i++) {  
        total += f(fp, s->item[i]);
    }
    
    return total;
}

