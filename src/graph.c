#include "../headers/graph.h"
#include <float.h>
#include <stdlib.h>

Vertex *create_vertex(int id) {
    Vertex *v = malloc(sizeof(Vertex));
    v->force_x = 0;
    v->force_y = 0;
    v->id = id;
    // losowa pozycja dla każdego vertex w obszarze 10x10
    v->x = (double)rand() / (double)RAND_MAX * 10;
    v->y = (double)rand() / (double)RAND_MAX * 10;
    return v;
}

Edge *create_edge() {
    Edge *e = malloc(sizeof(Edge));
    e->id_A = 0;
    e->id_B = 0;
    e->weight = 0;
    return e;
}


void free_graph(Graph *g) {
    for (int i = 0; i < g->num_edges; i++) {
        free(g->edges[i]);
    }

    for (int i = 0; i < g->num_vertices; i++) {
        free(g->vertices[i]);
    }

    free(g);
}
