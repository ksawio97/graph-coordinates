#include "../headers/layout.h"
#include <stdio.h>
#include <stdlib.h>

// funckje pomocnicze do algorytmu tuttea
static int is_boundary(int index) {
    return (index < 3); 
}

static int get_degree(Graph *g, int target_id) {
    int degree = 0;
    for (int i = 0; i < g->num_edges; i++) {
        if (g->edges[i].id_A == target_id || g->edges[i].id_B == target_id) {
            degree++;
        }
    }
    return degree;
}


void apply_fruchterman_reingold(Graph *g) {
    printf("-> [STUB] Uruchamianie algorytmu Fruchtermana-Reingolda (0)...\n");
    // dodac jeszcze obliczanie sił odpychania i przyciągania
}

void find_outside_wall(Graph *g) {

}

void apply_tutte_algorithm(Graph *g) {
    printf("-> [STUB] Uruchamianie algorytmu Tutte'a (1)...\n");
    if (g->num_vertices < 3) {
        fprintf(stderr, "Błąd: Graf musi mieć co najmniej 3 wierzchołki dla algorytmu Tutte'a.\n");
        return;
    }

    int boundary_count = 3;
    for (int i = 0; i < boundary_count; i++) {
        double angle = i * (2.0 * M_PI / boundary_count);
        g->vertices[i].x = cos(angle);
        g->vertices[i].y = sin(angle);
    }


    for (int i = boundary_count; i < g->num_vertices; i++) {
        g->vertices[i].x = 0.0;
        g->vertices[i].y = 0.0;
        
        g->vertices[i].force_x = get_degree(g, g->vertices[i].id); 
    }


    int max_iterations = 1000;
    double tolerance = 0.0001;
    double max_error;

    for (int iter = 0; iter < max_iterations; iter++) {
        max_error = 0.0;

        
        for (int i = boundary_count; i < g->num_vertices; i++) {
            double sum_x = 0.0;
            double sum_y = 0.0;
            int degree = (int)g->vertices[i].force_x; 


            for (int e = 0; e < g->num_edges; e++) {
                int neighbor_id = -1;
                if (g->edges[e].id_A == g->vertices[i].id) {
                    neighbor_id = g->edges[e].id_B;
                } else if (g->edges[e].id_B == g->vertices[i].id) {
                    neighbor_id = g->edges[e].id_A;
                }

                // Jeśli to  sąsiad to program szuka jego indeks w tablicy i dodaj jego współrzędne
                if (neighbor_id != -1) {
                    for (int j = 0; j < g->num_vertices; j++) {
                        if (g->vertices[j].id == neighbor_id) {
                            sum_x += g->vertices[j].x;
                            sum_y += g->vertices[j].y;
                            break;
                        }
                    }
                }
            }

            // Nowa pozycja to średnia pozycji sąsiadów
            double new_x = 0.0;
            double new_y = 0.0;
            if (degree > 0) {
                new_x = sum_x / degree;
                new_y = sum_y / degree;
            }

            
            double error = fabs(new_x - g->vertices[i].x) + fabs(new_y - g->vertices[i].y);
            if (error > max_error) {
                max_error = error;
            }

            
            g->vertices[i].x = new_x;
            g->vertices[i].y = new_y;
        }

        
        if (max_error < tolerance) {
            printf("Algorytm Tutte'a zakończył się po %d iteracjach.\n", iter);
            break;
        }
    }
}

