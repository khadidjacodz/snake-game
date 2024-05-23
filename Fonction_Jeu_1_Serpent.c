#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "Fonction_Jeu.h"
#include "Grille.h"
#include "Serpent.h"
#include "liste_Section.h"
#include "liste_Mouvement.h"

void Jouer_Serpent(struct Grille *g, struct Serpent *serp, int delai) {
    int ch;
    int nbf = 0;
    enum Direction sens = NEUTRE;  // Direction initiale du serpent
    int couleur, longueur;

    // Déclaration des variables pour le temps
    time_t start_time, end_time;
    
    // Initialisation de ncurses et du clavier
    initscr();               // Démarre le mode ncurses
    raw();                   // Désactive le buffering de ligne pour un contrôle plus précis
    keypad(stdscr, TRUE);    // Active la capture des touches spéciales (flèches)
    noecho();                // N'affiche pas les touches pressées
    halfdelay(delai);        // Définit un délai d'attente pour getch() en dixièmes de seconde

    // Initialisation de la grille
    Grille_tirage_fruit(g);                   // Place un fruit aléatoire dans la grille
    Grille_vider(g);                          // Vide la grille
    Grille_remplir_rouge(g, g->fruitx, g->fruity);  // Remplit la grille avec un fruit rouge
    Grille_remplir_serp(g, serp, sens);       // Place le serpent dans la grille
    Grille_redessiner(g);                     // Redessine la grille

   // printf("\nVous avez pour l'instant, mangé: %d fruits\n", nbf);     // Affiche le score initial
    refresh();                                // Met à jour l'affichage de ncurses

    // Enregistrement du temps de début
    time(&start_time);

    // Boucle principale du jeu
    while ((ch = getch()) != '-') {  // Continue jusqu'à ce que '-' soit pressé
        // Détection des touches fléchées pour changer la direction
        switch (ch) {
            case KEY_UP:
                if (sens != BAS) {
                    ajout_fin_liste_mouvement(serp->mouvement, creer_case(serp->tetex, serp->tetey, HAUT));
                    sens = HAUT;
                }
                break;
            case KEY_DOWN:
                if (sens != HAUT) {
                    ajout_fin_liste_mouvement(serp->mouvement, creer_case(serp->tetex, serp->tetey, BAS));
                    sens = BAS;
                }
                break;
            case KEY_LEFT:
                if (sens != DROITE) {
                    ajout_fin_liste_mouvement(serp->mouvement, creer_case(serp->tetex, serp->tetey, GAUCHE));
                    sens = GAUCHE;
                }
                break;
            case KEY_RIGHT:
                if (sens != GAUCHE) {
                    ajout_fin_liste_mouvement(serp->mouvement, creer_case(serp->tetex, serp->tetey, DROITE));
                    sens = DROITE;
                }
                break;
        }

        // Mise à jour de la position du serpent selon la direction
        switch (sens) {
            case HAUT:
                serp->tetey--;
                break;
            case BAS:
                serp->tetey++;
                break;
            case DROITE:
                serp->tetex++;
                break;
            case GAUCHE:
                serp->tetex--;
                break;
        }

        // Vérification des collisions avec les bords de la grille
        if (serp->tetex < 0 || serp->tetex >= g->m || serp->tetey < 0 || serp->tetey >= g->n) {
            break;  // Fin du jeu si collision
        }

        // Vérification des collisions avec le fruit
        if (serp->tetex == g->fruitx && serp->tetey == g->fruity) {
            longueur = (rand() % 2) + 1;    // Détermine la longueur de la nouvelle section
            couleur = (rand() % 6) + 41;    // Détermine la couleur de la nouvelle section
            ajout_fin_liste(serp->chaine, creer_section(longueur, couleur));  // Ajoute une nouvelle section au serpent
            Grille_tirage_fruit(g);  // Place un nouveau fruit
            nbf++;  // Incrémente le score
        }

        // Mise à jour de la grille
        Grille_vider(g);                          // Vide la grille
        Grille_remplir_rouge(g, g->fruitx, g->fruity);  // Remplit la grille avec un fruit rouge
        Grille_remplir_serp(g, serp, sens);       // Place le serpent dans la grille
        Grille_redessiner(g);                     // Redessine la grille

       // printf("\nVous avez pour l'instant, mangé: %d fruits\n", nbf);     // Affiche le score actuel
        refresh();                                // Met à jour l'affichage de ncurses
    }

    // Enregistrement du temps de fin
    time(&end_time);

    // Calcul du temps écoulé
    double elapsed_time = difftime(end_time, start_time);

    // Terminer la session ncurses
    endwin();  // Ferme le mode ncurses proprement

    printf("		Game over\n");  // Affiche un message de fin de jeu
    printf("\nNombre de fruit mangés: %d\n", nbf);  // Affiche le score final
    printf("Vous avez joué pendant: %.2f secondes\n", elapsed_time);  // Affiche le temps écoulé
}



