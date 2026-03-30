#ifndef IO_H
#define IO_H

#include "graph.h"
#include <stdbool.h>

// Wczytuje graf. Zapisuje ewentualny kod błędu pod wskaźnikiem err_code.
Graph* load_graph_from_file(const char *filename, int *err_code);

// Zapisuje wynik do pliku (tekstowo lub binarnie)
bool save_graph_to_file(const Graph *g, const char *filename, bool binary_mode);

#endif