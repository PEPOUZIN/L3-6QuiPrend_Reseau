#include "Partie.h"
#include "Joueur.h"
#include "GestionJoueur.h"
#include "GestionOrdi.h"
#include "Manche.h"
#include <stdio.h>
#include <string.h> // Ajoutez cette ligne en haut du fichier
#include <stdlib.h>
#include "Affichage.h"


//On initilalise la partie avec des Joueurs et des ordis simple
void initialiserPartie(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdi *go, struct Plateau *plateau) {
	partie->plateau = *plateau; // Initialiser le plateau
	partie->gestionJoueur = *gj;// Initialiser gestionJouer
	partie->gestionOrdi = *go;// Initialiser GestionOrdi

	//On veut que le score d'une des Personnes soit égale à 66 ou plus afin d'arrêter la boucle.
	for (int i = 0; i < 100; ++i) {
		effectuerManche(&partie->manches[i], &partie->plateau, &partie->gestionJoueur, &partie->gestionOrdi);
		if (trouverPlusGrosScore(partie, &partie->gestionJoueur, &partie->gestionOrdi) >= 66) {
			customPrintf("Fin de partie:\n");

			for(int i= 0; i<gj->nombreJoueurs;++i){
				mettreAJourVictoireDefaite(&partie->gestionJoueur.listeJoueurs[i]);
			}
			for(int i= 0; i<go->nombreOrdis;++i){
				mettreAJourVictoireDefaiteOrdi(&partie->gestionOrdi.listeOrdis[i]);
			}


			ecrireResult(partie, &partie->gestionJoueur, &partie->gestionOrdi,&partie->gestionOrdiAmeliorer);

			return;
		}
	}
}


//Fonction qui permet de lancer le jeu avec différents nombres de personnes
void Jeu(struct Partie *p) {
	struct Plateau plateau;
	struct GestionOrdi go;
	struct GestionJoueur gj;
	p->gestionJoueur = gj;
	p->gestionOrdi = go;
	p->plateau = plateau;

	initialiserGestionJoueur(&p->gestionJoueur);
	initialiserGestionOrdi(&p->gestionOrdi);

	int x = -1;
	int nbPersonne = -1;

	int y = -1;
	int nbJoueur = -1;

	int z = -1;
	int partieAmeliorer = -1;

	customPrintf("Bienvenue sur le 6 Qui Prend\n\nVeuillez choisir le nombre de Personnes total de la Partie:\n\n");

	while (x == -1) {

		fflush(stdout);
		scanf("%d", &nbPersonne);

		if (nbPersonne <= 0 || nbPersonne > 10) {
			customPrintf("Veuillez choisir un nombre entre 1 et 10!\n");
		} else {
			x = 0;
		}
	}

	customPrintf("Veuillez choisir le nombre de Joueurs afin de combler le reste par des Ordinateurs\n\n");

	while (y == -1) {

		fflush(stdout);
		scanf("%d", &nbJoueur);

		if (nbJoueur < 0 || nbJoueur > nbPersonne) {
			customPrintf("Veuillez choisir un nombre entre 1 et %d!\n\n", nbPersonne);
		} else {
			y = 0;
		}
	}

	customPrintf("Voulez-vous comblez la partie avec des Ordis Améliorés?\n\n1:Oui                       2:Non\n\n");

	while (z == -1) {

		fflush(stdout);
		scanf("%d", &partieAmeliorer);

		if (partieAmeliorer == 1 || partieAmeliorer == 2) {
			z = 0;
		} else {
			customPrintf("Veuillez choisir un nombre entre 1 et 2\n\n");
		}
	}

	int nbOrdi = nbPersonne - nbJoueur;

	for (int i = 0; i < nbJoueur; ++i) {
		bool nomValide = false;

		while (!nomValide) {
			customPrintf("Veuillez choisir un nom pour le Joueur %d:\n", i+1);
			fflush(stdout);

			scanf("%s", p->gestionJoueur.listeJoueurs[i].nom);

			// Vérifier si le nom est déjà utilisé
			nomValide = true;
			for (int j = 0; j < i; ++j) {
				if (strcmp(p->gestionJoueur.listeJoueurs[i].nom, p->gestionJoueur.listeJoueurs[j].nom) == 0) {
					customPrintf("Ce nom est déjà utilisé. Veuillez choisir un autre.\n");
					nomValide = false;
					break;
				}
			}
		}
		if (nomValide == true) {
			ajouterJoueur(&p->gestionJoueur, p->gestionJoueur.listeJoueurs[i].nom);
		}
	}


	if(partieAmeliorer == 2){

		for (int i = 0; i < nbOrdi; ++i) {
			char nom[30];
			sprintf(nom, "Bot n°%d", i+1);

			ajouterOrdi(&p->gestionOrdi, nom);
		}

		initialiserPartie(p, &p->gestionJoueur, &p->gestionOrdi, &p->plateau);

	}
	else{
		for (int i = 0; i < nbOrdi; ++i) {
			char nom[30];
			sprintf(nom, "Bot Amélioré n°%d", i+1);

			ajouterOrdiAmeliorer(&p->gestionOrdiAmeliorer, nom);
		}
		initialiserPartieAmeliorer(p, &p->gestionJoueur, &p->gestionOrdiAmeliorer, &p->plateau);
	}

}


