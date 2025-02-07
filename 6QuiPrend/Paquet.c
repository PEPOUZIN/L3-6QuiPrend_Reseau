#include <stdio.h>
#include "Paquet.h"
#include "Affichage.h"
#include <stdlib.h>  // Pour utiliser la fonction rand
#include <time.h>

void initialiserPaquet(struct Paquet *paquet) {
    int i;
    paquet->indice=0;
    for (i = 0; i < NB_CARTES; ++i) {
        paquet->cartes[i].numero = i + 1;

        if ((i + 1) % 10 == 0) {
            paquet->cartes[i].teteDeBoeuf = 3;  // Cartes se terminant par 0
        }else if ((i + 1) == 55) {
            paquet->cartes[i].teteDeBoeuf = 7;  // Carte numéro 55
        }else if ((i + 1) % 10 == 5) {
            paquet->cartes[i].teteDeBoeuf = 2;  // Cartes se terminant par 5

        } else if ((i + 1) % 11 == 0) {
            paquet->cartes[i].teteDeBoeuf = 5;  // Doubles (comme 11, 22, etc.)
        } else {
            paquet->cartes[i].teteDeBoeuf = 1;  // Autres cartes
        }
    }
}

void afficherPaquet(const struct Paquet *paquet) {
    for (int i = 0; i < NB_CARTES; ++i) {
    	customPrintf("Carte %d - Numéro : %d, Têtes de Bœuf : %d\n", i + 1, paquet->cartes[i].numero, paquet->cartes[i].teteDeBoeuf);
    }
}
void melangerPaquet(struct Paquet *paquet) {
    srand((unsigned int)time(NULL));  // Initialiser le générateur de nombres aléatoires

    int i, j;
    struct Carte temp;
    for (i = NB_CARTES - 1; i > 0; --i) {
        j = rand() % (i + 1);  // Générer un index aléatoire entre 0 et i inclus

        // Échanger la carte à l'index i avec la carte à l'index aléatoire j
        temp = paquet->cartes[i];
        paquet->cartes[i] = paquet->cartes[j];
        paquet->cartes[j] = temp;
    }
}
struct Carte* distribuerCartes(struct Paquet *paquet) {
    struct Carte *listcarte = malloc(10 * sizeof(struct Carte));

    if (listcarte != NULL) {
        for (int i = paquet->indice; i < paquet->indice + 10; ++i) {
            listcarte[i - paquet->indice] = paquet->cartes[i];
        }

        paquet->indice = paquet->indice + 10;
    }

    return listcarte;
}
void libererListeCarte(struct Paquet *p) {
    free(p);
}

struct Carte retirerCarte(struct Paquet *p) {
    if (p->indice < NB_CARTES) {
        struct Carte carteRetiree = p->cartes[p->indice];
        p->indice++;
        return carteRetiree;
    } else {
        // Vous pouvez ajouter un traitement pour gérer le cas où toutes les cartes ont été retirées
        // Par exemple, réinitialiser l'indice pour permettre une nouvelle distribution
    	customPrintf("Erreur : Toutes les cartes ont été retirées du paquet.\n");
        // Vous pouvez également choisir de retourner une carte "vide" ou une carte spéciale pour indiquer l'erreur
        struct Carte carteVide = {0, 0};
        return carteVide;
    }
}


