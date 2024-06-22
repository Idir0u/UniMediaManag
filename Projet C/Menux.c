#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "professeurs.h"
#include "etudiants.h"
#include "filieres.h"
#include "departements.h"
#include "semestres.h"
#include "modules.h"
#include "supports.h"
#include "niveaux.h"
#include "etablissements.h"
#include "SaisirChaine.h"
#include "Commentaires.h"
#include "Demandes.h"
#include "Menux.h"

int verifierExistence(int *T, int taille, int valeur) {
    for (int i = 0; i < taille; i++) {
        if (T[i] == valeur) {
            return 0; // L'entier existe dans le tableau
        }
    }
    return 1; // L'entier n'existe pas dans le tableau

}

void Menu0(){
    int opt;
    printf("\nBonjour, et bienvenue sur la plateforme e-learnig d'universite\n");
    do{
        printf("\nChoisissez votre mode de navigation\n1: etudiant\t2: professeur\nChoix :");
        scanf("%d",&opt);
    }while( (opt != 1) && (opt !=2) );
    // rechercher si l'utisateur un professeur dans ce cas existe dans l'universite
    if(opt == 2)
    {
        logInProf();
    }
    else if(opt == 1)
    {
        logInEtudiant();
    }
    MenuChoixEtablissement(opt);

}
void MenuChoixEtablissement(int opt){
    int idEtab;
    int i;
    int *T;

    do{
        Afficheetablissement(&T,&i);
        printf("\nSaisir l'ID de l'etablissement : ");
        scanf("%d", &idEtab);
    }while(verifierExistence(T,i,idEtab));
    // rechercher si l'utisateur un etudiant dans cette existe dans l'etablissement choisi
    if(opt == 1)
    {
        MenuChoixNiveau(idEtab);
    }
    if(opt == 2)
        MenuChoixDepartement(idEtab);
}
//-----------------------------------------------------------------/
void MenuChoixDepartement(int idEtab)
{
    int id_Departement, choix;
    int i;
    int *T=NULL;
    do{
        AfficherDepartement(idEtab,&T,&i);
        if (i == 0) {
            printf("\nAucune Departement n'est disponible pour cet etablissement.");
            printf("\nSaisir 1 pour retourner à la liste des etablissement.");
            printf("\nSaisir un autre nombre pour quitter le menu:");
            scanf("%d", &choix);

            if (choix == 1) {
                MenuChoixEtablissement(2);
                return;
            } else {
                printf("\nVous avez choisi de quitter le menu.");
                free(T);
                return;
            }
        }
        printf("\n Saisir l'id de la Departement : ");
        scanf("%d", &id_Departement);
    }while(verifierExistence(T,i,id_Departement));
    free(T);

    MenuChoixFiliere(id_Departement,"",2,idEtab);
}
//-------------------------------------------------------------------//
void MenuChoixNiveau(int idEtab)
{
    int niv;
    int i;
    int *T=NULL;
    char S[4][20]={"license", "master", "doctorat", "Cycle_ingenieur"};
    char niveau[20];
    do{
        AfficherNiveau(&T,&i);
        printf("\nSaisir le Niveau : ");
        scanf("%d",&niv);
    }while(verifierExistence(T,i,niv));

    free(T);
    strcpy(niveau,S[niv-1]);
    MenuChoixFiliere(0,niveau,1,idEtab);
}
//-------------------------------------------------------------------------/
void MenuChoixFiliere(int id_Departement, char *Niveau, int opt, int idEtab) {
    FILE *file = fopen("Filieres.txt", "r");

    if (file == NULL) {
        perror("\nErreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int choix;
    int id_filiere;
    int i;
    int *T = NULL;

    if (opt == 2) { // professeur
        do {
            AfficheFiliere_par_Departement(file, id_Departement, &T, &i);

            if (i > 0) {
                printf("\nSaisir l'id de la filiere : ");
                scanf("%d", &id_filiere);
            }

        } while (i > 0 && verifierExistence(T, i, id_filiere));

        if (i == 0) {
            printf("\nAucune filiere n'est disponible pour ce departement.");
            printf("\nSaisir 1 pour retourner à la liste des departements.");
            printf("\nSaisir un autre nombre pour quitter le menu.");
            scanf("%d", &choix);

            if (choix == 1) {
                fclose(file);
                MenuChoixDepartement(idEtab);
                return;
            } else {
                printf("\nVous avez choisi de quitter le menu.");
                fclose(file);
                free(T);
                return;
            }
        }
    } else if (opt == 1) { // etudiant
        do {
            AfficheFiliere_par_Niveau(file, idEtab, Niveau, &T, &i);

            if (i > 0) {
                printf("\nSaisir l'id de la filiere : ");
                scanf("%d", &id_filiere);
            }

        } while (i > 0 && verifierExistence(T, i, id_filiere));

        if (i == 0) {
            printf("\nles filiere avec le niveau choisi ne sont pas encore ajouter");
            printf("\nSaisir 1 pour retourner au liste des Niveaux");
            printf("\nSaisir un nombre quelconque pour quitter le menu : ");
            scanf("%d", &choix);

            if (choix == 1) {
                MenuChoixNiveau(idEtab);
                return;
            } else {
                printf("\nVous avez choisi de quitter le menu");
                return;
            }
        }
    }

    MenuChoixSemestres(id_filiere, opt, id_Departement, Niveau, idEtab);

    fclose(file);
    free(T);
}

//--------------------------------------------------------------------//
void MenuChoixSemestres(int id_filiere,int opt,int id_Departement,char *Niveau,int idEtab)
{
    int id_semestre;
    int i;
    int choix;
    int *T=NULL;
    do{
    AfficheSemestres(id_filiere,&T,&i);
    if(i == 0)
        {
            printf("\nles semestre de cette filiere ne sont pas encore ajouter");
            printf("\nSaisir 1 pour retourner au liste des filieres");
            printf("\nSaisir numbre quelconque pour quitter le menu:");
            scanf("%d",&choix);
            if(choix == 1)
            {
                MenuChoixFiliere(id_Departement,Niveau,opt,idEtab);
                return;
            }
            else{
                printf("Vous avez choisissiez de quitter le menu");
                return;
            }

        }
    printf("\n Saisir l'id du semestre : ");
    scanf("%d", &id_semestre);
    }while(verifierExistence(T,i,id_semestre));
    MenuChoixModules(id_semestre,opt,id_filiere,id_Departement,Niveau,idEtab);
}
//-------------------------------------------//
void MenuChoixModules(int id_semestre,int opt,int id_filiere,int id_Departement,char* Niveau,int idEtab)
{
    int i;
    int *T=NULL;

    AfficheModules(id_semestre,&T,&i);


    if(opt == 1)
        {
            Commentaire *listeCommentaires = NULL;
            Demande *listeDemandes = NULL;
            Support* listeSupports = NULL;
            MenuEtudiant(&listeCommentaires, &listeDemandes, &listeSupports);
        }
    else if(opt == 2)
        {

            MenuProf();
        }
}
void MenuEtudiant(Commentaire** listeCommentaires, Demande** listeDemandes, Support** listeSupports) {
    int etape = 1;
    int choix;

    while (etape <= 2) {
        switch (etape) {
            case 1: // Choix d'affichage
                printf("\nvous voulez Afficher les supports :\n");
                printf("1 - par module \n");
                printf("2 - par module et type\n");
                printf("Faites votre choix : ");
                scanf("%d", &choix);
                if (choix == 1) {
                    lireEtAfficherSupportsParModule();
                } else if (choix == 2) {
                    lireEtAfficherSupportsParModuleEtType();
                } else {
                    // Gérer le cas où l'entrée n'est pas valide
                }
                break;

            case 2: // Choix d'action pour le support
                printf("Le support que vous cherchez est-il disponible ? (1 pour Oui / 2 pour Non) : \t");
                scanf("%d", &choix);

                if (choix == 1) {
                    printf("\nvous voulez télécharger un support :\n");
                    telechargerSupport();
                    printf("\nvous pouvez ajouter un commentaire sur le support:\n");
                    printf("1 - Ajouter un commentaire\n");
                    printf("2 - Quitter\n");
                    scanf("%d", &choix);

                    if (choix == 1) {
                        AjouterCommentaire(listeCommentaires);
                        printf("\nvotre commentaire est enregistre ");
                    } else {
                        // Gérer le cas où l'entrée n'est pas valide
                    }
                } else if (choix == 2) {
                    AjouterDemande(listeDemandes);
                    printf("\nvotre Demande est enregistre ");
                } else {
                    // Gérer le cas où l'entrée n'est pas valide
                }
                break;

            default:
                // Gérer le cas où l'entrée n'est pas valide pour l'étape
                break;
        }

        etape++;
    }
}

void MenuProf() {
    int choix;

    do {
        printf("\n1 - Ajouter un support\n");
        printf("2 - Supprimer un support\n");
        printf("3 - Afficher la liste des commentaires\n");
        printf("4 - Afficher les demandes\n");
        printf("0 - Quitter\n");
        printf("Faites votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterSupport();
                break;
            case 2: {
                int id;
                printf("\nSaisir l'ID du support à supprimer : ");
                scanf("%d", &id);
                supprimerSupport(id);
                break;
            }
            case 3: {
                chargerCommentairesEtAfficher();
                int choixSupp;
                printf("\nVoulez-vous supprimer un commentaire ? (1 pour Oui / 0 pour Non) : ");
                scanf("%d", &choixSupp);
                if (choixSupp == 1) {
                    int idCommentaire;
                    printf("\nSaisir l'ID du commentaire à supprimer : ");
                    scanf("%d", &idCommentaire);
                    supprimerCommentaire(idCommentaire);
                }
                break;
            }
            case 4: {
                chargerDemandesEtAfficher();
                int choixSupp;
                printf("\nVoulez-vous supprimer une demande ? (1 pour Oui / 0 pour Non) : ");
                scanf("%d", &choixSupp);
                if (choixSupp == 1) {
                    int idDemande;
                    printf("\nSaisir l'ID de la demande à supprimer : ");
                    scanf("%d", &idDemande);
                    supprimerDemande(idDemande);
                } /*else if (choixSupp == 0) {
                    ajouterSupport();
                }*/
                break;
            }
            case 0:
                printf("\nFermeture du programme Professeur.\n");
                break;
            default:
                printf("\nChoix non valide.\n");
                break;
        }
    }while (choix != 0);
}
