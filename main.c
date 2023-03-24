#include "shape_manager.h"

int main() {
    AddShape(MakePointShape(65, 78));
    AddShape(MakeCircleShape(MakePoint(69, 54), 765));
    AddShape(MakeSquareShape(MakePoint(8, 6), 98));
    PrintShapes();
    RemoveShape(3);
    PrintShapes();

    return 0;
}
