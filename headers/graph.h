#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

// Reprezentacja pojedynczego wierzchołka
typedef struct {
    int id;
    double x;
    double y;
    double force_x; 
    double force_y;
} Vertex;

// Reprezentacja krawędzi (zgodnie z formatem: Nazwa A B Waga)
typedef struct {
    char name[32];
    // TO DELETE
    int id_A;
    int id_B;
    // END
    int index_A;
    int index_B;
    double weight;
} Edge;

// Główna struktura grafu
typedef struct {
    Vertex *vertices;
    int num_vertices;
    int capacity_vertices; 
    
    Edge *edges;
    int num_edges;
    int capacity_edges;
} Graph;

#endif
