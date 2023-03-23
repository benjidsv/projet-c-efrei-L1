#include "shapes.h"

#ifndef PROJETC_LINKED_LIST_H
#define PROJETC_LINKED_LIST_H

#endif //PROJETC_LINKED_LIST_H

typedef struct ShapeLinkedList{
    Shape *element;
    struct ShapeLinkedList *next;
} ShapeLinkedList;
