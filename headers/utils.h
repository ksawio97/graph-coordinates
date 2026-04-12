#ifndef UTILS_H
#define UTILS_H

typedef struct LinkListStr {
    int id;
    int order;
    struct LinkListStr* next;    
} LinkList;

typedef struct SetStr {
    int size;
    LinkList** values;
} Set;


void add_element_set(Set *s, int id, int order);
int contains_set(Set *s, int id);
void free_set(Set *s);
Set* new_set(int size);

#endif
