#ifndef COMMENTAIRES_H
#define COMMENTAIRES_H

typedef struct Commentaire {
    int ID;
    char contenu[100];
    char date[20];
    struct Commentaire* suivant;
}Commentaire;

void AjouterCommentaire(Commentaire** listeCommentaires);
void supprimerCommentaire(int idCommentaire);
void chargerCommentairesEtAfficher();
#endif
