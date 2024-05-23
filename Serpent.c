#include <stdlib.h>
#include <stdio.h>
#include "Serpent.h"

struct Serpent * creer_serpent(int n, int m) {

	struct Serpent * serp = malloc(sizeof(struct Serpent)); 
    // Initialisation de la position du serpent au centre de la grille
    // Cordx et cordy représentent les coordonnées x et y du serpent sur la grille
	serp->tetex = (n/2);
	serp->tetey = (m/2);
    // Initialisation de la liste chaînée 'chaine' qui représente le corps du serpent
	serp->chaine = creer_liste();
	// Ajoute une section initiale au début de la liste de chaînes du serpent
	ajout_debut_liste(serp->chaine, creer_section(1, 41));
	// Initialisation de la liste de mouvements du serpent, qui gérera les directions de mouvement
	serp->mouvement = creer_liste_mouvement();
    
	return serp;
}

