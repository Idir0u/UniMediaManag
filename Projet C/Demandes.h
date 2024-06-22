#ifndef DEMANDES_H
#define DEMANDES_H

typedef struct Demande{
    int ID;
    char contenu[100];
    char date[20];
    struct Demande* suivant;
}Demande;

void AjouterDemande(Demande** listeDemandes);
void chargerDemandesEtAfficher();
void supprimerDemande(int idDemande);
void ValiderEntrer();

#endif
