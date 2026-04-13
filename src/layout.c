#include "../headers/layout.h"
#include <math.h>
#include <stdio.h>
#include "../headers/utils.h"

// Do algorytmu fruchtermana reingolda
#define ITERATIONS 100       // Liczba kroków algorytmu
#define C_REP 10.0           // Stała odpychania
#define C_SPRING 1.0         // Stała przyciągania (sprężyny)
#define L_IDEAL 5.0          // Idealna długość krawędzi
#define INITIAL_TEMP 10.0    // Początkowa temperatura chłodzenia
#define COOLING_FACTOR 0.95  // Współczynnik stygnięcia (95% w każdym kroku)
                             //
// Funkcja aplikująca siłę odpychania dla pojedynczej pary wierzchołków
static void apply_repulsive_force(Vertex* u, Vertex* v, double C_rep) {
    double dx = u->x - v->x;
    double dy = u->y - v->y;
    double dist = sqrt(dx*dx + dy*dy);

    if (dist < 0.0001) dist = 0.0001; // Zabezpieczenie przed dzieleniem przez zero

    double f_rep = C_rep / (dist * dist);
    double dir_x = dx / dist;
    double dir_y = dy / dist;

    // u jest odpychane od v
    u->force_x += f_rep * dir_x;
    u->force_y += f_rep * dir_y;
    
    // v jest odpychane od u (w przeciwną stronę)
    v->force_x -= f_rep * dir_x;
    v->force_y -= f_rep * dir_y;
}

// Funkcja aplikująca siłę przyciągania (sprężyny) dla pojedynczej krawędzi
static void apply_attractive_force(Vertex* u, Vertex* v, double C_spring, double l) {
    double dx = u->x - v->x;
    double dy = u->y - v->y;
    double dist = sqrt(dx*dx + dy*dy);

    if (dist < 0.0001) dist = 0.0001;

    double f_attr = C_spring * log(dist / l);
    double dir_x = dx / dist;
    double dir_y = dy / dist;

    // u i v ciągną siebie nawzajem
    u->force_x -= f_attr * dir_x;
    u->force_y -= f_attr * dir_y;
    
    v->force_x += f_attr * dir_x;
    v->force_y += f_attr * dir_y;
}

Dict *get_id_index_dict(Graph *g) {
    Dict *dict = new_dict(g->num_vertices);
    
    // Połączenie id -> index
    for (int i = 0; i < g->num_vertices; i++) {
       add_element_dict(dict, g->vertices[i].id, i); 
    }

    return dict;
}

void apply_fruchterman_reingold(Graph *g) {
    printf("-> [STUB] Uruchamianie algorytmu Fruchtermana-Reingolda (0)...\n");
    // dodac jeszcze obliczanie sił odpychania i przyciągania
    if (!g || g->num_vertices == 0) {
        printf("-> [FR] Graf jest pusty, pomijam obliczenia.\n");
        return;
    }

    printf("-> Uruchamianie algorytmu Fruchtermana-Reingolda (0)...\n");

    double temperature = INITIAL_TEMP;

    // Główna pętla algorytmu
    for (int iter = 0; iter < ITERATIONS; iter++) {
        
        // Wyzerowanie sił z poprzedniej iteracji
        for (int i = 0; i < g->num_vertices; i++) {
            g->vertices[i].force_x = 0.0;
            g->vertices[i].force_y = 0.0;
        }

        // Aplikacja sił odpychania (każdy z każdym)
        for (int i = 0; i < g->num_vertices; i++) {
            for (int j = i + 1; j < g->num_vertices; j++) {
                apply_repulsive_force(&g->vertices[i], &g->vertices[j], C_REP);
            }
        }
        
        Dict *id_index = get_id_index_dict(g);
        // Aplikacja sił przyciągania (wzdłuż krawędzi)
        for (int e = 0; e < g->num_edges; e++) {
            // Zamieniamy id na index w tablicy g->vertices
            int u_idx = contains_dict(id_index, g->edges[e].id_A);
            int v_idx = contains_dict(id_index, g->edges[e].id_B);

            // Zabezpieczenie przed wyjściem poza tablicę, gdyby indeksy były błędne
            if (u_idx >= 0 && u_idx < g->num_vertices && 
                v_idx >= 0 && v_idx < g->num_vertices) {
                apply_attractive_force(&g->vertices[u_idx], &g->vertices[v_idx], C_SPRING, L_IDEAL);
            }
        }
        free_dict(id_index);

        // Aktualizacja pozycji z uwzględnieniem temperatury chłodzenia
        for (int i = 0; i < g->num_vertices; i++) {
            Vertex* v = &g->vertices[i];

            double force_mag = sqrt(v->force_x * v->force_x + v->force_y * v->force_y);
            
            if (force_mag > 0) {
                double step = fmin(force_mag, temperature);

                v->x += (v->force_x / force_mag) * step;
                v->y += (v->force_y / force_mag) * step;
            }
        }

        //  Zmniejszenie temperatury (Cooling schedule)
        temperature *= COOLING_FACTOR;
    }

    printf("-> Zakończono po %d iteracjach.\n", ITERATIONS);
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

