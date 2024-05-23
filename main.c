#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "Grille.h"
#include "Serpent.h"
#include "liste_Section.h"
#include "Fonction_Jeu.h"



int main(int argc, char **  argv) {
	int joueur;
	int delai;	
	struct Grille * g;
	struct Serpent * serp;
	
	if (argc != 5) {
		fprintf(stderr, "Veuillez entrer le bon nombre d'argumets (4)\n");
		exit(1);
	}
	joueur = atoi(argv[4]);
	if(joueur!=1) {printf("partie du jeu pas encore developpée");}
	else {
	g = Grille_allouer(atoi(argv[1]), atoi(argv[2]));

	if ((g->n < 0) || (g->m<0)) {
		fprintf(stderr, "Un des arguments est négatif\n");
		exit(1);
	}

	serp = creer_serpent(g->n, g->m);
	delai = atoi(argv[3]);
	Jouer_Serpent(g, serp, delai);
	Grille_desallouer(&g);}
	printf("\n 		SNAKE\n");

	
	return EXIT_SUCCESS;
	
}

