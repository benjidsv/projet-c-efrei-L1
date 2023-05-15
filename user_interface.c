#include "user_interface.h"
#include "shape_manager.h"
#include "shape_drawer.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 32

#define PRINT_ACTIONS_PROMPT printf("Choisissez une action:\n    1 - Créer une forme\n    2 - Supprimer une forme\n    3 - Afficher la liste des formes\n    4 - Dessiner les formes\n    5 - Quitter le programme\n")
#define PRINT_SHAPE_CREATION_PROMPT printf("Quel type de forme voulez vous créer ?\n    1 - Point\n    2 - Ligne\n    3 - Carré\n    4 - Rectangle\n    5 - Cercle\n    6 - Polygone\n    7 - Retour\n")

// Lis un entier et le retourne
int ReadInt() {
    char *end, input[MAX_INPUT_LENGTH];
    long inputAsLong;

    // On entre dans une boucle qui se répète tant que la saisie est invalide (pas un entier / pas entre min et max)
    printf("> ");
    while (fgets(input, MAX_INPUT_LENGTH, stdin)) { // On récupère la saisie
        // On convertit la saisie en entier avec strtol (string to long)
        inputAsLong = strtol(input, &end, 10);
        // Si la fin est égale à l'entrée originale / la fin n'est pas une nouvelle ligne (dernier caractère avec fgets)
        // cela veut dire qu'il y a eu un problème (très probablement que la saisie est invalide)
        if (end == input || *end != '\n') {
            printf("Saisie invalide - entrez une valeur appropriée\n> ");
        } else break; // Sinon la saisie est valide
    }

    return (int)inputAsLong;
}

// Lis un entier positif et retourne la saisie
int ReadIntPositive() {
    char *end, input[MAX_INPUT_LENGTH];
    long inputAsLong;

    // On entre dans une boucle qui se répète tant que la saisie est invalide (pas un entier / pas entre min et max)
    printf("> ");
    while (fgets(input, MAX_INPUT_LENGTH, stdin)) { // On récupère la saisie
        // On convertit la saisie en entier avec strtol (string to long)
        inputAsLong = strtol(input, &end, 10);
        // Si la fin est égale à l'entrée originale / la fin n'est pas une nouvelle ligne (dernier caractère avec fgets)
        // cela veut dire qu'il y a eu un problème (très probablement que la saisie est invalide)
        // On vérifie aussi que l'entrée est bien positive
        if (end == input || *end != '\n' || inputAsLong < 0) {
            printf("Saisie invalide - entrez une valeur appropriée\n> ");
        } else break; // Sinon la saisie est valide
    }

    return (int)inputAsLong;
}

// Lis un entier entre minValue et maxValue et retourne la saisie
int ReadIntBetween(const int minValue, const int maxValue) {
    char *end, input[MAX_INPUT_LENGTH];
    long inputAsLong;

    // On entre dans une boucle qui se répète tant que la saisie est invalide (pas un entier / pas entre min et max)
    printf("> ");
    while (fgets(input, MAX_INPUT_LENGTH, stdin)) { // On récupère la saisie
        // On convertit la saisie en entier avec strtol (string to long)
        inputAsLong = strtol(input, &end, 10);
        // Si la fin est égale à l'entrée originale / la fin n'est pas une nouvelle ligne (dernier caractère avec fgets)
        // cela veut dire qu'il y a eu un problème (très probablement que la saisie est invalide)
        // On vérifie aussi que l'entrée est bien entre min et max
        if (end == input || *end != '\n' || inputAsLong < minValue || inputAsLong > maxValue) {
            printf("Saisie invalide - entrez une valeur appropriée\n> ");
        } else break; // Sinon la saisie est valide
    }

    return (int)inputAsLong;
}

void CreatePoint() {
    int x, y;

    printf("Saisissez la coordonnée en x\n");
    x = ReadInt();
    printf("Saisissez la coordonnée en y\n");
    y = ReadInt();

    AddShape(MakePointShape(x, y));
    printf("Le point a été ajouté avec succès\n");
}

