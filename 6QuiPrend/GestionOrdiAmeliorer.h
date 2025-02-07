#ifndef GESTIONORDIAMELIORER_H_
#define GESTIONORDIAMELIORER_H_

#include "OrdiAmeliorer.h"

#define MAX_ORDISA 10


struct GestionOrdiAmeliorer {
	struct OrdiAmeliorer listeOrdis[MAX_ORDISA]; // Tableau d'ordinateurs
	int nombreOrdis;
};
void initialiserGestionOrdiAmeliorer(struct GestionOrdiAmeliorer *gestionOrdi);
void ajouterOrdiAmeliorer(struct GestionOrdiAmeliorer *gestionOrdi, const char *nom);
void afficherOrdisAmeliorer(const struct GestionOrdiAmeliorer *gestionOrdi);
struct OrdiAmeliorer *getOrdiAmeliorerAtIndex(struct GestionOrdiAmeliorer *gestionOrdi, int index);
struct OrdiAmeliorer *chercherOrdiAmeliorer(struct GestionOrdiAmeliorer *gj, char *nom);
#endif /* GESTIONORDIAMELIORER_H_ */