//On parcourt la liste des Personnes afin de chercher le + gros scores d'entres elles
int trouverPlusGrosScore(struct Partie *p, struct GestionJoueur *gj, struct GestionOrdi *go) {
	int plusGrosScore = 0;
	char* nom = "DefaultPlayerName";  // Initialize with a default value

	for (int i = 0; i < gj->nombreJoueurs; ++i) {
		if (gj->listeJoueurs[i].score > plusGrosScore) {
			plusGrosScore = gj->listeJoueurs[i].score;
			nom = gj->listeJoueurs[i].nom;  // Update nom with the player's name
		}
	}

	for (int i = 0; i < go->nombreOrdis; ++i) {
		if (go->listeOrdis[i].score > plusGrosScore) {
			plusGrosScore = go->listeOrdis[i].score;
			nom = go->listeOrdis[i].nom;  // Update nom with the computer's name
		}
	}
	return plusGrosScore;
}


void mettreAJourVictoireDefaite(struct Joueur *joueur) {
	if (joueur->score <= 66) {
		setVictoire(joueur);
	} else {
		setDefaite(joueur);
	}
}

void mettreAJourVictoireDefaiteOrdi(struct Ordi *ordi) {
	if (ordi->score <= 66) {
		setVictoireOrdi(ordi);
	} else {
		setDefaiteOrdi(ordi);
	}
}

void mettreAJourVictoireDefaiteOrdiAmeliorer(struct OrdiAmeliorer *ordi) {
	if (ordi->score <= 66) {
		setVictoireOrdiAmeliorer(ordi);
	} else {
		setDefaiteOrdiAmeliorer(ordi);
	}
}

/*----------------------------------------------------------------------------------------------------------------------*/


//Ces fonctions sont les mêmes sauf que celles-ci sont pour les Ordis Améliorer étant donné que c'est une classe différente.

void initialiserPartieAmeliorer(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go, struct Plateau *plateau) {
	partie->plateau = *plateau; // Initialiser le plateau
	partie->gestionJoueur = *gj;
	partie->gestionOrdiAmeliorer = *go;

	for (int i = 0; i < 100; ++i) {
		effectuerMancheAmeliorer(&partie->manches[i], &partie->plateau, &partie->gestionJoueur, &partie->gestionOrdiAmeliorer);
		if (trouverPlusGrosScoreAmeliorer(partie, &partie->gestionJoueur, &partie->gestionOrdiAmeliorer) >= 66) {
			customPrintf("Fin de partie:\n");
			for(int i= 0; i<gj->nombreJoueurs;++i){
				mettreAJourVictoireDefaite(&partie->gestionJoueur.listeJoueurs[i]);
			}
			for(int i= 0; i<go->nombreOrdis;++i){
				mettreAJourVictoireDefaiteOrdiAmeliorer(&partie->gestionOrdiAmeliorer.listeOrdis[i]);
			}
			ecrireResult(partie, &partie->gestionJoueur, &partie->gestionOrdi,&partie->gestionOrdiAmeliorer);

			return;
		}
	}
}

