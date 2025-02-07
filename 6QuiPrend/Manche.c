#include "Manche.h"
#include <stdio.h>
#include "Joueur.h"
#include "Ordi.h"
#include "GestionOrdi.h"
#include "GestionJoueur.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Paquet.h"
#include "Affichage.h"
#include "Plateau.h" // Assurez-vous que Plateau.h est inclus ici
#include <limits.h>

#include <string.h>


int effectuerManche(struct Manche *manche, struct Plateau *p, struct GestionJoueur *gj, struct GestionOrdi *go) {
	initPlateau(p);
	initialiserPaquet(&manche->paquet);
	melangerPaquet(&manche->paquet);
	distribuerJeux(gj, go,manche);
	initialiserListeCarteAJouer(manche);

	struct Carte nouvelleCarte[4] ;

	int plusGrosScore = INT_MIN;

	//On ajoute les 4 cartes du début au plateau

	for (int i = 0; i < 4; i++) {
		nouvelleCarte[i] = retirerCarte(&manche->paquet);
		ajouterCartePlateau(p, &nouvelleCarte[i], i);
	}

	int tour = 0;

	//On arrête les tours si personne n'a plus de cartes ou alors qu'un joueur à + de 66 de score.

	while(tour!=10 && plusGrosScore <66){
		//printf("Plus Gros Score : %d\n", plusGrosScore);
		//initialiserListeCarteAJouer(manche);
		if(tour == 0){
			// Utilisation de printf
			customPrintf("\n\n");


			// Utilisation de printf
			customPrintf("\nDébut de la Manche:\n\n");


			// Utilisation de printf
			customPrintf("\nDébut du tour %d:\n\n", tour + 1);



		}
		else{
			customPrintf("\nDébut du tour %d:\n\n", tour+1);
		}
		//if(plusGrosScore<66){


		//On demande à chaque Joueur quelle carte il veut jouer.

		AfficherPlateau(p);
		customPrintf("\n\n");
		struct Carte paquetManche[gj->nombreJoueurs+go->nombreOrdis];

		for(int i=0; i<gj->nombreJoueurs; ++i){
			int sortie = -1;
			int carteChoisie = -1;
			afficherMainJoueur(&gj->listeJoueurs[i]);
			customPrintf("\nChoisir une carte à jouer :\n\n");

			while(sortie == -1){
				//printf("%d\n", gj->listeJoueurs[i].nbCarte);
				fflush(stdout);
				scanf("%d", &carteChoisie);

				if(carteChoisie < 0 || carteChoisie >= gj->listeJoueurs[i].nbCarte){
					customPrintf("\nChoisir une carte à jouer entre 0 et %d :\n\n", gj->listeJoueurs[i].nbCarte - 1);
				}
				else{
					sortie = 0;
				}
			}


			paquetManche[i] = poserCarteJoueur(&gj->listeJoueurs[i], carteChoisie);
			insererCarte(manche,i,&paquetManche[i]);
		}

		//Les ordis choississent aléatoirement

		for (int i = 0; i < go->nombreOrdis; i++) {
			//afficherMainOrdi(&go->listeOrdis[i]);
			paquetManche[i + gj->nombreJoueurs] = poserCarteAleatoire(&go->listeOrdis[i]);
			insererCarte(manche, i + gj->nombreJoueurs, &paquetManche[i + gj->nombreJoueurs]);
		}

		//On trie la liste de Carte à jouer
		triListe(manche,gj,go);
		customPrintf("\n\n");
		afficherListeCarteAJouer(manche,gj,go);
		customPrintf("\n\n");
		AfficherPlateau(p);

		//On essaye de les mettre dans le Plateau

		for(int i = 0; i<gj->nombreJoueurs+go->nombreOrdis; i++){

			struct Carte c;
			c =ajouterCarteDansTab(p,manche->listeCarteAJouer[i]);


			//Si le numéro de la carte est non-égale à zéro cela signifie que la fonction ne peut placer la carte et qu'il faut demander afin d'enlever une colonne
			if (c.numero != 0) {
				customPrintf("nom: %s\n", (manche->listeCarteAJouer[i]->nom));
				affichage(manche->listeCarteAJouer[i]);
				customPrintf("\n\n");

				for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis; j++) {

					//Pour retrouver à qui appartient la carte après avoir était triée, on regarde le nom de la Carte
					if (strcmp(gj->listeJoueurs[j].nom, manche->listeCarteAJouer[i]->nom) == 0) {

						int scoreActuel = 0;
						int choixLigne = -1;
						while (choixLigne == -1) {
							customPrintf("Impossibilité de placer la carte:\nVeuillez choisir une ligne à enlever\n");
							fflush(stdout);
							scanf("%d", &choixLigne);
							if (choixLigne < 0 || choixLigne >= 4) {

								// Si la saisie n'est pas un entier ou est hors des limites, réinitialisez le choix
								choixLigne = -1;
								customPrintf("Veuillez choisir une ligne entre 0 et 3\n");
								// Vider le tampon d'entrée pour éviter des problèmes de saisie ultérieure
								while (getchar() != '\n');
							}
							else{
								scoreActuel = calculScore(p, &c, choixLigne);
								struct Joueur* joueur = chercherJoueur(gj, manche->listeCarteAJouer[i]->nom);
								//printf("score : %d\n", scoreActuel);
								setScoreJoueur(joueur, scoreActuel);

							}
						}

						//L'ordi joue aléatoirement


					}
					else if (strcmp(go->listeOrdis[j].nom, manche->listeCarteAJouer[i]->nom) == 0){
						int ligneChoisie = rand() % 4;
						int scoreActuel = calculScore(p, &c, ligneChoisie);
						setScoreOrdi(chercherOrdi(go, manche->listeCarteAJouer[i]->nom), scoreActuel);

					}
				}
			}

			//Dans ce cas alors on affecte le score à la bonne Personne
			else if(c.numero == 0 && c.teteDeBoeuf!=0){

				for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis; j++) {
					if (strcmp(gj->listeJoueurs[j].nom, manche->listeCarteAJouer[i]->nom) == 0) {
						struct Joueur* joueur = chercherJoueur(gj, manche->listeCarteAJouer[i]->nom);
						setScoreJoueur(joueur, c.teteDeBoeuf);
					}
					else if (strcmp(go->listeOrdis[j].nom, manche->listeCarteAJouer[i]->nom) == 0){
						setScoreOrdi(chercherOrdi(go, manche->listeCarteAJouer[i]->nom), c.teteDeBoeuf);
					}
				}
			}
		}
		AfficherPlateau(p);
		customPrintf("\n\n");
		for(int i = 0; i<gj->nombreJoueurs; ++i){
			customPrintf("nom : %s , score : %d\n" , gj->listeJoueurs[i].nom, gj->listeJoueurs[i].score);

		}
		for(int i = 0; i<go->nombreOrdis; ++i){
			customPrintf("nom : %s , score : %d\n" , go->listeOrdis[i].nom, go->listeOrdis[i].score);

		}


		++tour;
		// Initialiser à la valeur minimale possible d'un entier

		// Parcourir les joueurs humains
		for (int i = 0; i < gj->nombreJoueurs; ++i) {
			if (gj->listeJoueurs[i].score > plusGrosScore) {
				plusGrosScore = gj->listeJoueurs[i].score;
			}
		}

		// Parcourir les ordinateurs
		for (int i = 0; i < go->nombreOrdis; ++i) {
			if (go->listeOrdis[i].score > plusGrosScore) {
				plusGrosScore = go->listeOrdis[i].score;
			}
			//}

		}
	}


	return plusGrosScore;

}



