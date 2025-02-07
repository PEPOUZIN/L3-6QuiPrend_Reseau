/*
 * GestionOrdiAmeliorer.c
 *
 *  Created on: 12 déc. 2023
 *      Author: stizr
 */

#include "GestionOrdiAmeliorer.h"
#include "Affichage.h"
#include <stdio.h>
#include <string.h>

void initialiserGestionOrdiAmeliorer(struct GestionOrdiAmeliorer *gestionOrdi) {
    gestionOrdi->nombreOrdis = 0;

    // Initialise chaque ordinateur dans le tableau
    for (int i = 0; i < MAX_ORDISA; ++i) {
        initialiserOrdiAmeliorer(&gestionOrdi->listeOrdis[i], ""); // Vous pouvez initialiser le nom selon vos besoins
    }
}



void ajouterOrdiAmeliorer(struct GestionOrdiAmeliorer *gestionOrdi, const char *nom) {
    // Ajoute un ordinateur supplémentaire à la liste si l'espace est disponible
    if (gestionOrdi->nombreOrdis < MAX_ORDISA) {
        initialiserOrdiAmeliorer(&gestionOrdi->listeOrdis[gestionOrdi->nombreOrdis], nom);
        gestionOrdi->nombreOrdis++;
    } else {
    	customPrintf("La liste des ordinateurs est pleine, impossible d'ajouter un nouvel ordinateur.\n");
    }
}

void afficherOrdisAmeliorer(const struct GestionOrdiAmeliorer *gestionOrdi) {
	customPrintf("Liste des ordinateurs :\n");

    // Affiche les détails de chaque ordinateur dans le tableau
    for (int i = 0; i < gestionOrdi->nombreOrdis; ++i) {
        printf("Ordinateur %d - Nom : %s\n", i + 1, gestionOrdi->listeOrdis[i].nom);
    }
}

struct OrdiAmeliorer *getOrdiAmeliorerAtIndex(struct GestionOrdiAmeliorer *gestionOrdi, int index) {
    // Retourne le joueur à la position index si l'index est valide
    if (index >= 0 && index < gestionOrdi->nombreOrdis) {
        return &gestionOrdi->listeOrdis[index];
    } else {
    	customPrintf("Index hors limites. Aucun joueur trouvé à la position %d.\n", index);
        return NULL;
    }
}

struct OrdiAmeliorer *chercherOrdiAmeliorer(struct GestionOrdiAmeliorer *go, char *nom) {
    for (int i = 0; i < go->nombreOrdis; ++i) {
        if (strcmp(go->listeOrdis[i].nom, nom) == 0) {
            return &go->listeOrdis[i];
        }
    }

    // Retourner NULL si l'ordinateur n'est pas trouvé
    return NULL;
}



