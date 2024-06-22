#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "departements.h"

typedef struct
{
    int id;        // CodeDepartement
    int idetab;    // CodeEtablissement
    char Nom[20];
} Departement;

void AfficherDepartement(int idEtab, int **T, int *i) {
    Departement departement;
    FILE *f = fopen("Departement.txt", "r");

    if (f == NULL) {
        perror("\nErreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    } else {
        *i = 0;
        *T = NULL;

        printf("\n-----------La liste des departements est : --------------\n");

        while (fscanf(f, "%d-%d-%39[^\n]\n", &departement.id, &departement.idetab, departement.Nom) == 3) {
            if (departement.idetab == idEtab) {

                int *temp = realloc(*T, (*i + 1) * sizeof(int));

                if (temp == NULL) {
                    fclose(f);
                    free(*T);
                    perror("Erreur d'allocation de mémoire");
                    exit(EXIT_FAILURE);
                }

                *T = temp;
                (*T)[*i] = departement.id;
                (*i)++;

                printf("id_departement: %d - Departement: %s\n", departement.id, departement.Nom);
            }
        }

    }
}
