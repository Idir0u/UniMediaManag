#include <stdio.h>
#include <stdlib.h>
#include "semestres.h"

typedef struct semestre{
    int Id_semesetre;
    int Id_filiere;
    char nom[10];
} Semestre;

void AfficheSemestres(int id_filiere, int **T, int *i) {
    Semestre semestre;
    FILE *f = fopen("Semestres.txt", "r");
    if (f == NULL) {
        perror("\nErreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    } else {
        *i = 0;
        *T = NULL;

        printf("\n-----------La liste des semestres selon la filiere est : --------------\n");
        while (fscanf(f, "%d-%d-%39s", &semestre.Id_semesetre, &semestre.Id_filiere, semestre.nom) == 3) {
            if (semestre.Id_filiere == id_filiere) {
                int *temp = realloc(*T, (*i + 1) * sizeof(int));

                if (temp == NULL) {

                    fclose(f);
                    free(*T);
                    perror("Erreur d'allocation de mémoire");
                    exit(EXIT_FAILURE);
                }

                *T = temp;
                (*T)[*i] = semestre.Id_semesetre;
                (*i)++;

                printf("id_semestre: %d - Semestre: %s\n", semestre.Id_semesetre, semestre.nom);
            }
        }
        fclose(f);
    }
}

