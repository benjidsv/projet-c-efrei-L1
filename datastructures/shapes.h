#ifndef PROJETC_SHAPES_H
#define PROJETC_SHAPES_H

#endif //PROJETC_SHAPES_H

typedef enum EShapeType {
    POINT,
    LINE,
} EShapeType;

typedef struct Shape {
    EShapeType type;
    void *shape;
} Shape;

typedef struct Point {
    int x, y;
} Point;

Point *MakePoint(int x, int y);
Shape *MakePointShape(int x, int y);
void DeletePoint(Point *p);
void PrintPoint(Point *p);

typedef struct Line {
    Point *start, *end;
} Line;

Line *MakeLine(Point *start, Point *end);
Shape *MakeLineShape(Point *start, Point *end);
void DeleteLine(Line *l);
void PrintLine(Line *l);

