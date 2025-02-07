#include "Carte.h"
#include "Affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNumero(const struct Carte *carte) {
    return carte->numero;
}

int getTeteDeBoeuf(const struct Carte *carte) {
    return carte->teteDeBoeuf;
}

void setNumero(struct Carte *carte, int nouveauNumero) {
    carte->numero = nouveauNumero;
}

void setTeteDeBoeuf(struct Carte *carte, int nouvellesTetes) {
    carte->teteDeBoeuf = nouvellesTetes;
}
void affichage(const struct Carte *carte) {
    if (carte != NULL) {
        //int teteDeBoeuf = carte->teteDeBoeuf;

    	customPrintf( "| %d* %d | ",getTeteDeBoeuf(carte), getNumero(carte));;
    } else {
    	customPrintf( "|  vide  |");
    }
}


void setNom(struct Carte *c,  char *n) {
    // Vérifiez si la carte n'est pas NULL et si la chaîne de caractères n'est pas NULL (si nécessaire)
    if (c != NULL && n != NULL) {
        // Utilisez strncpy pour copier la chaîne avec une limite
        strncpy(c->nom, n, sizeof(c->nom) - 1);
        // Assurez-vous que la chaîne est terminée par un null-terminator
        c->nom[sizeof(c->nom) - 1] = '\0';
    }
}


