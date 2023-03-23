#include "shapes.h"
#include <stdlib.h>
#include <stdio.h>

Point *MakePoint(int x, int y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;

    return p;
}

Shape *MakePointShape(int x, int y) {
    Shape *s = malloc(sizeof(Shape));
    s->type = POINT;
    s->shape = MakePoint(x, y);

    return s;
}

void DeletePoint(Point *p) {
    free(p);
}

void PrintPoint(Point *p) {
    printf("POINT %d %d", p->x, p->y);
}

Line *MakeLine(Point *start, Point *end) {
    Line *l = malloc(sizeof(Line));
    l->start = start;
    l->end = end;

    return l;
}

Shape *MakeLineShape(Point *start, Point *end) {
    Shape *s = malloc(sizeof(Shape));
    s->type = LINE;
    s->shape = MakeLine(start, end);
}

void DeleteLine(Line *l) {
    DeletePoint(l->start);
    DeletePoint(l->end);
    free(l);
}
void PrintLine(Line *l) {
    printf("LINE %d %d %d %d", l->start->x, l->start->y, l->end->x, l->end->y);
}
