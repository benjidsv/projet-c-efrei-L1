#include <stddef.h>
#include <stdlib.h>
#include <printf.h>
#include "shape_manager.h"
#include "datastructures/linked_list.h"

ShapeLList g_shapes; // Liste qui sert à stocker les formes
UIntLList g_freeIds; // Liste qui sert à stocker les id libres pour les réutiliser
unsigned int g_id = 1;

unsigned int GetNextId() {
    if (g_freeIds.first == NULL) return g_id++; // Si aucun id n'est libre on retourne simplement le suivant

    unsigned int id = g_freeIds.first->data;
    if (g_freeIds.first->next == NULL) g_freeIds.first = NULL;
    else g_freeIds.first = g_freeIds.first->next;
    return id;
}

unsigned int AddShape(Shape *s) {
    // On crée l'élément à ajouter
    ShapeLListElement *new = malloc(sizeof(ShapeLListElement));
    new->data = s;
    new->next = NULL; // C'est le dernier élément

    if (g_shapes.first == NULL) {
        // Si le premier élément de la liste est nul (la liste est vide)
        new->previous = NULL; // Alors l'élément précédent est nul
        g_shapes.first = new;
        g_shapes.last = new; // Le premier et dernier élément sont l'unique élément qu'on vient d'ajouter
    } else {
        // Sinon on l'ajoute simplement à la fin de la liste
        new->previous = g_shapes.last;
        g_shapes.last->next = new;
        g_shapes.last = new;
    }

    s->id = GetNextId();
    return s->id;
}

int RemoveShape(unsigned int id) {
    ShapeLListElement *toRemove;
    if (g_shapes.first->data->id == id) {
        // On doit supprimer le premier élément
        toRemove = g_shapes.first;
        if (toRemove->next != NULL) {
            // Si c'est le seul élément de la liste
            toRemove->next->previous = NULL;
            g_shapes.first = toRemove->next;
        } else g_shapes.first = NULL;
    }
    else if (g_shapes.last->data->id == id) {
        // On doit supprimer le dernier élément
        toRemove = g_shapes.last;
        toRemove->previous->next = NULL;
        g_shapes.last = toRemove->previous;
    }
    else {
        // L'élément est quelque part dans la liste
        ShapeLListElement *next = g_shapes.first;
        while (next != NULL) {
            // On parcoure la liste jusqu'à trouver l'élément
            if (next->data->id == id) break;
            next = next->next;
        }

        if (next == NULL) return 0; // Si c'est nul ça veut dire qu'on à pas trouvé d'élément avec le bon id

        // On le retire de la liste
        toRemove = next;
        toRemove->next->previous = toRemove->previous;
        toRemove->previous->next = toRemove->next;
    }

    // On le supprime de la mémoire
    DeleteShape(toRemove->data);
    free(toRemove);

    // On ajoute l'id de la forme supprimée aux id libres pour le réutiliser plus tard
    UIntLListElement *new = malloc(sizeof(UIntLListElement));
    new->data = id;
    new->next = NULL;
    if (g_freeIds.first == NULL) {
        g_freeIds.first = new;
        g_freeIds.last = new;
        new->previous = NULL;
    }
    else {
        new->previous = g_freeIds.last;
        g_freeIds.last->next = new;
        g_freeIds.last = new;
    }

    return 1;
}

void PrintShapes() {
    if (g_shapes.first == NULL || g_shapes.first->data == NULL) {
        printf("La liste est vide\n");
        return;
    }

    printf("La liste contient les formes suivantes:\n");
    // On parcoure la liste pour afficher chaque élément
    ShapeLListElement *next = g_shapes.first;
    while (next != NULL) {
        PrintShape(next->data);
        printf("\n");
        next = next->next;
    }
}

ShapeLList* GetShapes() {
    return &g_shapes;
}
