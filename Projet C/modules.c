#include <stdio.h>
#include <stdlib.h>
#include "modules.h"

typedef struct module{
    int Id_module;
    int Id_semestre;
    char nom[50];
} Module;


void AfficheModules(int id_semestre, int **T, int *i)
{
    Module md;
    FILE *f = fopen("Modules.txt", "r");
    if (f == NULL)
    {
        perror("\nErreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    else
    {
        *i = 0;
        *T = NULL;
        printf("\n-----------La liste des modules de semestre est : --------------\n");
        while (fscanf(f, "%d-%d-%49[^\n]\n", &md.Id_module, &md.Id_semestre, md.nom) == 3)
        {
            if (md.Id_semestre == id_semestre)
            {
                int *temp = realloc(*T, (*i + 1) * sizeof(int));
                if (temp == NULL)
                {

                    fclose(f);
                    free(*T);
                    perror("Erreur d'allocation de mémoire");
                    exit(EXIT_FAILURE);
                }

                *T = temp;
                (*T)[*i] = md.Id_module;
                (*i)++;
                printf("id_module: %d - module: %s\n", md.Id_module, md.nom);
            }
        }
        fclose(f);
    }
}