void distribuerJeux(struct GestionJoueur *listjoueur, struct GestionOrdi *listordinateurs, struct Manche *manche) {
	// Initialisation de la structure Paquet pour gérer le paquet de cartes

	for (int i = 0; i < listjoueur->nombreJoueurs; ++i) {
		struct Carte *listcarte = distribuerCartes(&manche->paquet);

		struct Joueur *joueur = getJoueurAtIndex(listjoueur, i);
		ajouterCarteMainJoueur(joueur, listcarte);

		// Copiez le nom du joueur dans le champ nom de chaque carte
		for (int j = 0; j < joueur->nbCarte; j++) {
			strcpy(listcarte[j].nom, joueur->nom);
		}
	}

	for (int i = 0; i < listordinateurs->nombreOrdis; ++i) {
		struct Carte *listcarte = distribuerCartes(&manche->paquet);

		struct Ordi *ordi = getOrdiAtIndex(listordinateurs, i);
		ajouterCarteMainOrdi(ordi, listcarte);

		// Copiez le nom de l'ordinateur dans le champ nom de chaque carte
		for (int j = 0; j < ordi->nbCarte; j++) {
			strcpy(listcarte[j].nom, ordi->nom);
		}
	}
}



void initialiserListeCarteAJouer(struct Manche *manche) {
	for (int i = 0; i < sizeof(manche->listeCarteAJouer) / sizeof(manche->listeCarteAJouer[0]); ++i) {
		// Allouez dynamiquement de la mémoire pour chaque carte
		manche->listeCarteAJouer[i] = (struct Carte*)malloc(sizeof(struct Carte));
		// Initialisez chaque élément à une valeur par défaut
		manche->listeCarteAJouer[i]->numero = 0;
		manche->listeCarteAJouer[i]->teteDeBoeuf = 0;
	}
}

