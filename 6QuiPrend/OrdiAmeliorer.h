#ifndef ORDIAMELIORER_H_
#define ORDIAMELIORER_H_


#include "Paquet.h"
#include "Plateau.h"
#define TAILLE_MAIN 10


struct OrdiAmeliorer {
	char nom[20];          // Nom de l'ordinateur
	struct Carte main[TAILLE_MAIN];  // Main de l'ordinateur
	int nbCarte;
	int score;
	int victoire;
	int defaite;
};
void initialiserOrdiAmeliorer(struct OrdiAmeliorer *ordi, const char *nom);
void afficherMainOrdiAmeliorer(const struct OrdiAmeliorer *ordi);
void ajouterCarteMainOrdiAmeliorer(struct OrdiAmeliorer *ordi, struct Carte nouvelleCarte[10]);
struct Carte poserCarteAleatoireAmeliorer(struct OrdiAmeliorer *ordi, struct Plateau *p);
void setScoreOrdiAmeliorer(struct OrdiAmeliorer *o, int i);
char* getNomOrdiAmeliorer(struct OrdiAmeliorer *o);
void setVictoireOrdiAmeliorer(struct OrdiAmeliorer *o);
void setDefaiteOrdiAmeliorer(struct OrdiAmeliorer *o);


#endif /* ORDIAMELIORER_H_ */
