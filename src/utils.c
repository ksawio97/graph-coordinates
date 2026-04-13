#include "../headers/utils.h"
#include <stdlib.h>

void add_element_dict(Dict* d, int id, int index) {
    int dict_index = abs(id) % d->size;

    LinkList* l = d->values[dict_index];
    LinkList* n = malloc(sizeof(LinkList));
    n->id = id;
    n->index = index;
    n->next = NULL;
    if (l == NULL) {
        d->values[dict_index] = n; 
    } else {
        while (l->next != NULL) {
            l = l->next;
        }   
        d->values[dict_index]->next = n;
    }
}
// zwraca index lub -1 jak nie ma
int contains_dict(Dict *d, int id) {
    int dict_index = abs(id) % d->size;
    if (d->values[dict_index] == NULL) {
        return -1;
    }
    
    LinkList *l = d->values[dict_index];
    while (l != NULL) {
        if (l->id == id) {
            return l->index;
        }
        l = l->next;
    }
    return -1;
}

void free_dict(Dict *d) {
   for (int i = 0; i < d->size; i++) {
       LinkList *prev = NULL;
       LinkList *l = d->values[i]; 
       while (l != NULL) {
            prev = l;
            l = l->next;
            free(prev);
            prev = NULL;
       }
   }
   free(d);
}

Dict* new_dict(int size) {
    Dict* d = malloc(sizeof(Dict));
    d->size = size;
    d->values = malloc(sizeof(LinkList) * size);
    for (int i = 0; i < size; i++) {
        d->values[i] = NULL;
    }

    return d;
}
