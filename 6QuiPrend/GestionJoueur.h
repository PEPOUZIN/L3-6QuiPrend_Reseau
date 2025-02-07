#ifndef GESTIONJOUEUR_H
#define GESTIONJOUEUR_H

#include "Joueur.h"

#define MAX_JOUEURS 10

// Structure pour la gestion des joueurs
struct GestionJoueur {
    struct Joueur listeJoueurs[MAX_JOUEURS]; // Tableau de joueurs
    int nombreJoueurs;                       // Nombre total de joueurs dans la liste
};

// Fonctions pour la gestion des joueurs
void initialiserGestionJoueur(struct GestionJoueur *gestionJoueur);
void ajouterJoueur(struct GestionJoueur *gestionJoueur, const char *nom);
void afficherJoueurs(const struct GestionJoueur *gestionJoueur);
struct Joueur *getJoueurAtIndex( struct GestionJoueur *gestionJoueur, int index);
struct Joueur* chercherJoueur(struct GestionJoueur *gj, char *nom);
#endif /* GESTIONJOUEUR_H */
