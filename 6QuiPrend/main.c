/*
 * main.c
 *
 *  Created on: 6 déc. 2023
 *      Author: stizr
 */


#include <stdio.h>
#include <stdlib.h>
#include "Paquet.h"
#include "Ordi.h"
#include "Carte.h"
#include "Plateau.h"
#include "Affichage.h"
#include "Partie.h"

int main() {

    struct Partie partie;

    Jeu(&partie);


    	const char *c = "pandoc jeu.txt -o jeuPdf.pdf --pdf-engine=pdflatex";
    	// Exécution de la commande via le shell
    	int r = system(c);
    	// Vérification du code de retour
    	if (r == 0) {
    	    printf("La conversion a réussi.\n");
    	} else {
    	    printf("Erreur lors de la conversion. Code de retour : %d\n", r);
    	}


    return 0;
}


