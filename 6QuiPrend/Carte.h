#ifndef CARTE_H
#define CARTE_H
#define MAX_ETOILES_PAR_LIGNE 4
struct Carte {
    int numero;       // Numéro de la carte (1 à 104)
    int teteDeBoeuf;  // Nombre de points de pénalité (Têtes de Bœuf)
    char nom[20];
};

int getNumero(const struct Carte *carte);
int getTeteDeBoeuf(const struct Carte *carte);
void setNumero(struct Carte *carte, int nouveauNumero);
void setTeteDeBoeuf(struct Carte *carte, int nouvellesTetes);
void affichage(const struct Carte *carte);
void setNom(struct Carte *c, char *nom);

#endif  // CARTE_H

