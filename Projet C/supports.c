#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "supports.h"


void afficherSupportsParModule(int idModule, Support* listeSupports) {
    Support* temp = listeSupports;

    printf("Liste des supports pour le module %d :\n", idModule);
    while (temp != NULL) {
        if (temp->id_module == idModule) {
            printf("ID Support : %d - ID Module : %d - Support : %s - Type : %s - Format : %s\n", temp->id_support, temp->id_module, temp->nom_support, temp->type_support, temp->format);
        }
        temp = temp->suivant;
    }
}

void lireEtAfficherSupportsParModule() {
    FILE* fichier = fopen("supports.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    Support* listeSupports = NULL;
    char ligne[200];

    int idModule;
    printf("Saisir l'ID du module : ");
    scanf("%d", &idModule);

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Support* nouveauSupport = (Support*)malloc(sizeof(Support));
        if (nouveauSupport == NULL) {
            printf("Erreur d'allocation de mémoire.\n");
            fclose(fichier);
            return;
        }

        if (sscanf(ligne, "%d-%d-%49[^-]-%49[^-]-%49[^\n]", &nouveauSupport->id_support, &nouveauSupport->id_module, nouveauSupport->nom_support, nouveauSupport->type_support, nouveauSupport->format) == 5) {
            if (nouveauSupport->id_module == idModule) {
                nouveauSupport->suivant = listeSupports;
                listeSupports = nouveauSupport;
            }
        }
    }

    fclose(fichier);

    afficherSupportsParModule(idModule, listeSupports);

    while (listeSupports != NULL) {
        Support* temp = listeSupports;
        listeSupports = listeSupports->suivant;
        free(temp);
    }
}

void afficherSupportsParModuleEtType(int idModule, char* type, Support* listeSupports) {
    Support* temp = listeSupports;

    printf("Liste des supports pour le module %d et de type %s :\n", idModule, type);
    while (temp != NULL) {
        if (temp->id_module == idModule && strcmp(temp->type_support, type) == 0) {
            printf("ID Support : %d - ID Module : %d - Support : %s - Type : %s - Format : %s\n", temp->id_support, temp->id_module, temp->nom_support, temp->type_support, temp->format);
        }
        temp = temp->suivant;
    }
}

void lireEtAfficherSupportsParModuleEtType() {
    FILE* fichier = fopen("supports.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    Support* listeSupports = NULL;
    char ligne[200];

    int idModule;
    printf("Saisir l'ID du module : ");
    scanf("%d", &idModule);

    char type[50];
    printf("Saisir le type de support : ");
    scanf("%s", type);


    for (int i = 0; type[i]; i++) {
        type[i] = toupper(type[i]);
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Support* nouveauSupport = (Support*)malloc(sizeof(Support));
        if (nouveauSupport == NULL) {
            printf("Erreur d'allocation de mémoire.\n");
            fclose(fichier);
            return;
        }

        if (sscanf(ligne, "%d-%d-%49[^-]-%49[^-]-%49[^\n]", &nouveauSupport->id_support, &nouveauSupport->id_module, nouveauSupport->nom_support, nouveauSupport->type_support, nouveauSupport->format) == 5) {

            for (int i = 0; nouveauSupport->type_support[i]; i++) {
                nouveauSupport->type_support[i] = toupper(nouveauSupport->type_support[i]);
            }

            if (nouveauSupport->id_module == idModule && strcmp(nouveauSupport->type_support, type) == 0) {
                nouveauSupport->suivant = listeSupports;
                listeSupports = nouveauSupport;
            }
        }
    }

    fclose(fichier);

    afficherSupportsParModuleEtType(idModule, type, listeSupports);

    while (listeSupports != NULL) {
        Support* temp = listeSupports;
        listeSupports = listeSupports->suivant;
        free(temp);
    }
}


int idExisteDeja(int idSupport) {
    FILE* fichier = fopen("Supports.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    char ligne[200];
    int supportTrouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int id;
        sscanf(ligne, "%d-", &id);

        if (id == idSupport) {
            supportTrouve = 1;
            break;
        }
    }

    fclose(fichier);

    return supportTrouve;
}

void ajouterSupport() {
    FILE* fichier = fopen("Supports.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    Support* nouveauSupport = (Support*)malloc(sizeof(Support));
    if (nouveauSupport == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        fclose(fichier);
        return;
    }
    int idSupport;
    printf("Saisir l'ID du support : ");
    scanf("%d", &idSupport);
    while (idExisteDeja(idSupport)) {
        printf("L'ID du support existe déjà. Veuillez saisir un autre ID de support : ");
        scanf("%d", &idSupport);
    }

    int idModule;
    printf("Saisir l'ID du module : ");
    scanf("%d", &idModule);
    while (!idExisteDeja(idModule)) {
        printf("L'ID du module n'existe pas. Veuillez saisir un autre ID de Module : ");
        scanf("%d", &idModule);
    }
    printf("Saisir le nom du support : ");
    scanf("%s", nouveauSupport->nom_support);

    printf("Saisir le type du support : ");
    scanf("%s", nouveauSupport->type_support);

    printf("Saisir le format du support : ");
    scanf("%s", nouveauSupport->format);

    fprintf(fichier, "\n%d-%d-%s-%s-%s", nouveauSupport->id_support, nouveauSupport->id_module, nouveauSupport->nom_support, nouveauSupport->type_support, nouveauSupport->format);

    fclose(fichier);
    free(nouveauSupport);
}

void supprimerSupport(int idSupport) {
    FILE *fichier = fopen("Supports.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    char ligne[200];
    int supportTrouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int id;
        sscanf(ligne, "%d-", &id);


        if (id != idSupport) {
            fputs(ligne, temp);
        } else {
            supportTrouve = 1;
        }
    }

    fclose(fichier);
    fclose(temp);

    if (!supportTrouve) {
        remove("temp.txt");
        printf("Le support avec l'ID %d n'existe pas.\n", idSupport);
        return;
    }

    remove("Supports.txt");
    rename("temp.txt", "Supports.txt");
    printf("Le support avec l'ID %d a été supprimé avec succès.\n", idSupport);
}

void telechargerSupport() {
    FILE* fichierSupports = fopen("Supports.txt", "r");
    if (fichierSupports == NULL) {
        printf("\nErreur : Impossible d'ouvrir le fichier des supports.\n");
        return;
    }

    int id;
    printf("\nEntrez l'ID du support à télécharger : ");
    scanf("%d", &id);

    FILE* fichierTelechargements = fopen("telechargements.txt", "a");
    if (fichierTelechargements == NULL) {
        printf("\nErreur : Impossible d'ouvrir le fichier de téléchargements.\n");
        fclose(fichierSupports);
        return;
    }

    Support support;
    int trouve = 0;
    while (fscanf(fichierSupports, "%d-%d-%49[^-]-%49[^-]-%49[^\n]\n", &support.id_support, &support.id_module, support.nom_support, support.type_support, support.format) == 5) {
        if (support.id_support == id) {
            fprintf(fichierTelechargements, "%d-%d-%s-%s-%s\n", support.id_support, support.id_module, support.nom_support, support.type_support, support.format);
            trouve = 1;
            break;
        }
    }

    fclose(fichierSupports);
    fclose(fichierTelechargements);

    if (trouve) {
        printf("\nLe support avec l'ID %d a été téléchargé et enregistré.\n", id);
    } else {
        printf("\nSupport non trouvé avec l'ID %d.\n", id);
    }
}