void CreateLine() {
    int x1, x2, y1, y2;

    printf("Saisissez la coordonnée en x du premier point\n");
    x1 = ReadInt();
    printf("Saisissez la coordonnée en y du premier point\n");
    y1 = ReadInt();

    printf("Saisissez la coordonnée en x du second point\n");
    x2 = ReadInt();
    printf("Saisissez la coordonnée en y du second point\n");
    y2 = ReadInt();

    AddShape(MakeLineShape(MakePoint(x1, y1), MakePoint(x2, y2)));
    printf("La ligne a été ajoutée avec succès\n");
}

void CreateSquare() {
    int x, y, l;

    printf("Saisissez la coordonnée en x du coin supérieur gauche\n");
    x = ReadInt();
    printf("Saisissez la coordonnée en y du coin supérieur gauche\n");
    y = ReadInt();
    printf("Saisissez la longueur de coté");
    l = ReadIntPositive();

    AddShape(MakeSquareShape(MakePoint(x, y), l));
    printf("Le carré a été ajouté avec succès\n");
}

void CreateRectangle() {
    int x, y, w, h;

    printf("Saisissez la coordonnée en x du coin supérieur gauche\n");
    x = ReadInt();
    printf("Saisissez la coordonnée en y du coin supérieur gauche\n");
    y = ReadInt();
    printf("Saisissez la longueur\n");
    w = ReadIntPositive();
    printf("Saisissez la largeur\n");
    h = ReadIntPositive();

    AddShape(MakeRectangleShape(MakePoint(x, y), w, h));
    printf("Le rectangle a été ajouté avec succès\n");
}

void CreateCircle() {
    int x, y, r;

    printf("Saisissez la coordonnée en x du centre\n");
    x = ReadInt();
    printf("Saisissez la coordonnée en y du centre\n");
    y = ReadInt();
    printf("Saisissez le rayon\n");
    r = ReadIntPositive();

    AddShape(MakeCircleShape(MakePoint(x, y), r));
    printf("Le cercle a été ajouté avec succès\n");
}

void CreatePolygon() {
    printf("Saisissez le nombre de points du polygone\n");
    int n = ReadIntPositive();
    if (n == 0) return; // Un polygone avec 0 points n'a pas de sens

    Point **pts = malloc(n * sizeof(Point*));
    for (int i = 0; i < n; ++i) {
        int x, y;

        printf("Point n°%d\n", i + 1);
        printf("Saisissez la coordonnée en x\n");
        x = ReadInt();
        printf("Saisissez la coordonnée en y\n");
        y = ReadInt();

        pts[i] = MakePoint(x, y);
    }

    AddShape(MakePolygonShape(pts, n));
    printf("Le polygone a été ajouté avec succès\n");
}

int MainLoop() {
    int answer;
    while (1) {
        PRINT_ACTIONS_PROMPT;
        answer = ReadIntBetween(1, 5);

        //region Création de forme
        if (answer == 1) {
            // L'utilisateur veut créer une forme
            PRINT_SHAPE_CREATION_PROMPT;
            answer = ReadIntBetween(1, 7);
            switch (answer) {
                case 1:
                    CreatePoint();
                    continue;
                case 2:
                    CreateLine();
                    break;
                case 3:
                    CreateSquare();
                    break;
                case 4:
                    CreateRectangle();
                    break;
                case 5:
                    CreateCircle();
                    break;
                case 6:
                    CreatePolygon();
                    break;
                case 7:
                    // Dans le cas d'un retour on veut simplement recommencer la boucle
                    continue;
                default:
                    // Dans le cas ou la valeur retournée est imprévue (ce qui devrait être impossible) alors on a un sérieux problème
                    abort();
            }
        }
        //endregion

        //region Suppression de forme
        else if (answer == 2) {
            int success = 0;
            while (success == 0) {
                printf("Entrez l'ID de la forme à supprimer (ou 0 pour annuler la procédure):\n");
                int idToDelete = ReadInt();
                if (idToDelete == 0) break; // Retour

                success = RemoveShape(idToDelete);
                if (!success) printf("Aucune forme n'a cet ID\n");
            }

            if (success) printf("La forme a été supprimée\n");

            continue;
        }
        //endregion

        else if (answer == 3) PrintShapes();

        else if (answer == 4) DrawShapes(GetShapes());

        else if (answer == 5) return 1; // On quitte le programme car l'utilisateur le demande

        else abort(); // On quitte le programme avec une erreur (on ne devrait jamais arriver ici)
    }
}
