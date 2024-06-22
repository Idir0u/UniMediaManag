#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "SaisirChaine.h"
#include "Demandes.h"


void ValiderEntrer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void AjouterDemande(Demande** listeDemandes) {
    char demande[100];
    printf("Ajoutez votre Demande : ");
    ValiderEntrer(); // Nettoie le buffer d'entrée
    fgets(demande, sizeof(demande), stdin);
    demande[strcspn(demande, "\n")] = '\0';
    time_t t = time(NULL);
    struct tm* timeinfo = localtime(&t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", timeinfo);

    Demande* nouveauDemande = (Demande*)malloc(sizeof(Demande));
    if (nouveauDemande == NULL) {
        printf("Erreur.\n");
        return;
    }
    strcpy(nouveauDemande->date, date);
    strcpy(nouveauDemande->contenu, demande);
    nouveauDemande->suivant = *listeDemandes;
    *listeDemandes = nouveauDemande;

    FILE* fichier = fopen("demandes.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }
    fprintf(fichier, "%s---%s\n",demande,nouveauDemande->date);
    fclose(fichier);
}

void chargerDemandesEtAfficher() {
    FILE* fichier = fopen("demandes.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }
    char ligne[200];
    Demande* listeDemandes = NULL;
    Demande* dernierDemande = NULL;
    int numDemande=1;
    printf("Liste des demandes :\n");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char demande[100];
        char date[20];

        if (sscanf(ligne, "%99[^-]-%99[^\n]\n", demande, date) == 2) {
            Demande* nouveauDemande = (Demande*)malloc(sizeof(Demande));
            if (nouveauDemande == NULL) {
                printf("Erreur.\n");
                fclose(fichier);
                return;
            }

            strcpy(nouveauDemande->contenu, demande);
            strcpy(nouveauDemande->date, date);
            nouveauDemande->suivant = NULL;

            if (listeDemandes == NULL) {
                listeDemandes = nouveauDemande;
                dernierDemande = nouveauDemande;
            } else {
                dernierDemande->suivant = nouveauDemande;
                dernierDemande = nouveauDemande;
            }

            printf("%d - Demandes : %s ----- date : %s\n", numDemande, demande, date);
            numDemande++;
        }
    }

    fclose(fichier);

    while (listeDemandes != NULL) {
        Demande* temp = listeDemandes;
        listeDemandes = listeDemandes->suivant;
        free(temp);
    }
}
void supprimerDemande(int idDemande) {
    FILE* fichierLecture = fopen("demandes.txt", "r");
    if (fichierLecture == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    FILE* fichierEcriture = fopen("temp.txt", "w");
    if (fichierEcriture == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier temporaire.\n");
        fclose(fichierLecture);
        return;
    }

    int compteur = 1;
    char contenu[100];
    while (fgets(contenu, sizeof(contenu), fichierLecture) != NULL) {
        if (compteur != idDemande) {
            fprintf(fichierEcriture, "%s", contenu);
        }
        compteur++;
    }

    fclose(fichierLecture);
    fclose(fichierEcriture);

    remove("demandes.txt");
    rename("temp.txt", "demandes.txt");
}