struct Carte recupererElement(struct Manche *manche, int i) {

	return *manche->listeCarteAJouer[i];

}
void insererCarte(struct Manche *manche, int i, struct Carte *nouvelleCarte) {
	// Allouez dynamiquement de la mémoire pour la nouvelle carte
	manche->listeCarteAJouer[i] = (struct Carte*)malloc(sizeof(struct Carte));

	// Copiez les valeurs de la nouvelle carte dans la liste
	manche->listeCarteAJouer[i]->numero = nouvelleCarte->numero;
	manche->listeCarteAJouer[i]->teteDeBoeuf = nouvelleCarte->teteDeBoeuf;
	strcpy(manche->listeCarteAJouer[i]->nom, nouvelleCarte->nom);

	// Notez que cela suppose que votre structure Carte a un champ nom. Si ce n'est pas le cas, ajustez en conséquence.
}



void triListe(struct Manche *m, struct GestionJoueur *gj, struct GestionOrdi *go) {
	struct Carte *temp;

	for (int i = 0; i < gj->nombreJoueurs+go->nombreOrdis - 1; i++) {
		for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis - i - 1; j++) {
			if (m->listeCarteAJouer[j]->numero > m->listeCarteAJouer[j + 1]->numero) {
				// Échanger les cartes pour les trier en ordre croissant
				temp = m->listeCarteAJouer[j];
				m->listeCarteAJouer[j] = m->listeCarteAJouer[j + 1];
				m->listeCarteAJouer[j + 1] = temp;
			}
		}
	}
}


void afficherListeCarteAJouer(struct Manche *manche,struct GestionJoueur *gj, struct GestionOrdi *go ) {
	customPrintf("Liste des cartes à jouer :\n");

	for (int i = 0; i < gj->nombreJoueurs+go->nombreOrdis; i++) {

		affichage(manche->listeCarteAJouer[i]);

	}
}








/*----------------------------------------------------------------------------------------------------------------------*/




