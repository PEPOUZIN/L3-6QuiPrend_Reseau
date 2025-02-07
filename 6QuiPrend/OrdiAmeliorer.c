/*
 * OrdiAmeliorer.c
 *
 *  Created on: 12 déc. 2023
 *      Author: stizr
 */

#include "OrdiAmeliorer.h"

#include <stdio.h>
#include "Ordi.h"
#include "Affichage.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initialiserOrdiAmeliorer(struct OrdiAmeliorer *ordi, const char *nom) {
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

}

void afficherMainOrdiAmeliorer(const struct OrdiAmeliorer *ordi) {
	customPrintf("\nMain de l'ordinateur %s :\n", ordi->nom);
	for (int i = 0; i < ordi->nbCarte ; ++i) {
		customPrintf("Carte %d - Numéro : %d, Têtes de Bœuf : %d\n", i , ordi->main[i].numero, ordi->main[i].teteDeBoeuf);
	}
	customPrintf("\n");

}

void ajouterCarteMainOrdiAmeliorer(struct OrdiAmeliorer *o, struct Carte nouvelleCarte[10]) {
	for (int i = 0; i < 10; ++i) {
		o->main[i] = nouvelleCarte[i];
		strcpy(o->main[i].nom, o->nom);
		o->main[i].nom[sizeof(o->main[i].nom) - 1] = '\0';
	}
	o->nbCarte=10;
}

struct Carte poserCarteAleatoireAmeliorer(struct OrdiAmeliorer *ordi, struct Plateau *p) {
	int choix = 0;
	int indexCarte = -1;
	struct Carte cartesJouer[ordi->nbCarte];

	for (int i = 0; i < ordi->nbCarte; ++i) {
		struct Carte c = meilleureCartePlateau(p, &ordi->main[i]);
		if (c.numero != 0) {
			cartesJouer[choix] = c;
			choix++;
		}
	}

	if (choix == 0) {
		// Aucune carte jouable, choisir une au hasard
		indexCarte = rand() % ordi->nbCarte;
		for (int i = indexCarte; i < ordi->nbCarte - 1; ++i) {
			ordi->main[i] = ordi->main[i + 1];
		}
		// Si aucune carte n'est jouable, marquer le dernier emplacement comme vide
		ordi->main[ordi->nbCarte - 1].numero = 0;
		ordi->main[ordi->nbCarte - 1].teteDeBoeuf = 0;
		ordi->nbCarte--;
		return ordi->main[indexCarte];
	} else {
		// Choisir une carte parmi celles jouables
		indexCarte = rand() % choix;

		// Retrouver l'indice de la carte dans la main originale
		int index = -1;
		for (int i = 0; i < ordi->nbCarte; ++i) {
			if (cartesJouer[indexCarte].numero == ordi->main[i].numero) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			// Déplacer les cartes jouées vers la fin de la main
			for (int i = index; i < ordi->nbCarte - 1; ++i) {
				ordi->main[i] = ordi->main[i + 1];
			}

			// Marquer le dernier emplacement comme vide
			ordi->main[ordi->nbCarte - 1].numero = 0;
			ordi->main[ordi->nbCarte - 1].teteDeBoeuf = 0;

			// Réduire le compte après le déplacement
			ordi->nbCarte = ordi->nbCarte - 1;

			return cartesJouer[indexCarte];
		}
	}

	ordi->main[ordi->nbCarte - 1].numero = 0;
	ordi->main[ordi->nbCarte - 1].teteDeBoeuf = 0;

	// Réduire le compte après le déplacement
	ordi->nbCarte = ordi->nbCarte - 1;
	// Retourner une carte vide
	return ordi->main[0];
}



void setScoreOrdiAmeliorer(struct OrdiAmeliorer *o, int i){
	o->score += i;
}

char* getNomOrdiAmeliorer(struct OrdiAmeliorer *o){
	return o->nom;
}

void setVictoireOrdiAmeliorer(struct OrdiAmeliorer *o){
	o->victoire+=1;
}
void setDefaiteOrdiAmeliorer(struct OrdiAmeliorer *o){
	o->defaite+=1;
}
