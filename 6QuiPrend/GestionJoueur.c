#include "GestionJoueur.h"
#include "Affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialiserGestionJoueur(struct GestionJoueur *gestionJoueur) {
    gestionJoueur->nombreJoueurs = 0;

    // Initialise chaque joueur dans le tableau
    for (int i = 0; i < MAX_JOUEURS; ++i) {
        initialiserJoueur(&gestionJoueur->listeJoueurs[i], ""); // Vous pouvez initialiser le nom selon vos besoins
    }
}



void ajouterJoueur(struct GestionJoueur *gestionJoueur, const char *nom) {
    // Ajoute un joueur supplémentaire à la liste si l'espace est disponible
    if (gestionJoueur->nombreJoueurs < MAX_JOUEURS) {
        initialiserJoueur(&gestionJoueur->listeJoueurs[gestionJoueur->nombreJoueurs], nom);
        gestionJoueur->nombreJoueurs++;
    } else {
    	customPrintf("La liste des joueurs est pleine, impossible d'ajouter un nouveau joueur.\n");
    }
}

void afficherJoueurs(const struct GestionJoueur *gestionJoueur) {
	customPrintf("Liste des joueurs :\n");

    // Affiche les détails de chaque joueur dans le tableau
    for (int i = 0; i < gestionJoueur->nombreJoueurs; ++i) {
    	customPrintf("Joueur %d - Nom : %s\n", i + 1, gestionJoueur->listeJoueurs[i].nom);
    }
}

struct Joueur *getJoueurAtIndex( struct GestionJoueur *gestionJoueur, int index) {
    // Retourne le joueur à la position index si l'index est valide
    if (index >= 0 && index < gestionJoueur->nombreJoueurs) {
        return &gestionJoueur->listeJoueurs[index];
    } else {
    	customPrintf("Index hors limites. Aucun joueur trouvé à la position %d.\n", index);
        return NULL;
    }
}

struct Joueur* chercherJoueur(struct GestionJoueur *gj,  char *nom) {
    for (int i = 0; i < gj->nombreJoueurs; ++i) {
        if (strcmp(gj->listeJoueurs[i].nom, nom) == 0) {
            return &gj->listeJoueurs[i];
        }
    }

    // Retourner NULL si le joueur n'est pas trouvé
    return NULL;
}

