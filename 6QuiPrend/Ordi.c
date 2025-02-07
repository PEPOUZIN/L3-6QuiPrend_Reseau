#include <stdio.h>
#include "Ordi.h"
#include "Affichage.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initialiserOrdi(struct Ordi *ordi, const char *nom) {
	strcpy(ordi->nom, nom);
	ordi->nbCarte=0;
	// Initialisation de la main de l'ordinateur
	for (int i = 0; i < TAILLE_MAIN; ++i) {
		ordi->main[i].numero = 0;
		ordi->main[i].teteDeBoeuf = 0;

	}

	ordi->score = 0;
	ordi->victoire = 0;
	ordi->defaite = 0;

	// Ici, vous pouvez implémenter la distribution de cartes à l'ordinateur
	srand((unsigned int)time(NULL));
}

void afficherMainOrdi(const struct Ordi *ordi) {
	customPrintf("\nMain de l'ordinateur %s :\n", ordi->nom);
	for (int i = 0; i < ordi->nbCarte ; ++i) {
		customPrintf("Carte %d - Numéro : %d, Têtes de Bœuf : %d / %s\n", i , ordi->main[i].numero, ordi->main[i].teteDeBoeuf, (ordi->main[i].nom));
	}
	customPrintf("\n");
}
// Implémentez d'autres fonctions pour gérer les actions de l'ordinateur

void ajouterCarteMainOrdi(struct Ordi *o, struct Carte nouvelleCarte[10]) {
	for (int i = 0; i < 10; ++i) {
		o->main[i] = nouvelleCarte[i];
		strcpy(o->main[i].nom, o->nom);
		o->main[i].nom[sizeof(o->main[i].nom) - 1] = '\0';
	}
	o->nbCarte=10;
}


struct Carte poserCarteAleatoire(struct Ordi *ordi) {
	int indexCarte = rand() % ordi->nbCarte; // Sélection aléatoire d'une carte
	struct Carte carteJouee = ordi->main[indexCarte];

	// Retirer la carte sélectionnée de la main en décalant les cartes vers la gauche
	for (int i = indexCarte; i < TAILLE_MAIN - 1; ++i) {
		ordi->main[i] = ordi->main[i + 1];
	}
	ordi->main[TAILLE_MAIN - 1].numero = 0; // Marquer le dernier emplacement comme vide
	ordi->main[TAILLE_MAIN - 1].teteDeBoeuf = 0;
	ordi->nbCarte=ordi->nbCarte-1;
	return carteJouee;
}
void setScoreOrdi(struct Ordi *o, int i){
	o->score += i;
}

char* getNomOrdi(struct Ordi *o){
	return o->nom;
}

void setVictoireOrdi(struct Ordi *j){
	j->victoire+=1;
}

void setDefaiteOrdi(struct Ordi *j){
	j->defaite+=1;
}
