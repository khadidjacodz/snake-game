#ifndef SERPENT_H
#define SERPENT_H

#include "liste_Section.h"
#include "liste_Mouvement.h"


struct Serpent {
	
	int tetex;
	int tetey;
	struct Liste * chaine;	
	struct Liste_Mouvement * mouvement;
	
};

/* Fonction permertant d'alouer un espace pour le serpent et qui prend en entrée les dimensions de la grille */
struct Serpent * creer_serpent(int n, int m);

/* void update_liste(struct Serpent * serp); */

#endif

