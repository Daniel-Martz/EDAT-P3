#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"


#define MAX_SIZE 100

int main(int argc, char **argv){
    Graph *graph = NULL;
    long from , to;
    FILE *f = NULL;
    

    if (argc < 4)
    {
        fprintf(stderr, "Debe introducir: %s  <.txt> <Id origen> <Id llegada>", argv[0]);
        return -1;
    }

    from = atoi(argv[2]);
    to = atoi(argv[3]);

    if(!(graph = graph_init())) return -1;

    if(!(f = fopen(argv[1], "r"))){
        graph_free(graph);
        return -1;
    }

    if(graph_readFromFile(f, graph) == ERROR){
        return -1;
    }

    fprintf(stdout, "Input graph:\n");
    graph_print(stdout, graph);

    fprintf(stdout, "--------DFS------------\n");
    fprintf(stdout, "From Vertex id: %ld\n",from);
    fprintf(stdout, "To Vertex id: %ld\n",to);
    fprintf(stdout, "Output:\n");
    if(graph_depthSearch(graph, from, to) == ERROR){
        return -1;
    }

    fprintf(stdout, "--------BFS------------\n");
    fprintf(stdout, "From Vertex id: %ld\n",from);
    fprintf(stdout, "To Vertex id: %ld\n",to);
    fprintf(stdout, "Output:\n");
    if(graph_breathSearch(graph, from, to) == ERROR){
        return -1;
    }

    graph_free(graph);
    fclose(f);

    return 0;
}
