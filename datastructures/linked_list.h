#include "shapes.h"

#ifndef PROJETC_LINKED_LIST_H
#define PROJETC_LINKED_LIST_H

#endif //PROJETC_LINKED_LIST_H

typedef struct ShapeLListElement {
    Shape *data;
    struct ShapeLListElement *previous;
    struct ShapeLListElement *next;
} ShapeLListElement;

typedef struct ShapeLList {
    ShapeLListElement *first;
    ShapeLListElement *last;
} ShapeLList;

typedef struct UIntLListElement {
    unsigned int data;
    struct UIntLListElement *previous;
    struct UIntLListElement *next;
} UIntLListElement;

typedef struct IntLList {
    UIntLListElement *first;
    UIntLListElement *last;
} UIntLList;
