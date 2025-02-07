#ifndef PARTIE_H_
#define PARTIE_H_

#include "Joueur.h"
#include "Ordi.h"
#include "GestionJoueur.h"
#include "GestionOrdi.h"
#include "GestionOrdiAmeliorer.h"
#include "Manche.h"
#include "Plateau.h"

#define MAX_JOUEURS 10 // Choisissez une valeur maximale pour le nombre de joueurs
#define MAX_ORDIS 10   // Choisissez une valeur maximale pour le nombre d'ordinateurs
#define MAX_MANCHES 50 // Choisissez une valeur maximale pour le nombre de manches

struct Partie {
    struct GestionJoueur gestionJoueur;
    struct GestionOrdi gestionOrdi;
    struct GestionOrdiAmeliorer gestionOrdiAmeliorer;
    struct Manche manches[MAX_MANCHES];
    struct Plateau plateau;
};


void Jeu(struct Partie *p);

void initialiserPartie(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdi *go, struct Plateau *plateau);
int trouverPlusGrosScore(struct Partie * p, struct GestionJoueur *gj, struct GestionOrdi *go);
void ecrireResult(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdi *go,struct GestionOrdiAmeliorer *gm);

void mettreAJourVictoireDefaiteOrdi(struct Ordi *ordi);
void mettreAJourVictoireDefaite(struct Joueur *j);
void mettreAJourVictoireDefaiteOrdiAmeliorer(struct OrdiAmeliorer *ordi);



void initialiserPartieAmeliorer(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go, struct Plateau *plateau);
int trouverPlusGrosScoreAmeliorer(struct Partie *p, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go);
//void mettreAJourVictoireDefaiteOrdiAmeliorer(struct OrdiAmeliorer *ordi);



#endif /* PARTIE_H_ */