int trouverPlusGrosScoreAmeliorer(struct Partie *p, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go) {
	int plusGrosScore = 0;

	for (int i = 0; i < gj->nombreJoueurs; ++i) {
		if (gj->listeJoueurs[i].score > plusGrosScore) {
			plusGrosScore = gj->listeJoueurs[i].score;
		}
	}

	for (int i = 0; i < go->nombreOrdis; ++i) {
		if (go->listeOrdis[i].score > plusGrosScore) {
			plusGrosScore = go->listeOrdis[i].score;
		}
	}



	return plusGrosScore;
}



void ecrireResult(struct Partie *partie, struct GestionJoueur *gj, struct GestionOrdi *go, struct GestionOrdiAmeliorer *gm) {
	// Ouvre le fichier resultats_formates.txt en mode append
	FILE *file = fopen("resultats_formates.txt", "a");
	if (file == NULL) {
		perror("Erreur lors de l'ouverture du fichier resultats_formates.txt");
		exit(EXIT_FAILURE);
	}

	// Écrire les résultats des joueurs dans le fichier avec le nombre de victoires et de défaites
	for (int i = 0; i < gj->nombreJoueurs; ++i) {
		fprintf(file, "%s : %d points, Victoires : %d, Défaites : %d\n",
				gj->listeJoueurs[i].nom,
				gj->listeJoueurs[i].score,
				gj->listeJoueurs[i].victoire,
				gj->listeJoueurs[i].defaite);
	}

	// Écrire les résultats des ordinateurs dans le fichier avec le nombre de victoires et de défaites
	for (int i = 0; i < go->nombreOrdis; ++i) {
		fprintf(file, "%s : %d points, Victoires : %d, Défaites : %d\n",
				go->listeOrdis[i].nom,
				go->listeOrdis[i].score,
				go->listeOrdis[i].victoire,
				go->listeOrdis[i].defaite);

	}
	// Écrire les résultats des ordinateurs dans le fichier avec le nombre de victoires et de défaites
	for (int i = 0; i < gm->nombreOrdis; ++i) {
		fprintf(file, "%s : %d points, Victoires : %d, Défaites : %d\n",
				gm->listeOrdis[i].nom,
				gm->listeOrdis[i].score,
				gm->listeOrdis[i].victoire,
				gm->listeOrdis[i].defaite);

	}


	// Fermer le fichier
	fclose(file);

	char awkCommandStats[] = "awk -F'[:,]' '{player_sum[$1] += $2; player_count[$1] += 1; victories[$1] += $4; defeats[$1] += $6;} \
                               END {printf \"Moyenne des scores :\\n\"; \
                                    for (player in player_sum) { \
                                        avg_score = player_sum[player] / player_count[player]; \
                                        printf \"%s : %.2f points, Victoires : %d, Défaites : %d\\n\", \
                                               player, avg_score, victories[player], defeats[player]; \
                                    }}' resultats_formates.txt > stat.txt 2> awk_error.log";

	// Ouvre un processus pour exécuter la commande awk
	FILE *awkProcessStats = popen(awkCommandStats, "w");

	if (awkProcessStats == NULL) {
		perror("Erreur lors de l'ouverture du processus awk (stats)");
		exit(EXIT_FAILURE);
	}

	// Ferme le processus awk (stats)
	int statusStats = pclose(awkProcessStats);

	if (statusStats == -1) {
		perror("Erreur lors de la fermeture du processus awk (stats)");
		exit(EXIT_FAILURE);
	} else if (statusStats != 0) {
		fprintf(stderr, "Le processus awk (stats) a terminé avec un code de sortie non nul\n");
		exit(EXIT_FAILURE);
	}
}

