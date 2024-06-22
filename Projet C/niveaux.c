#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "niveaux.h"
typedef struct
{
   // CodeEtablissement
    char Nom[20];
} Niveau;

void AfficherNiveau(int **T, int *i) {
    Niveau niveau;
    *i = 0;
    int choix;

    FILE *f = fopen("Niveaux.txt", "r");
    if (f == NULL) {
        perror("\nErreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    } else {
        *T = NULL;

        printf("\n-----------La liste des Niveaux est : --------------\n");
        while (fscanf(f, "%d-%19[^\n]\n", &choix, niveau.Nom) == 2) {
            int *temp = realloc(*T, (*i + 1) * sizeof(int));

            if (temp == NULL) {

                fclose(f);
                free(*T);
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }

            *T = temp;
            (*T)[*i] = choix;
            (*i)++;

            printf("%d :niveau: %s\n", choix, niveau.Nom);
        }

        fclose(f);
    }
}
