#include <stdio.h>
#include <stdlib.h>
#include "etablissements.h"
typedef struct Etablissement {
    int ID;
    char nom[30];

} Etablissement;

void Afficheetablissement(int** T, int* i) {
    Etablissement etab;
    FILE* f = fopen("Etablissement.txt", "r");
    if (f == NULL) {
        printf("erreur d'affiche");
    } else {
        *i = 0;
        int capacity = 10;
        *T = malloc(capacity * sizeof(int));

        if (*T == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        printf("Liste des etablissements de l'universite :\n");
        while (fscanf(f, "%d-%30s", &etab.ID, etab.nom) == 2) {
            if (*i >= capacity) {
                capacity *= 2;
                *T = realloc(*T, capacity * sizeof(int));

                if (*T == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
            }

            (*T)[*i] = etab.ID;
            (*i)++;
            printf("\nid_etablissement: %d - Etablissement: %s", etab.ID, etab.nom);
        }
    }

    fclose(f);
}
