#ifndef JOUEUR_H
#define JOUEUR_H
#include "Carte.h"
#define MAIN_TAILLE_MAX 10


struct Joueur {
    char nom[20];          // Nom de l'ordinateur
    struct Carte main[MAIN_TAILLE_MAX];  // Main de l'ordinateur
    int nbCarte;
    int score;
    int victoire;
    int defaite;
};



// Déclaration des fonctions pour l'ordinateur
void initialiserJoueur(struct Joueur *j, const char *nom);
void afficherMainJoueur(const struct Joueur *j);
void ajouterCarteMainJoueur(struct Joueur *j, struct Carte nouvelleCarte[10]);
struct Carte poserCarteJoueur(struct Joueur *j, int carte);
void setScoreJoueur(struct Joueur *j, int i);
char* getNomJoueur(struct Joueur *j);
void setVictoire(struct Joueur *j);
void setDefaite(struct Joueur *j);
#endif // JOUEUR_H



