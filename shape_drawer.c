#include "shape_drawer.h"
#include "util/math.h"

#define WIDTH 40
#define HEIGHT 20
#define EMPTY_CHAR '-'
#define FILLED_CHAR '#'

char **CreateEmptyImage() {
    char **image = malloc(HEIGHT * sizeof(char*));
    for (int y = 0; y < HEIGHT; ++y) {
        image[y] = malloc(sizeof(char) * WIDTH);
        for (int x = 0; x < WIDTH; ++x) {
            image[y][x] = EMPTY_CHAR;
        }
    }
    return image;
}

void FreeImage(char **image) {
    for (int y = 0; y < HEIGHT; ++y) {
        free(image[y]);
    }
    free(image);
}

void UpdateImageCoords(int x, int y, char **image) {
    if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
        // Si le point est bien situé dans l'image
        image[y][x] = FILLED_CHAR;
    }
}

void UpdateImagePoint(Point *point, char **image) {
    UpdateImageCoords(point->x, point->y, image);
}

void UpdateImageLine(Line *line, char **image) {
    // Implémentation de l'algorithme de Nicolas Flasque
    Point *A, *B;
    if (line->start->x <= line->end->x) {
        A = line->start;
        B = line->end;
    }
    else {
        A = line->end;
        B = line->start;
    }

    int dx = B->x - A->x, dy = B->y - A->y, dmin = Min(dx, Abs(dy)), dmax = Max(dx, Abs(dy));
    int numberOfSegments = dmin + 1, segmentBaseSize = (dmax + 1) / numberOfSegments, remainingPixels = (dmax + 1) % numberOfSegments;

    int *segments = malloc(numberOfSegments * sizeof(int));
    for (int i = 0; i < numberOfSegments; ++i) segments[i] = segmentBaseSize;

    int *accumulations = malloc(numberOfSegments * sizeof(int));
    accumulations[0] = 0;
    for (int i = 1; i < numberOfSegments; ++i) {
        accumulations[i] = ((i + 1) * remainingPixels) % numberOfSegments < (i * remainingPixels) % numberOfSegments;
        segments[i] += accumulations[i];
    }

    int x = A->x, y = A->y;
    UpdateImageCoords(x, y, image);
    segments[0] -= 1;
    if (dy < 0) {
        // On trace vers le bas
        if (dx > Abs(dy)) {
            // Horizontal
            for (int i = 0; i < numberOfSegments; ++i) {
                for (int j = 0; j < segments[i]; ++j) {
                    x++;
                    UpdateImageCoords(x, y, image);
                }
                y--;
            }
        }
        else {
            // Vertical
            for (int i = 0; i < numberOfSegments; ++i) {
                for (int j = 0; j < segments[i]; ++j) {
                    y--;
                    UpdateImageCoords(x, y, image);
                }
                x++;
            }
        }
    }
    else {
        // On trace vers le haut
        if (dx > dy) {
            // Horizontal
            for (int i = 0; i < numberOfSegments; ++i) {
                for (int j = 0; j < segments[i]; ++j) {
                    x++;
                    UpdateImageCoords(x, y, image);
                }
                y++;
            }
        }
        else {
            // Vertical
            for (int i = 0; i < numberOfSegments; ++i) {
                for (int j = 0; j < segments[i]; ++j) {
                    y++;
                    UpdateImageCoords(x, y, image);
                }
                x++;
            }
        }
    }
}

void UpdateImageSquare(Square *square, char **image) {
    // On trace chaque ligne une par une
    for (int x = 0; x < square->length; ++x)
        UpdateImageCoords(square->topLeft->x + x, square->topLeft->y, image);
    for (int y = square->length - 1; y > 0; --y)
        UpdateImageCoords(square->topLeft->x + square->length - 1, square->topLeft->y + y, image);
    for (int x = square->length - 2; x >= 0; --x)
        UpdateImageCoords(square->topLeft->x + x, square->topLeft->y + square->length - 1, image);
    for (int y = 0; y < square->length - 1; ++y) UpdateImageCoords(square->topLeft->x, square->topLeft->y + y, image);
}

void UpdateImageRectangle(Rectangle *rect, char **image) {
    // On trace chaque ligne une par une
    for (int x = 0; x < rect->width; ++x)
        UpdateImageCoords(rect->topLeft->x + x, rect->topLeft->y, image);
    for (int y = rect->height - 1; y > 0; --y)
        UpdateImageCoords(rect->topLeft->x + rect->width - 1, rect->topLeft->y + y, image);
    for (int x = rect->width - 2; x >= 0; --x)
        UpdateImageCoords(rect->topLeft->x + x, rect->topLeft->y + rect->height - 1, image);
    for (int y = 0; y < rect->height - 1; ++y) UpdateImageCoords(rect->topLeft->x, rect->topLeft->y + y, image);
}

void UpdateImageCircle(Circle *circle, char **image) {
    // Implémentation de l'algoritme de tracé de cercle
    int x = 0, y = circle->radius, d = circle->radius - 1;

    while (y >= x) {
        UpdateImageCoords(circle->center->x + x, circle->center->y + y, image);
        UpdateImageCoords(circle->center->x + y, circle->center->y + x, image);
        UpdateImageCoords(circle->center->x - x, circle->center->y + y, image);
        UpdateImageCoords(circle->center->x - y, circle->center->y + x, image);

        UpdateImageCoords(circle->center->x + x, circle->center->y - y, image);
        UpdateImageCoords(circle->center->x + y, circle->center->y - x, image);
        UpdateImageCoords(circle->center->x - x, circle->center->y - y, image);
        UpdateImageCoords(circle->center->x - y, circle->center->y - x, image);

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        }
        if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        }
        else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }
}

void UpdateImagePolygon(Polygon *polygon, char **image) {
    for (int i = 0; i < polygon->numberOfPoints - 1; ++i) {
        UpdateImageLine(MakeLine(polygon->points[i], polygon->points[i + 1]), image);
    }
    UpdateImageLine(MakeLine(polygon->points[0], polygon->points[polygon->numberOfPoints - 1]), image);
}

void PrintImage(char **image) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            printf("%c  ", image[y][x]);
        }
        printf("\n");
    }
}

void DrawShapes(ShapeLList *shapes) {
    char **image = CreateEmptyImage();
    ShapeLListElement *next = shapes->first;
    while (next != NULL) {
        switch (next->data->type) {
            case POINT:
                UpdateImagePoint((Point*)next->data->shape, image);
                break;
            case LINE:
                UpdateImageLine((Line*)next->data->shape, image);
                break;
            case SQUARE:
                UpdateImageSquare((Square*)next->data->shape, image);
                break;
            case RECTANGLE:
                UpdateImageRectangle((Rectangle*)next->data->shape, image);
                break;
            case CIRCLE:
                UpdateImageCircle((Circle*)next->data->shape, image);
                break;
            case POLYGON:
                UpdateImagePolygon((Polygon*)next->data->shape, image);
                break;
        }

        next = next->next;
    }

    PrintImage(image);
    FreeImage(image);
}