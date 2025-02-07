#ifndef ORDI_H
#define ORDI_H

#include "Paquet.h"

#define TAILLE_MAIN 10


struct Ordi {
    char nom[20];          // Nom de l'ordinateur
    struct Carte main[TAILLE_MAIN];  // Main de l'ordinateur
    int nbCarte;
    int score;
    int victoire;
    int defaite;
};

// Déclaration des fonctions pour l'ordinateur
void initialiserOrdi(struct Ordi *ordi, const char *nom);
void afficherMainOrdi(const struct Ordi *ordi);
void ajouterCarteMainOrdi(struct Ordi *ordi, struct Carte nouvelleCarte[10]);
struct Carte poserCarteAleatoire(struct Ordi *ordi);
void setScoreOrdi(struct Ordi *o, int i);
char* getNomOrdi(struct Ordi *o);
void setVictoireOrdi(struct Ordi *o);
void setDefaiteOrdi(struct Ordi *o);
#endif  // ORDI_H
