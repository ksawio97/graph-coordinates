#ifndef UTILS_H
#define UTILS_H

typedef struct LinkListStr {
    int id;
    int index;
    struct LinkListStr* next;    
} LinkList;

typedef struct DictStr {
    int size;
    LinkList** values;
} Dict;


void add_element_dict(Dict *d, int id, int index);
int contains_dict(Dict *d, int id);
void free_dict(Dict *d);
Dict* new_dict(int size);

#endif
