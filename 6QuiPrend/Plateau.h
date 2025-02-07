#ifndef PLATEAU_H_
#define PLATEAU_H_
#include "carte.h"
#define NB_LIGNES 4
#define NB_COL 6


struct Plateau {
    //'lignes 6 colonnes, choisir seulement les lignes, on peut la vider et on recuper la derniere carte de la ligne pour la remettre aud ebut
    //choix de ligne joueur /ordi aleatoir

    //reset plateau
    //methode affichage

    struct Carte* cases[NB_LIGNES][NB_COL];
};
void initPlateau(struct Plateau *p);
void AfficherPlateau(struct Plateau *p);
void ajouterCartePlateau(struct Plateau *p, struct Carte *c, int ligne);
struct Carte ajouterCarteDansTab(struct Plateau *p, struct Carte *c);
int calculScore(struct Plateau *p, struct Carte *c, int l);
struct Carte meilleureCartePlateau(struct Plateau *p, struct Carte *c);

#endif /* PLATEAU_H_ */
