#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "SaisirChaine.h"
#include "Commentaires.h"
#include "Demandes.h"


void AjouterCommentaire(Commentaire** listeCommentaires) {
    char contenu[100];
    printf("Ajoutez votre commentaire : ");
    ValiderEntrer(); // Nettoie le buffer d'entrée
    fgets(contenu, sizeof(contenu), stdin);
    contenu[strcspn(contenu, "\n")] = '\0';
    time_t t = time(NULL);
    struct tm* timeinfo = localtime(&t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", timeinfo);

    Commentaire* nouveauCommentaire = (Commentaire*)malloc(sizeof(Commentaire));
    if (nouveauCommentaire == NULL) {
        printf("Erreur.\n");
        return;
    }
    strcpy(nouveauCommentaire->date, date);
    strcpy(nouveauCommentaire->contenu, contenu);
    nouveauCommentaire->suivant = *listeCommentaires;
    *listeCommentaires = nouveauCommentaire;

    FILE* fichier = fopen("commentaires.txt", "a");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }
    //int numCommentaire = 1;
    fprintf(fichier, "\n%s---%s",contenu,nouveauCommentaire->date);
    fclose(fichier);
}

void chargerCommentairesEtAfficher() {
    FILE* fichier = fopen("commentaires.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    char ligne[200];
    Commentaire* listeCommentaires = NULL;
    Commentaire* dernierCommentaire = NULL;
    int numCommentaire = 1;

    printf("Liste des commentaires :\n");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char contenu[100];
        char date[20];

        if (sscanf(ligne, "%99[^-]-%99[^\n]\n", contenu, date) == 2) {
            Commentaire* nouveauCommentaire = (Commentaire*)malloc(sizeof(Commentaire));
            if (nouveauCommentaire == NULL) {
                printf("Erreur.\n");
                fclose(fichier);
                return;
            }

            strcpy(nouveauCommentaire->contenu, contenu);
            strcpy(nouveauCommentaire->date, date);
            nouveauCommentaire->suivant = NULL;

            if (listeCommentaires == NULL) {
                listeCommentaires = nouveauCommentaire;
                dernierCommentaire = nouveauCommentaire;
            } else {
                dernierCommentaire->suivant = nouveauCommentaire;
                dernierCommentaire = nouveauCommentaire;
            }

            printf("%d - commentaire : %s ----- date : %s\n", numCommentaire, contenu, date);
            numCommentaire++;
        }
    }

    fclose(fichier);

    while (listeCommentaires != NULL) {
        Commentaire* temp = listeCommentaires;
        listeCommentaires = listeCommentaires->suivant;
        free(temp);
    }
}
void supprimerCommentaire(int idCommentaire) {
    FILE* fichierLecture = fopen("commentaires.txt", "r");
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
        if (compteur != idCommentaire) {
            fprintf(fichierEcriture, "%s", contenu);
        }
        compteur++;
    }

    fclose(fichierLecture);
    fclose(fichierEcriture);

    remove("commentaire.txt");
    rename("temp.txt", "commentaires.txt");
}
