#include "../headers/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utils.h"
#include "../headers/graph.h"

#define DICT_SIZE 50

void read_data(FILE* fh, Graph* g) {
    Dict *d = new_dict(DICT_SIZE);
    Edge *e = create_edge();
    // read edge
    while (fscanf(fh, "%s %d %d %lf", e->name, &(e->id_A), &(e->id_B), &(e->weight)) == 4) {
        // check if they are new vertices
        bool has_A = contains_dict(d, e->id_A) != -1, has_B = contains_dict(d, e->id_B) != -1;
        // extend size if needed 
        if (!has_A) g->num_vertices++;
        if (!has_B) g->num_vertices++;
        g->num_edges++;

        // extend capacity if needed
        if (g->capacity_vertices < g->num_vertices) {
            int old_cap = g->capacity_vertices;
            g->capacity_vertices *= 2;
            g->vertices = realloc(g->vertices, sizeof(Vertex*) * g->capacity_vertices);
            for (int i = old_cap; i < g->capacity_vertices; i++) 
                g->vertices[i] = NULL;
        }


        // ditto but for edges
        if (g->capacity_edges < g->num_edges) {
            int old_cap = g->capacity_edges;
            g->capacity_edges *= 2;
            g->edges = realloc(g->edges, sizeof(Edge*) * g->capacity_edges);
            for (int i = old_cap; i < g->capacity_edges; i++) 
                g->edges[i] = NULL;
        }

        if (!has_B) {
            g->vertices[g->num_vertices - 1] = create_vertex(e->id_B);  
            add_element_dict(d, e->id_B, g->num_vertices - 1);
        }

        if (!has_A) {
            int ver_index = g->num_vertices - 1 - (has_B ? 0 : 1);
            g->vertices[ver_index] = create_vertex(e->id_A);

            add_element_dict(d, e->id_A, ver_index);
        }
        g->edges[g->num_edges - 1] = e;
        e = create_edge();
    }
    free(e);
    free_dict(d);
}

Graph* load_graph_from_file(const char *filename, int *err_code) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Błąd: Nie można otworzyć pliku wejściowego.\n");
        *err_code = 2; // Kod 2 - Błąd odczytu pliku
        return NULL;
    }

    Graph *g = malloc(sizeof(Graph)); 
    if (!g) {
        fprintf(stderr, "Błąd krytyczny: Brak pamięci do zaalokowania grafu.\n");
        fclose(file);
        *err_code = 5; // Kod 5 - Błąd alokacji pamięci
        return NULL;
    }
    g->num_vertices = 0;
    g->num_edges = 0;
    
    g->capacity_edges = 1;
    g->capacity_vertices = 1;
    g->edges = malloc(sizeof(Edge*));
    g->vertices = malloc(sizeof(Vertex*));
    //dodac dynamiczne dodoawanie woerzcholkow itp.
    read_data(file, g);


    fclose(file);
    *err_code = 0; // Sukces
    return g; 
}

// dodac zapis
bool save_graph_to_file(const Graph *g, const char *filename, bool binary_mode) {
    
    printf("-> [STUB] Zapisuje graf do pliku: %s (Tryb binarny: %s)\n", 
            filename, binary_mode ? "TAK" : "NIE");
    FILE *file = fopen(filename, binary_mode ? "wb" : "w");
    if (file == NULL) {
        fprintf(stderr, "Błąd: Nie można wpisać danych wyjściowych do pliku: %s.\n", filename);
        return NULL;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        Vertex *v = g->vertices[i];
        if (binary_mode) {
            fwrite(&v->id, sizeof(int), 1, file);
            fwrite(&v->x, sizeof(double), 1, file);
            fwrite(&v->y, sizeof(double), 1, file);
        } else {
            fprintf(file, "%d %lf %lf\n", v->id, v->x, v->y);
        }
    }


    fclose(file);
    return true;
}
