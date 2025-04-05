#include "list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _NodeList
{
    void *data;
    struct _NodeList *next;
} NodeList;

struct _List
{
    NodeList *last;
};

/* PRIVATE FUNCTIONS*/
NodeList *node_new()
{
    NodeList *n = NULL;
    n = (NodeList *)malloc(sizeof(NodeList));
    if (n == NULL)
    {
        return NULL;
    }

    n->data = NULL;
    n->next = NULL;
    return n;
}
/************************************/

List *list_new()
{
    List *l = NULL;

    l = (List *)malloc(sizeof(List));
    if (l == NULL)
    {
        return NULL;
    }
    l->last = NULL;
    return l;
}

Bool list_isEmpty(const List *pl)
{
    if (pl == NULL)
    {
        return TRUE;
    }
    if (pl->last == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

Status list_pushFront(List *pl, void *e)
{
    NodeList *n = NULL;

    if ((pl == NULL) || (e == NULL))
    {
        return ERROR;
    }
    n = node_new();
    if (n == NULL)
    {
        return ERROR;
    }

    n->data = (void *)e;

    if (list_isEmpty(pl) == TRUE)
    {
        n->next = n;
        pl->last = n;
    }
    else
    {
        n->next = pl->last->next;
        pl->last->next = n;
    }

    return OK;
}

Status list_pushBack(List *pl, void *e)
{
    NodeList *n = NULL;
    if ((pl == NULL) || (e == NULL))
    {
        return ERROR;
    }
    n = node_new();
    if (n == NULL)
    {
        return ERROR;
    }
    n->data = (void *)e;
    if (list_isEmpty(pl) == TRUE)
    {
        n->next = n;
        pl->last = n;
    }
    else
    {
        n->next = pl->last->next;
        pl->last->next = n;
        pl->last = n;
    }
    return OK;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order)
{

    NodeList *current = NULL;
    void *temp;

    if (pl == NULL || e == NULL || f == NULL || order == 0)
    {
        return ERROR;
    }

    list_pushFront(pl, e);

    if (order > 0)
    {
        current = pl->last->next;
        while (current != pl->last)
        {
            if (f(current->data, current->next->data) > 0)
            {
                temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                current = pl->last->next;
            }
            else
            {
                current = current->next;
            }
        }
    }
    else
    {
        current = pl->last->next;
        while (current != pl->last)
        {
            if (f(current->data, current->next->data) < 0)
            {
                temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                current = pl->last->next;
            }
            else
            {
                current = current->next;
            }
        }
    }
    return OK;
}

void *list_popFront(List *pl)
{
    void *pe = NULL;
    NodeList *n = NULL;
    if ((pl == NULL) || (list_isEmpty(pl) == TRUE))
    {
        return NULL;
    }
    n = pl->last->next;
    pe = n->data;
    if (pl->last->next == pl->last)
    {
        pl->last = NULL;
    }
    else
    {
        pl->last->next = n->next;
    }
    free((void *)n);
    return pe;
}

void *list_popBack(List *pl)
{
    void *pe = NULL;
    NodeList *pn = NULL;
    if ((pl == NULL) || (list_isEmpty(pl) == TRUE))
    {
        return NULL;
    }
    if (pl->last->next == pl->last)
    {
        pe = pl->last->data;
        free((void *)pl->last);
        pl->last = NULL;
        return pe;
    }
    pn = pl->last;
    while (pn->next != pl->last)
    {
        pn = pn->next;
    }
    pe = pl->last->data;
    pn->next = pl->last->next;
    free((void *)pl->last);
    pl->last = pn;
    return pe;
}

void list_free(List *pl)
{
    NodeList *current;
    NodeList *next;
    if (pl == NULL)
        return;
    if (pl->last == NULL)
    {
        free(pl);
        return;
    }

    current = pl->last->next;
    
    while (current != pl->last)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(pl->last);
    free(pl);
}

size_t list_size(const List *pl)
{
    size_t i = 1;
    NodeList *current = NULL;

    if (pl == NULL || pl->last == NULL)
    {
        return 0;
    }

    current = pl->last->next;
    while (current != pl->last)
    {
        current = current->next;
        i++;
    }
    return i;
}

int list_print(FILE *fp, const List *pl, P_ele_print f)
{
    int total = 0;
    NodeList *current;

    if (pl == NULL || fp == NULL || f == NULL || list_isEmpty(pl) == TRUE)
    {
        return -1;
    }

    current = pl->last->next;

    do
    {
        total += f(fp, current->data);
        total += fprintf(fp, " ");
        current = current->next;
    } while (current != pl->last->next);
    fprintf(fp, "\n");
    return total;
}
