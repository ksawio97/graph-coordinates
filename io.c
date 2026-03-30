#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    //dodac dynamiczne dodoawanie woerzcholkow itp.

    fclose(file);
    *err_code = 0; // Sukces
    return g; 
}

// dodac zapis
bool save_graph_to_file(const Graph *g, const char *filename, bool binary_mode) {
    
    printf("-> [STUB] Zapisuje graf do pliku: %s (Tryb binarny: %s)\n", 
            filename, binary_mode ? "TAK" : "NIE");
    return true;
}