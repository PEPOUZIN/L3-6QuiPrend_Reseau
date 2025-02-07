/*
 * Plateau.c
 *
 *  Created on: 31 oct. 2023
 *      Author: stizr
 */

#include <stdio.h>
#include "Plateau.h"
#include "Carte.h"
#include "Affichage.h"
#include <stdlib.h>  // Pour utiliser la fonction rand
#include <time.h>


void AfficherPlateau(struct Plateau *p) {
	for (int i = 0; i < NB_LIGNES; ++i) {
		for (int j = 0; j < NB_COL; ++j) {  // Correction de la boucle conditionnelle de j
			struct Carte* c = p->cases[i][j];

			affichage(c);

		}
		customPrintf("\n");
	}
}

void ajouterCartePlateau(struct Plateau *p, struct Carte *c, int i) {

	int j;
	for (j = 0; j < NB_COL; j++) {  // Correction de la réutilisation de j (déjà déclaré dans la boucle for)

		if (p->cases[i][j] == NULL) {
			// Trouvé une colonne libre, placez la carte ici
			p->cases[i][j] = c;
			break;
		}
	}

	// Si j est égal à NB_COL, cela signifie que la ligne est pleine, et la carte n'a pas été placée.
	if (j == NB_COL) {
		// Gérer le cas où la ligne est pleine
		customPrintf("La ligne %d est pleine. La carte n'a pas été placée.\n", i);
	}
}

struct Carte meilleureCartePlateau(struct Plateau *p, struct Carte *c){
	struct Carte carte = {0,0};
	//int score = 0;
	int anciennediff = 105;
	int valeur = 0;
	int diff = 0;
	//int indicei = -1;
	int indicej = -1;
	int impossible = 0;
	// int meilleureValeur = 105;

	for (int i = 0; i < NB_LIGNES; i++) {
		diff = 0;
		//impossible=0;
		//indicej=0;
		// Notez que j < NB_COL-1 a été modifié à j < NB_COL
		for (int j = 0; j < NB_COL; j++) {
			if (p->cases[i][j] != NULL && p->cases[i][j+1]==NULL/*&& c->numero > p->cases[i][j]->numero*/) {
				if(c->numero > p->cases[i][j]->numero && anciennediff > c->numero -p->cases[i][j]->numero){
					valeur = p->cases[i][j]->numero;
					// On a trouvé un endroit pour insérer la carte
					//if(meilleureValeur > p->cases[i][j]->numero){
					indicej = j + 1;
					//meilleureValeur = p->cases[i][j]->numero;
					//}

				}
				else if(c->numero < p->cases[i][j]->numero){
					//printf("La carte n'a pas pu être placer");
					//printf("%d < %d\n", c->numero, p->cases[i][j]->numero);
					++impossible;
				}
			} else if (p->cases[i][j] == NULL && /*p->cases[i][j+1]!=NULL &&*/ p->cases[i][j-1] != NULL/*&& impossible==0*/) {
				// Il y a une case vide, calculons la différence
				diff = c->numero - valeur;
				//printf("%d\n",diff);
			} else if(impossible == 4){
				//printf("non");
				diff = 105;
			}
		}


		if (diff < anciennediff && diff>0 && impossible<4) {
			anciennediff = diff;
			//indicei = i;
		}
	}
	if(impossible==4 || indicej == 5){
		return carte;
	}

	struct Carte carteScore;
	setTeteDeBoeuf(&carteScore, c->teteDeBoeuf);
	setNumero(&carteScore, c->numero);
	return carteScore;


}

struct Carte ajouterCarteDansTab(struct Plateau *p, struct Carte *c) {
	struct Carte carte = {0,0};
	int anciennediff = 105;
	int valeur = 0;
	int diff = 0;
	int indicei = -1;
	int indicej = -1;
	int impossible = 0;

	for (int i = 0; i < NB_LIGNES; i++) {
		diff = 0;
		for (int j = 0; j < NB_COL; j++) {
			if (p->cases[i][j] != NULL && p->cases[i][j+1]==NULL/*&& c->numero > p->cases[i][j]->numero*/) {
				if(c->numero > p->cases[i][j]->numero && anciennediff > c->numero -p->cases[i][j]->numero){
					valeur = p->cases[i][j]->numero;
					indicej = j + 1;


				}
				else if(c->numero < p->cases[i][j]->numero){
					++impossible;
				}
			} else if (p->cases[i][j] == NULL && p->cases[i][j-1] != NULL) {
				// Il y a une case vide, calculons la différence
				diff = c->numero - valeur;
			} else if(impossible == 4){
				diff = 105;
			}
		}


		if (diff < anciennediff && diff>0 && impossible<4) {
			anciennediff = diff;
			indicei = i;
		}
	}
	//printf("%d : %d [%d,%d]\n", impossible, c->numero, indicei, indicej);
	if (indicei != -1 && indicej != -1 && indicej != 5) {
		p->cases[indicei][indicej] = c;
		//score = 0;
	}

	else if(impossible==4){

		carte = *c;
		return carte;
	}
	else if(indicej == 5){
		int score = calculScore(p, c, indicei);
		struct Carte carteScore;
		setTeteDeBoeuf(&carteScore, score);
		setNumero(&carteScore, 0);
		return carteScore;

	}
	return carte;
}

int calculScore(struct Plateau *p, struct Carte* c, int l) {
	// Supprimez ou ajustez le message de débogage
	//printf("Calcul score\n");

	int valeur = 0;



	// Calculer le score en parcourant la ligne avant le placement de la nouvelle carte
	for (int i = 0; i < 6; ++i) {
		if (p->cases[l][i] != NULL) {
			valeur += p->cases[l][i]->teteDeBoeuf;
			p->cases[l][i] = NULL;  // Mettre à NULL chaque case dans la ligne
		}
	}
	// Libérez la mémoire de la carte précédente (s'il y en a une)
	if (p->cases[l][0] != NULL) {
		free(p->cases[l][0]);
	}

	// Allouer dynamiquement la mémoire pour la nouvelle carte
	struct Carte *nouvelleCarte = (struct Carte *)malloc(sizeof(struct Carte));
	if (nouvelleCarte == NULL) {
		fprintf(stderr, "Erreur d'allocation de mémoire\n");
		exit(EXIT_FAILURE);
	}

	// Initialiser les propriétés de la nouvelle carte
	setTeteDeBoeuf(nouvelleCarte, c->teteDeBoeuf);
	setNumero(nouvelleCarte, c->numero);

	// Placer la nouvelle carte à la première position de la ligne
	p->cases[l][0] = nouvelleCarte;

	return valeur;
}










void initPlateau(struct Plateau *p){
	// Initialiser le plateau en mettant toutes les cases à NULL
	for (int i = 0; i < NB_LIGNES; ++i) {
		for (int j = 0; j < NB_COL; ++j) {
			p->cases[i][j] = NULL;
		}
	}
}

void libererPlateau(struct Plateau *p) {
	for (int i = 0; i < NB_LIGNES; ++i) {
		for (int j = 0; j < NB_COL; ++j) {
			if (p->cases[i][j] != NULL) {
				// Libérer la mémoire de chaque carte
				free(p->cases[i][j]);
			}
		}
	}
}

