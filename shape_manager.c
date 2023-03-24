#include <stddef.h>
#include <stdlib.h>
#include <printf.h>
#include "shape_manager.h"

LList g_shapes;
unsigned int g_id = 1;

unsigned int GetNextId() {
    //TODO: change implementation to make unused ids be reused
    return g_id++;
}

unsigned int AddShape(Shape *s) {
    // On crée l'élément à ajouter
    LListElement *new = malloc(sizeof(LListElement));
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
    LListElement *toRemove;
    if (g_shapes.first->data->id == id) {
        // On doit supprimer le premier élément
        toRemove = g_shapes.first;
        if (toRemove->next != NULL) {
            toRemove->next->previous = NULL;
            g_shapes.first = toRemove->next;
        } else g_shapes.first = NULL;
    }
    else if (g_shapes.last->data->id == id) {
        toRemove = g_shapes.last;
        toRemove->previous->next = NULL;
    }
    else {
        LListElement *next = g_shapes.first;
        while (next != NULL) {
            if (next->data->id == id) break;
            next = next->next;
        }

        if (next == NULL) return 0; // Si c'est nul ça veut dire qu'on à pas trouvé d'élément avec le bon id

        toRemove = next;
        toRemove->next->previous = toRemove->previous;
        toRemove->previous->next = toRemove->next;
    }

    DeleteShape(toRemove->data);
    free(toRemove);

    return 1;
}

void PrintShapes() {
    if (g_shapes.first == NULL || g_shapes.first->data == NULL) {
        printf("La liste est vide.");
        return;
    }

    printf("La liste contient les formes suivantes:\n    ID : FORME PARAMÈTRES\n");
    // On parcoure la liste pour afficher chaque élément
    LListElement *next = g_shapes.first;
    while (next != NULL) {
        PrintShape(next->data);
        printf("\n");
        next = next->next;
    }
}
