#include "list.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_elements(List *l);

int main(int argc, char **argv)
{
    int n_elements = 0, i;
    FILE *f = NULL;
    List *l_orig = NULL, *l1_aux = NULL, *l2_aux = NULL, *l_rest = NULL;
    float aux = 0, *auxp = NULL;

    if (argc < 3)
    {
        fprintf(stderr, "Debe introducir: %s  <.txt> <order>", argv[0]);
        return -1;
    }

    l_orig = list_new();
    if (l_orig == NULL)
    {
        return 0;
    }

    l1_aux = list_new();
    if (l1_aux == NULL)
    {
        list_free(l_orig);
        return 0;
    }

    l2_aux = list_new();
    if (l2_aux == NULL)
    {
        list_free(l_orig);
        list_free(l1_aux);
        return 0;
    }

    l_rest = list_new();
    if (l_rest == NULL)
    {
        list_free(l_orig);
        list_free(l1_aux);
        list_free(l2_aux);
        return 0;
    }

    if (!(f = fopen(argv[1], "r")))
    {
        list_free(l_orig);
        list_free(l1_aux);
        list_free(l2_aux);
        list_free(l_rest);
        return -1;
    }

    fscanf(f, "%i", &n_elements);
    fgetc(f);
    if ((n_elements % 2) == 1)
    {
        for (i = 0; i < (n_elements / 2); i++)
        {
            fscanf(f, "%f", &aux);
            auxp = float_init(aux);
            list_pushBack(l_orig, (void *)auxp);
            fgetc(f);
            fscanf(f, "%f", &aux);
            auxp = float_init(aux);
            list_pushFront(l_orig, (void *)auxp);
            fgetc(f);
        }
        fscanf(f, "%f", &aux);
        auxp = float_init(aux);
        list_pushBack(l_orig, (void *)auxp);
    }
    else
    {
        for (i = 0; i < (n_elements / 2); i++)
        {
            fscanf(f, "%f", &aux);
            auxp = float_init(aux);
            list_pushBack(l_orig, (void *)auxp);
            fgetc(f);
            fscanf(f, "%f", &aux);
            auxp = float_init(aux);
            list_pushFront(l_orig, (void *)auxp);
            fgetc(f);
        }
    }
    fprintf(stdout, "SIZE: %li\n", list_size(l_orig));
    list_print(stdout, l_orig, float_print);

    for (i = 0; i < (n_elements / 2); i++)
    {
        auxp = (float *)list_popFront(l_orig);
        list_pushBack(l1_aux, auxp);
        list_pushFront(l_rest, auxp);
    }

    while (list_isEmpty(l_orig) == FALSE)
    {
        auxp = (float *)list_popFront(l_orig);
        list_pushFront(l2_aux, auxp);
        list_pushBack(l_rest, auxp);
    }
    fprintf(stdout, "Finished inserting. Now we extract from the beginning and insert in order:\n");
    list_print(stdout, l1_aux, float_print);
    fprintf(stdout, "Now we extract from the end and insert in order:\n");
    list_print(stdout, l2_aux, float_print);

    auxp = (float*)list_popBack(l_rest);
    if (list_pushInOrder(l_rest, auxp, float_cmp, atoi(argv[2])) == ERROR)
    {
        fclose(f);
        free_elements(l_rest);
        list_free(l_orig);
        list_free(l1_aux);
        list_free(l2_aux);
        list_free(l_rest);
        return -1;
    }

    fprintf(stdout, "SIZE: %li\n", list_size(l_rest));
    list_print(stdout, l_rest, float_print);

    fclose(f);
    free_elements(l_rest);
    list_free(l_orig);
    list_free(l1_aux);
    list_free(l2_aux);
    list_free(l_rest);
    return 0;
}

void free_elements(List *l)
{
    float *auxp = NULL;

    if (!l)
    {
        return;
    }

    while (list_isEmpty(l) == FALSE)
    {
        auxp = (float *)list_popFront(l);
        if (auxp != NULL)
        {
            free(auxp);
        }
    }
}

