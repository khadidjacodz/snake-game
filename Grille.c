#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Grille.h"
#include "liste_Mouvement.h"

struct Grille * Grille_allouer(int n, int m){
        int i, j;
        struct Grille *g = malloc(sizeof(struct Grille));
        g->n = n;
        g->m = m;
        g->tab = malloc(n * sizeof(char **));// Allocation pour un tableau de pointeurs vers char*
	for (i=0; i<n; i++) {
		g->tab[i] = malloc(m * sizeof(char*));		
		for (j=0; j<m; j++) {
			g->tab[i][j] = malloc(8 * sizeof(char));// Allocation pour une chaîne de caractères
		}
	}	
	
	g->fruitx=0; //coordonnés du fruit init a 0
	g->fruity=0;
	
	return g;	
	}


void Grille_vider(struct Grille * g) {
	int i, j;
	for (i=0; i<g->n; i++) {
		for (j=0; j<g->m; j++) {
			strcpy(g->tab[i][j], "\033[40m  ");	
		}
	}
} //rempli les cases de la grille de deux espaces de couleur noir

void Grille_tirage_fruit(struct Grille *g){
       
       srand(time(NULL));
       
        g->fruitx = rand() % g->m;
        g->fruity = rand() % g->n;
        
}



void Grille_remplir_rouge(struct Grille * g, int x, int y) {
	strcpy(g->tab[y][x], "\033[41m  "); //rouge	
}


void Grille_desallouer(struct Grille ** g) {
	int i, j;	
	if (*g == NULL)
       		return; //si elle n'a pas ete allouée 
	
	for (i=0; i<(*g)->n; i++) {
		for (j=0; j<(*g)->m; j++) {
			free((*g)->tab[i][j]);
			(*g)->tab[i][j] = NULL; //pour s'assurer qu'elle ne pointe plus sur rien
		}
		free((*g)->tab[i]);
		(*g)->tab[i] = NULL;
	}
	free(*g);
	*g = NULL;
}

void Grille_redessiner(struct Grille *g){

	int i,j;

	printf("\033[2J"); //effacer le terminal
	printf("\033[H");//positionner le curseur au début de la ligne
	// Ligne supérieure du liseret
	for (j=0; j<g->m+2; j++) {
		printf("\033[103m  "); // Chaque espace de liseret représenté par 2 espace jaune
       	}
	
	printf("\033[1E"); //nouvelle ligne
	// Contenu de la grille avec liseret de chaque côté
	for (i=0; i<g->n; i++) {
		printf("\033[106m  "); //liseret gauche
		for (j=0; j<g->m; j++) {
                	printf("%s\033[0m", g->tab[i][j]);
		}
		printf("\033[106m  ");//liseret droit
		printf("\033[1E"); 
	}
	
	for (j=0; j<g->m+2; j++) {
		printf("\033[103m  ");//liseret du bas
	}
	
	printf("\033[0m\n");

}

void Grille_remplir_couleur(struct Grille * g, int x, int y, int couleur) {
	
	if (couleur>40 && couleur<48 && x >= 0 && x<g->m && y >= 0 &&y<g->n){
		snprintf(g->tab[y][x], 8, "\033[%dm  ", couleur);
	}
}


void Grille_remplir_serp(struct Grille * g, struct Serpent * serp, enum Direction sens) {
        
        
        int i, x=serp->tetex, y=serp->tetey;      //coordonée de la tete du serpent   
       
       struct Section * s = serp->chaine->premier;
       struct Case * c = serp->mouvement->premier;
       
        if (g == NULL || serp == NULL || est_vide(serp->chaine))
                return; //n'a pas été allouué 
	
        while (s != NULL) {
		for (i = 0; i < s->taille; i++) {	//parcours la taille de la section
	        	
	        	if (c!=NULL && x==c->cordx && y==c->cordy) {
	        		sens = c->sens;
	        		c = c->suivant;
	        	}
	        	
			Grille_remplir_couleur(g, x, y, s->couleur);       
	        	
			switch (sens) {
                              
				case HAUT:
					y++;
					break;
                                
				case BAS:
					y--;
					break;
				
				case GAUCHE:
					x++;
					break;
				
				case DROITE:
					x--;
					break;
			}
		
		
		}
		
		s = s->suivant;
                        
	}
	
}

