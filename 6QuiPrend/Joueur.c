#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Joueur.h"
#include "Affichage.h"
#include "Carte.h"

void initialiserJoueur(struct Joueur *j, const char *nom) {
    j->nbCarte = 0;
    strcpy(j->nom, nom);

    // Initialisation de la main du joueur
    for (int i = 0; i < MAIN_TAILLE_MAX; ++i) {
        j->main[i].numero = 0;
        j->main[i].teteDeBoeuf = 0;
    }

    j->score = 0;
    j->victoire = 0;
    j->defaite = 0;


}

void afficherMainJoueur(const struct Joueur *j) {
	customPrintf("Main du Joueur %s :\n", j->nom);
    for (int i = 0; i < j->nbCarte; ++i) {
    	customPrintf("Carte %d - Numéro : %d, Têtes de Bœuf : %d / %s\n", i, j->main[i].numero, j->main[i].teteDeBoeuf, (j->main[i].nom));
    }
}

void ajouterCarteMainJoueur(struct Joueur *j, struct Carte nouvelleCarte[10]) {
    for (int i = 0; i < 10; ++i) {
        j->main[i] = nouvelleCarte[i];
        // Assurez-vous que le champ nom est suffisamment grand pour contenir le nom du joueur
        strcpy(j->main[i].nom, j->nom);
        j->main[i].nom[sizeof(j->main[i].nom) - 1] = '\0';
    }
    j->nbCarte=10;
}

struct Carte poserCarteJoueur(struct Joueur *j, int c) {
    int indexCarte = c % MAIN_TAILLE_MAX;
    struct Carte carteJouee = j->main[indexCarte];

    // Retirer la carte sélectionnée de la main en décalant les cartes vers la gauche
    for (int i = indexCarte; i < j->nbCarte - 1; ++i) {
        j->main[i] = j->main[i + 1];
    }

    // Marquer le dernier emplacement comme vide
    j->main[j->nbCarte - 1].numero = 0;
    j->main[j->nbCarte - 1].teteDeBoeuf = 0;
    j->nbCarte--;

    return carteJouee;
}
void setScoreJoueur(struct Joueur *j, int i){
	j->score += i;
}

char* getNomJoueur(struct Joueur *j){
	return j->nom;
}

void setVictoire(struct Joueur *j){
	j->victoire+=1;
}

void setDefaite(struct Joueur *j){
	j->defaite+=1;
}
