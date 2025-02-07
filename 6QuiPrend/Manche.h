#ifndef MANCHE_H_
#define MANCHE_H_

#include "Joueur.h"
#include "Ordi.h"
#include "Plateau.h"
#include "GestionOrdi.h"
#include "GestionJoueur.h"
#include "GestionOrdiAmeliorer.h"
#include <stdbool.h>

struct Manche {
	struct Paquet paquet;
	int fin ;
	struct Carte *listeCarteAJouer[10];
};

void initialiserListeCarteAJouer(struct Manche *manche);
struct Carte recupererElement(struct Manche *manche, int i);
void insererCarte(struct Manche *manche, int i, struct Carte *nouvelleCarte);


//FONCTIONS DE BASE
int effectuerManche(struct Manche *manche, struct Plateau *p, struct GestionJoueur *listjoueur, struct GestionOrdi *listo);
void distribuerJeux(struct GestionJoueur *listjoueur, struct GestionOrdi *listordinateurs, struct Manche *manche);
void triListe(struct Manche *m,struct GestionJoueur *gj, struct GestionOrdi *go);
void afficherListeCarteAJouer(struct Manche *manche,struct GestionJoueur *gj, struct GestionOrdi *go );

//FONCTIONS AMELIORER
int effectuerMancheAmeliorer(struct Manche *manche, struct Plateau *p, struct GestionJoueur *listjoueur, struct GestionOrdiAmeliorer *listo);
void distribuerJeuxAmeliorer(struct GestionJoueur *listjoueur, struct GestionOrdiAmeliorer *listordinateurs, struct Manche *manche);
void triListeAmeliorer(struct Manche *m, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go);
void afficherListeCarteAJouerAmeliorer(struct Manche *manche,struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go );




#endif /* MANCHE_H_ */
