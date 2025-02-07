#include "GestionOrdi.h"
#include "Affichage.h"
#include <stdio.h>
#include <string.h>

void initialiserGestionOrdi(struct GestionOrdi *gestionOrdi) {
    gestionOrdi->nombreOrdis = 0;

    // Initialise chaque ordinateur dans le tableau
    for (int i = 0; i < MAX_ORDIS; ++i) {
        initialiserOrdi(&gestionOrdi->listeOrdis[i], ""); // Vous pouvez initialiser le nom selon vos besoins
    }
}



void ajouterOrdi(struct GestionOrdi *gestionOrdi, const char *nom) {
    // Ajoute un ordinateur supplémentaire à la liste si l'espace est disponible
    if (gestionOrdi->nombreOrdis < MAX_ORDIS) {
        initialiserOrdi(&gestionOrdi->listeOrdis[gestionOrdi->nombreOrdis], nom);
        gestionOrdi->nombreOrdis++;
    } else {
    	customPrintf("La liste des ordinateurs est pleine, impossible d'ajouter un nouvel ordinateur.\n");
    }
}

void afficherOrdis(const struct GestionOrdi *gestionOrdi) {
	customPrintf("Liste des ordinateurs :\n");

    // Affiche les détails de chaque ordinateur dans le tableau
    for (int i = 0; i < gestionOrdi->nombreOrdis; ++i) {
    	customPrintf("Ordinateur %d - Nom : %s\n", i + 1, gestionOrdi->listeOrdis[i].nom);
    }
}

struct Ordi *getOrdiAtIndex(struct GestionOrdi *gestionOrdi, int index) {
    // Retourne le joueur à la position index si l'index est valide
    if (index >= 0 && index < gestionOrdi->nombreOrdis) {
        return &gestionOrdi->listeOrdis[index];
    } else {
    	customPrintf("Index hors limites. Aucun joueur trouvé à la position %d.\n", index);
        return NULL;
    }
}

struct Ordi *chercherOrdi(struct GestionOrdi *go, char *nom) {
    for (int i = 0; i < go->nombreOrdis; ++i) {
        if (strcmp(go->listeOrdis[i].nom, nom) == 0) {
            return &go->listeOrdis[i];
        }
    }

    // Retourner NULL si l'ordinateur n'est pas trouvé
    return NULL;
}



