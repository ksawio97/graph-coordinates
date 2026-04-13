#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>

void add_element_set(Set *s, int id, int order) {
    LinkList* l = s->values[id % s->size];
    LinkList* n = malloc(sizeof(LinkList));
    n->id = id;
    n->order = order;
    n->next = NULL;
    if (l == NULL) {
        s->values[id % s->size] = n; 
    } else {
        while (l->next != NULL) {
            l = l->next;
        }   
        s->values[id % s->size]->next = n;
    }
}
// zwraca order lub -1 jak nie ma
int contains_set(Set *s, int id) {
    int index = id % s->size;
    if (s->values[index] == NULL) {
        return -1;
    }
    
    LinkList *l = s->values[index];
    while (l != NULL) {
        if (l->id == id) {
            return l->order;
        }
        l = l->next;
    }
    return -1;
}

void free_set(Set *s) {
   for (int i = 0; i < s->size; i++) {
       LinkList *prev = NULL;
       LinkList *l = s->values[i]; 
       while (l != NULL) {
            prev = l;
            l = l->next;
            free(prev);
            prev = NULL;
       }
   }
   free(s);
}

Set* new_set(int size) {
    Set* s = malloc(sizeof(Set));
    s->size = size;
    s->values = malloc(sizeof(LinkList) * size);
    for (int i = 0; i < size; i++) {
        s->values[i] = NULL;
    }

    return s;
}
