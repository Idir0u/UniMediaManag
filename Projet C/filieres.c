#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "filieres.h"

typedef struct filiere
{
    int id_etab;
    int id_depart;
    int id_filiere;
    char nom_filiere[50];
    char niveau[20];
} Filiere;

void AfficheFiliere_par_Departement(FILE *file, int idDepartement, int **T, int *i) {
    Filiere filiere;
    *i = 0;
    *T = NULL;

    while (fscanf(file, "%d-%d-%d-%49[^-]-%19s\n", &filiere.id_filiere, &filiere.id_etab, &filiere.id_depart, filiere.nom_filiere, filiere.niveau) == 5) {
        if (filiere.id_depart == idDepartement) {
            int *temp = realloc(*T, (*i + 1) * sizeof(int));

            if (temp == NULL) {
                fclose(file);
                free(*T);
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }

            *T = temp;
            (*T)[*i] = filiere.id_filiere;
            (*i)++;

            printf("id_filiere: %d - nom_filiere: %s - %s\n", filiere.id_filiere, filiere.nom_filiere, filiere.niveau);
        }
    }
}


void AfficheFiliere_par_Niveau(FILE *file, int idEtab, const char *Niveau, int **T, int *i) {
    Filiere filiere;
    *i = 0;
    *T = NULL;

    while (fscanf(file, "%d-%d-%d-%99[^-]-%19s\n", &filiere.id_filiere, &filiere.id_etab, &filiere.id_depart, filiere.nom_filiere, filiere.niveau) == 5) {
        if ((strcmp(filiere.niveau, Niveau) == 0) && (idEtab == filiere.id_etab)) {
            int *temp = realloc(*T, (*i + 1) * sizeof(int));

            if (temp == NULL) {
                fclose(file);
                free(*T);
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }

            *T = temp;
            (*T)[*i] = filiere.id_filiere;
            (*i)++;

            printf("id_filiere: %d - nom_filiere: %s\n", filiere.id_filiere, filiere.nom_filiere);
        }
    }
}