int effectuerMancheAmeliorer(struct Manche *manche, struct Plateau *p, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go) {
	initPlateau(p);
	initialiserPaquet(&manche->paquet);
	melangerPaquet(&manche->paquet);
	distribuerJeuxAmeliorer(gj, go,manche);
	initialiserListeCarteAJouer(manche);
	//printf("\nIl y a %d ordis\n", go->nombreOrdis);
	//printf("Il y a %d joueurs\n\n", gj->nombreJoueurs);
	struct Carte nouvelleCarte[4] ;

	int plusGrosScore = INT_MIN;



	for (int i = 0; i < 4; i++) {
		nouvelleCarte[i] = retirerCarte(&manche->paquet);
		ajouterCartePlateau(p, &nouvelleCarte[i], i);
	}

	int tour = 0;

	while(tour!=10 && plusGrosScore <66){
		//initialiserListeCarteAJouer(manche);
		if(tour == 0){
					// Utilisation de printf
					customPrintf("\n\n");


					// Utilisation de printf
					customPrintf("\nDébut de la Manche:\n\n");


					// Utilisation de printf
					customPrintf("\nDébut du tour %d:\n\n", tour + 1);



				}
				else{
					customPrintf("\nDébut du tour %d:\n\n", tour+1);
				}
		//if(plusGrosScore<66){




		AfficherPlateau(p);

		struct Carte paquetManche[gj->nombreJoueurs+go->nombreOrdis];

		for(int i=0; i<gj->nombreJoueurs; ++i){
			int sortie = -1;
			int carteChoisie = -1;
			afficherMainJoueur(&gj->listeJoueurs[i]);
			customPrintf("\nChoisir une carte à jouer :\n\n");

			while(sortie == -1){
				//printf("%d\n", gj->listeJoueurs[i].nbCarte);
				fflush(stdout);
				scanf("%d", &carteChoisie);

				if(carteChoisie < 0 || carteChoisie >= gj->listeJoueurs[i].nbCarte){
					customPrintf("\nChoisir une carte à jouer entre 0 et %d :\n\n", gj->listeJoueurs[i].nbCarte - 1);
				}
				else{
					sortie = 0;
				}
			}


			paquetManche[i] = poserCarteJoueur(&gj->listeJoueurs[i], carteChoisie);
			insererCarte(manche,i,&paquetManche[i]);
		}

		for (int i = 0; i < go->nombreOrdis; i++) {
			// Obtenir la carte à poser aléatoirement pour chaque ordinateur
			afficherMainOrdiAmeliorer(&go->listeOrdis[i]);
			struct Carte carteJouee = poserCarteAleatoireAmeliorer(&go->listeOrdis[i], p);

			// Afficher la carte jouée par l'ordinateur
			customPrintf("Carte de l'ordinateur %s : %d;%d\n", go->listeOrdis[i].nom, carteJouee.numero, carteJouee.teteDeBoeuf);

			// Insérer la carte dans la manche
			insererCarte(manche, i + gj->nombreJoueurs, &carteJouee/*&paquetManche[i+ gj->nombreJoueurs]*/);

			// Ajouter la carte au paquet de la manche
			paquetManche[i + gj->nombreJoueurs] = carteJouee;
		}



		triListeAmeliorer(manche,gj,go);
		customPrintf("\n\n");
		afficherListeCarteAJouerAmeliorer(manche,gj,go);
		customPrintf("\n\n");
		AfficherPlateau(p);

		for(int i = 0; i<gj->nombreJoueurs+go->nombreOrdis; i++){

			struct Carte c;
			c =ajouterCarteDansTab(p,manche->listeCarteAJouer[i]);
			//printf("noma %s\n", manche->listeCarteAJouer[i]->nom);
			if (c.numero != 0) {
				customPrintf("nom: %s\n", (manche->listeCarteAJouer[i]->nom));
				//char* proprietaire = manche->listeCarteAJouer[i].nom;
				affichage(manche->listeCarteAJouer[i]);
				customPrintf("\n");

				for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis; j++) {
					if (strcmp(gj->listeJoueurs[j].nom, manche->listeCarteAJouer[i]->nom) == 0) {

						//int choix = 1;
						int scoreActuel = 0;
						int choixLigne = -1;
						while (choixLigne == -1) {
							customPrintf("Impossibilité de placer la carte:\nVeuillez choisir une ligne à enlever\n");
							fflush(stdout);
							scanf("%d", &choixLigne);
							if (choixLigne < 0 || choixLigne >= 4) {

								// Si la saisie n'est pas un entier ou est hors des limites, réinitialisez le choix
								choixLigne = -1;
								customPrintf("Veuillez choisir une ligne entre 0 et 3\n");
								// Vider le tampon d'entrée pour éviter des problèmes de saisie ultérieure
								while (getchar() != '\n');
							}
							else{
								scoreActuel = calculScore(p, &c, choixLigne);
								struct Joueur* joueur = chercherJoueur(gj, manche->listeCarteAJouer[i]->nom);
								//printf("score : %d\n", scoreActuel);
								setScoreJoueur(joueur, scoreActuel);

							}
						}

					}
					else if (strcmp(go->listeOrdis[j].nom, manche->listeCarteAJouer[i]->nom) == 0){

						int ligneChoisie = rand() % 4;
						customPrintf("choixligne bot : %d\n", ligneChoisie);
						//printf("choix de l'ordi %d + nom %s\n", ligneChoisie, manche->listeCarteAJouer[i].nom);
						int scoreActuel = calculScore(p, &c, ligneChoisie);
						//printf("score : %d\n", scoreActuel);
						setScoreOrdiAmeliorer(chercherOrdiAmeliorer(go, manche->listeCarteAJouer[i]->nom), scoreActuel);


					}
				}
			}
			else if(c.numero == 0 && c.teteDeBoeuf!=0){
				customPrintf("OrdiAmeliorer score %d\n", c.teteDeBoeuf);
				for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis; j++) {
					if (strcmp(gj->listeJoueurs[j].nom, manche->listeCarteAJouer[i]->nom) == 0) {
						struct Joueur* joueur = chercherJoueur(gj, manche->listeCarteAJouer[i]->nom);
						setScoreJoueur(joueur, c.teteDeBoeuf);
					}
					else if (strcmp(go->listeOrdis[j].nom, manche->listeCarteAJouer[i]->nom) == 0){

						struct OrdiAmeliorer* ordi = chercherOrdiAmeliorer(go, manche->listeCarteAJouer[i]->nom);

						setScoreOrdiAmeliorer(ordi, c.teteDeBoeuf);
					}
				}
			}



		}
		for(int i = 0; i<gj->nombreJoueurs; ++i){
			customPrintf("nom : %s , score : %d\n" , gj->listeJoueurs[i].nom, gj->listeJoueurs[i].score);

		}
		for(int i = 0; i<go->nombreOrdis; ++i){
			customPrintf("nom : %s , score : %d\n" , go->listeOrdis[i].nom, go->listeOrdis[i].score);

		}
		customPrintf("\n");
		AfficherPlateau(p);
		++tour;
		// Initialiser à la valeur minimale possible d'un entier

		// Parcourir les joueurs humains
		for (int i = 0; i < gj->nombreJoueurs; ++i) {
			if (gj->listeJoueurs[i].score > plusGrosScore) {
				plusGrosScore = gj->listeJoueurs[i].score;
			}
		}

		// Parcourir les ordinateurs
		for (int i = 0; i < go->nombreOrdis; ++i) {
			if (go->listeOrdis[i].score > plusGrosScore) {
				plusGrosScore = go->listeOrdis[i].score;
			}
			//}

		}
	}


	return plusGrosScore;

}






