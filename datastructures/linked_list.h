#include "shapes.h"

#ifndef PROJETC_LINKED_LIST_H
#define PROJETC_LINKED_LIST_H

#endif //PROJETC_LINKED_LIST_H

typedef struct LListElement {
    Shape *data;
    struct LListElement *previous;
    struct LListElement *next;
} LListElement;

typedef struct LList {
    LListElement *first;
    LListElement *last;
} LList;
