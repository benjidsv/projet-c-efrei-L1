#include "datastructures/linked_list.h"

#ifndef PROJETC_SHAPE_MANAGER_H
#define PROJETC_SHAPE_MANAGER_H

#endif //PROJETC_SHAPE_MANAGER_H

// Ajoute une forme à la liste, retourne son id ou -1 en cas d'erreur
unsigned int AddShape(Shape *s);

// Retire la forme de la liste avec l'id correspondant, retourne 0 en cas d'erreur (id invalide) et 1 sinon
int RemoveShape(unsigned int id);

void PrintShapes();


