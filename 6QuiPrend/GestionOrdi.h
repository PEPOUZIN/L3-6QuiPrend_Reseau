#ifndef GESTIONORDI_H
#define GESTIONORDI_H

#include "Ordi.h"

#define MAX_ORDIS 10

// Structure pour la gestion des ordinateurs
struct GestionOrdi {
    struct Ordi listeOrdis[MAX_ORDIS]; // Tableau d'ordinateurs
    int nombreOrdis;                   // Nombre total d'ordinateurs dans la liste
};

// Fonctions pour la gestion des ordinateurs
void initialiserGestionOrdi(struct GestionOrdi *gestionOrdi);
void ajouterOrdi(struct GestionOrdi *gestionOrdi, const char *nom);
void afficherOrdis(const struct GestionOrdi *gestionOrdi);
struct Ordi *getOrdiAtIndex(struct GestionOrdi *gestionOrdi, int index);
struct Ordi *chercherOrdi(struct GestionOrdi *gj, char *nom);
#endif /* GESTIONORDI_H */
