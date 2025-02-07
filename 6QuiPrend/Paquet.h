#ifndef PAQUET_H
#define PAQUET_H

#include "Carte.h"

#define NB_CARTES 104

struct Paquet {
    struct Carte cartes[NB_CARTES];
    int indice;
};

void initialiserPaquet(struct Paquet *paquet);
void afficherPaquet(const struct Paquet *paquet);
void melangerPaquet(struct Paquet *paquet);
struct Carte* distribuerCartes( struct Paquet *paquet);
void libererListeCarte(struct Paquet *p);
struct Carte retirerCarte(struct Paquet *p);
#endif  // PAQUET_H
