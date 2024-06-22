#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Professeur {
    int idProfesseur;
    char nom[50];
    char email[50];
    char motDePasse[20];
} Professeur;

bool verifierEmailProfesseur(char email[]) {
    FILE *f = fopen("Professeurs.txt", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return false;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        char emailFichier[50];
        sscanf(ligne, "%*d-%*[^-]-%49[^-]", emailFichier);
        if (strcmp(emailFichier, email) == 0) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

bool verifierMotDePasseProfesseur(char email[], char motDePasse[]) {
    FILE *f = fopen("Professeurs.txt", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return false;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        char emailFichier[50], motDePasseFichier[20];
        sscanf(ligne, "%*d-%*[^-]-%49[^-]-%19s", emailFichier, motDePasseFichier);
        if (strcmp(emailFichier, email) == 0 && strcmp(motDePasseFichier, motDePasse) == 0) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

void logInProf() {
    char email[50], motDePasse[20];
    bool emailValide = false;
    int essaisEmail = 0;
    do {
        if (essaisEmail > 0) {
            printf("Email incorrect. Veuillez réessayer : ");
            scanf("%s", email);
        } else {
            printf("Veuillez saisir votre email : ");
            scanf("%s", email);
        }
        emailValide = verifierEmailProfesseur(email);
        essaisEmail++;
    } while (!emailValide && essaisEmail < 3);

    if (!emailValide) {
        printf("Nombre maximum d'essais atteint. Veuillez contacter l'administration.\n");
        return;
    }

    bool motDePasseValide = false;
    int essaisMotDePasse = 0;
    do {
        if (essaisMotDePasse > 0) {
            printf("Mot de passe incorrect. Veuillez réessayer : ");
            scanf("%s", motDePasse);
        } else {
            printf("Veuillez saisir votre mot de passe : ");
            scanf("%s", motDePasse);
        }
        motDePasseValide = verifierMotDePasseProfesseur(email, motDePasse);
        essaisMotDePasse++;
    } while (!motDePasseValide && essaisMotDePasse < 3);

    if (motDePasseValide) {
        printf("Bienvenue Professeur !\n");
    } else {
        printf("Nombre maximum d'essais atteint. Veuillez contacter l'administration.\n");
    }
}
