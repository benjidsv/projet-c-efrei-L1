#ifndef PROJETC_SHAPES_H
#define PROJETC_SHAPES_H

#endif //PROJETC_SHAPES_H

typedef enum EShapeType {
    POINT,
    LINE,
    SQUARE,
    RECTANGLE,
    CIRCLE,
    POLYGON,
} EShapeType;

typedef struct Shape {
    EShapeType type;
    void *shape;
} Shape;

void DeleteShape(Shape *s);

typedef struct Point {
    int x, y;
} Point;

Shape *MakePointShape(int x, int y);
void DeletePoint(Point *p);
void PrintPoint(Point *p);

typedef struct Line {
    Point *start, *end;
} Line;

Shape *MakeLineShape(Point *start, Point *end);
void DeleteLine(Line *l);
void PrintLine(Line *l);

typedef struct Square {
    Point *topLeft;
    int length;
} Square;

Shape *MakeSquareShape(Point *topLeft, int length);
void DeleteSquare(Square *s);
void PrintSquare(Square *s);

typedef struct Rectangle {
    Point *topLeft;
    int width, height;
} Rectangle;

Shape *MakeRectangleShape(Point *topLeft, int width, int height);
void DeleteRectangle(Rectangle *r);
void PrintRectangle(Rectangle *r);

typedef struct Circle {
    Point *center;
    int radius;
} Circle;

Shape *MakeCircleShape(Point *circle, int radius);
void DeleteCircle(Circle *c);
void PrintCircle(Circle *c);

typedef struct Polygon {
    Point **points; // Un pointeur peut être une liste, ceci est une liste de pointeurs (vers des points)
    int numberOfPoints;
} Polygon;

Shape *MakePolygonShape(Point **points, int numberOfPoints);
void DeletePolygon(Polygon *p);
void PrintPolygon(Polygon *p);