void distribuerJeuxAmeliorer(struct GestionJoueur *listjoueur, struct GestionOrdiAmeliorer *listordinateurs, struct Manche *manche) {
	// Initialisation de la structure Paquet pour gérer le paquet de cartes

	for (int i = 0; i < listjoueur->nombreJoueurs; ++i) {
		struct Carte *listcarte = distribuerCartes(&manche->paquet);

		struct Joueur *joueur = getJoueurAtIndex(listjoueur, i);
		ajouterCarteMainJoueur(joueur, listcarte);

		// Copiez le nom du joueur dans le champ nom de chaque carte
		for (int j = 0; j < joueur->nbCarte; j++) {
			strcpy(listcarte[j].nom, joueur->nom);
		}
	}

	for (int i = 0; i < listordinateurs->nombreOrdis; ++i) {
		struct Carte *listcarte = distribuerCartes(&manche->paquet);

		struct OrdiAmeliorer *ordi = getOrdiAmeliorerAtIndex(listordinateurs, i);
		ajouterCarteMainOrdiAmeliorer(ordi, listcarte);

		// Copiez le nom de l'ordinateur dans le champ nom de chaque carte
		for (int j = 0; j < ordi->nbCarte; j++) {
			strcpy(listcarte[j].nom, ordi->nom);
		}
	}
}


void triListeAmeliorer(struct Manche *m, struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go) {
	struct Carte *temp;

	for (int i = 0; i < gj->nombreJoueurs+go->nombreOrdis - 1; i++) {
		for (int j = 0; j < gj->nombreJoueurs+go->nombreOrdis - i - 1; j++) {
			if (m->listeCarteAJouer[j]->numero > m->listeCarteAJouer[j + 1]->numero) {
				// Échanger les cartes pour les trier en ordre croissant
				temp = m->listeCarteAJouer[j];
				m->listeCarteAJouer[j] = m->listeCarteAJouer[j + 1];
				m->listeCarteAJouer[j + 1] = temp;
			}
		}
	}
}


void afficherListeCarteAJouerAmeliorer(struct Manche *manche,struct GestionJoueur *gj, struct GestionOrdiAmeliorer *go ) {
	customPrintf("Liste des cartes à jouer :\n");

	for (int i = 0; i < gj->nombreJoueurs+go->nombreOrdis; i++) {

		affichage(manche->listeCarteAJouer[i]);

	}
}
