#ifndef SUPPORTS_H
#define SUPPORTS_H

typedef struct Support {
    int id_support;
    int id_module;
    char nom_support[50];
    char type_support[50];
    char format[50];
    struct Support* suivant;
} Support;

// Function declarations
void afficherSupportsParModule(int idModule, Support* listeSupports);
void lireEtAfficherSupportsParModule();
void afficherSupportsParModuleEtType(int idModule, char* type, Support* listeSupports);
void lireEtAfficherSupportsParModuleEtType();
int idExisteDeja(int idSupport);
void ajouterSupport();
void supprimerSupport(int id);

void telechargerSupport();

#endif // SUPPORTS_H
