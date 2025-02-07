/*
 * Affichage.c
 *
 *  Created on: 12 déc. 2023
 *      Author: kyzun
 */
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Affichage.h"


void customPrintf(const char *format,...) {
    // Ouvrir (ou créer) le fichier "jeu.txt" en mode ajout (a)
    FILE *jeuFile = fopen("jeu.txt", "a");
    if (jeuFile == NULL) {
        perror("Erreur lors de l'ouverture ou de la création du fichier jeu.txt");
        // Gestion de l'erreur (vous pouvez choisir de quitter le programme ici si nécessaire)
        return;
    }


    // Utiliser un tableau pour stocker les arguments de format variable
    char buffer[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Imprimer sur le terminal
    printf("%s", buffer);

    // Écrire dans le fichier "jeu.txt"
    fprintf(jeuFile, "%s", buffer);
    fflush(jeuFile);  // Assurez-vous que l'écriture est réalisée immédiatement

    // Fermer le fichier
    fclose(jeuFile);
}


