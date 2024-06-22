#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Etudiant {
    int idEtudiant;
    int idEtablissement;
    int idSemestre;
    char prenom[50];
    char nom[50];
    char email[100];
    char motDePasse[50];
} Etudiant;

// Fonction pour vérifier si l'email est présent dans le fichier des étudiants
bool verifierEmail(char email[]) {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return false;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        char emailFichier[100];
        sscanf(ligne, "%*d-%*d-%*d-%*[^-]-%*[^-]-%99[^-]", emailFichier);
        if (strcmp(emailFichier, email) == 0) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

// Fonction pour vérifier le mot de passe
bool verifierMotDePasse(char email[], char motDePasse[]) {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return false;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        char emailFichier[100], motDePasseFichier[50];
        sscanf(ligne, "%*d-%*d-%*d-%*[^-]-%*[^-]-%99[^-]-%49s", emailFichier, motDePasseFichier);
        if (strcmp(emailFichier, email) == 0 && strcmp(motDePasseFichier, motDePasse) == 0) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

// Fonction pour connecter l'utilisateur
void logInEtudiant() {
    char email[100], motDePasse[50];
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
        emailValide = verifierEmail(email);
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
        motDePasseValide = verifierMotDePasse(email, motDePasse);
        essaisMotDePasse++;
    } while (!motDePasseValide && essaisMotDePasse < 3);

    if (motDePasseValide) {
        printf("Bienvenue !\n");
    } else {
        printf("Nombre maximum d'essais atteint. Veuillez contacter l'administration.\n");
    }
}
