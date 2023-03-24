#include "shapes.h"
#include <stdlib.h>
#include <stdio.h>

//region Point
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
    s->id = 0;

    return s;
}

void DeletePoint(Point *p) {
    free(p);
}

void PrintPoint(Point *p) {
    printf("POINT %d %d", p->x, p->y);
}
//endregion

//region Ligne
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
    s->id = 0;

    return s;
}

void DeleteLine(Line *l) {
    DeletePoint(l->start);
    DeletePoint(l->end);
    free(l);
}
void PrintLine(Line *l) {
    printf("LINE %d %d %d %d", l->start->x, l->start->y, l->end->x, l->end->y);
}
//endregion

//region Carré
Square *MakeSquare(Point *topLeft, int length) {
    Square *s = malloc(sizeof(Square));
    s->topLeft = topLeft;
    s->length = length;

    return s;
}

Shape *MakeSquareShape(Point *topLeft, int length) {
    Shape *s = malloc(sizeof(Shape));
    s->type = SQUARE;
    s->shape = MakeSquare(topLeft, length);
    s->id = 0;

    return s;
}

void DeleteSquare(Square *s) {
    DeletePoint(s->topLeft);
    free(s);
}

void PrintSquare(Square *s) {
    printf("CARRÉ (%d, %d) %d", s->topLeft->x, s->topLeft->y, s->length);
}
//endregion

//region Rectangle
Rectangle *MakeRectangle(Point *topLeft, int width, int height) {
    Rectangle *s = malloc(sizeof(Rectangle));
    s->topLeft = topLeft;
    s->width = width;
    s->height = height;

    return s;
}

Shape *MakeRectangleShape(Point *topLeft, int width, int height) {
    Shape *s = malloc(sizeof(Shape));
    s->type = RECTANGLE;
    s->shape = MakeRectangle(topLeft, width, height);
    s->id = 0;

    return s;
}

void DeleteRectangle(Rectangle *s) {
    DeletePoint(s->topLeft);
    free(s);
}

void PrintRectangle(Rectangle *s) {
    printf("RECTANGLE (%d, %d) %d %d", s->topLeft->x, s->topLeft->y, s->width, s->height);
}
//endregion

//region Cercle
Circle *MakeCircle(Point *center, int radius) {
    Circle *s = malloc(sizeof(Circle));
    s->center = center;
    s->radius = radius;

    return s;
}

Shape *MakeCircleShape(Point *center, int radius) {
    Shape *s = malloc(sizeof(Shape));
    s->type = CIRCLE;
    s->shape = MakeCircle(center, radius);
    s->id = 0;

    return s;
}

void DeleteCircle(Circle *s) {
    DeletePoint(s->center);
    free(s);
}

void PrintCircle(Circle *s) {
    printf("CERCLE (%d, %d) %d", s->center->x, s->center->y, s->radius);
}
//endregion

//region Polygone
Polygon *MakePolygon(Point **points, int numberOfPoints) {
    Polygon *p = malloc(sizeof(Polygon));
    p->points = points;
    p->numberOfPoints = numberOfPoints;

    return p;
}

Shape *MakePolygonShape(Point **points, int numberOfPoints) {
    Shape *s = malloc(sizeof(Shape));
    s->type = POLYGON;
    s->shape = MakePolygon(points, numberOfPoints);
    s->id = 0;

    return s;
}

void DeletePolygon(Polygon *p) {
    for (int i = 0; i < p->numberOfPoints; ++i) {
        free(p->points[i]);
    }
    free(p->points);
    free(p);
}

void PrintPolygon(Polygon *p) {
    printf("POLYGONE ");
    for (int i = 0; i < p->numberOfPoints; ++i) {
        printf("(%d %d) ", p->points[i]->x, p->points[i]->y);
    }
}
//endregion

void DeleteShape(Shape *s) {
    switch (s->type) {
        case POINT:
            DeletePoint((Point*)s->shape);
            break;
        case LINE:
            DeleteLine((Line*)s->shape);
            break;
        case SQUARE:
            DeleteSquare((Square*)s->shape);
            break;
        case RECTANGLE:
            DeleteRectangle((Rectangle*)s->shape);
            break;
        case CIRCLE:
            DeleteCircle((Circle*)s->shape);
            break;
        case POLYGON:
            DeletePolygon((Polygon*)s->shape);
            break;
    }

    free(s);
}

void PrintShape(Shape *s) {
    printf("    %d : ", s->id);
    switch (s->type) {
        case POINT:
            PrintPoint((Point*)s->shape);
            break;
        case LINE:
            PrintLine((Line*)s->shape);
            break;
        case SQUARE:
            PrintSquare((Square*)s->shape);
            break;
        case RECTANGLE:
            PrintRectangle((Rectangle*)s->shape);
            break;
        case CIRCLE:
            PrintCircle((Circle*)s->shape);
            break;
        case POLYGON:
            PrintPolygon((Polygon*)s->shape);
            break;
    }
}
