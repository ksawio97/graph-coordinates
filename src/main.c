#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // Do getopt

#include "../headers/graph.h"
#include "../headers/io.h"
#include "../headers/layout.h"

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;
    int algorithm = 0; // Domyślnie 0
    bool binary_output = false;
    int opt;
    
    // Parsowanie flag
    while ((opt = getopt(argc, argv, "i:o:a:bh")) != -1) {
        switch (opt) {
            case 'i': input_file = optarg; break;
            case 'o': output_file = optarg; break;
            case 'a': algorithm = atoi(optarg); break;
            case 'b': binary_output = true; break;
            case 'h':
                printf("Użycie: %s -i <plik_wejsciowy> -o <plik_wyjsciowy> [-a 0|1] [-b]\n", argv[0]);
                return 0;
            case '?': 
            default:
                fprintf(stderr, "Błąd: Niewłaściwa wartość argumentu.\n");
                return 4; 
        }
    }

    // Kod 1 - Brak wymaganych argumentów
    if (!input_file || !output_file) {
        fprintf(stderr, "Błąd: Nie podano pliku wejściowego lub wyjściowego.\n");
        return 1; 
    }

    // Kod 4 - Walidacja numeru algorytmu
    if (algorithm != 0 && algorithm != 1) {
        fprintf(stderr, "Błąd: Niewłaściwa wartość argumentu (nieznany algorytm).\n");
        return 4;
    }

    printf("Rozpoczęcie pracy programu...\n");
    printf("Wejście: %s | Wyjście: %s | Algorytm: %d\n", input_file, output_file, algorithm);

    // Wczytywanie grafu
    int io_error_code = 0;
    Graph *g = load_graph_from_file(input_file, &io_error_code);
    

    if (!g) {
        return io_error_code; 
    }

    // uruchomienie wybranego algorytmu
    if (algorithm == 0) {
        apply_fruchterman_reingold(g);
    } else {
        apply_tutte_algorithm(g);
    }

    // zapis grafu do pliku
    if (!save_graph_to_file(g, output_file, binary_output)) {
        free(g);
        return 2; 
    }

    // Sprzątanie pamięci
    free(g);
    printf("Zakończono pomyślnie.\n");

    return 0;
}
