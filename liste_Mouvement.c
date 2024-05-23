#include <stdlib.h>
#include <stdio.h>
#include "liste_Mouvement.h"

// Crée une nouvelle case avec les coordonnées x et y et la direction spécifiée
struct Case * creer_case(int cordx, int cordy, enum Direction sens) {
    // Allocation de mémoire pour une nouvelle case
    struct Case * c = malloc(sizeof(struct Case));
    // Initialisation des propriétés de la case
    c->cordx = cordx;
    c->cordy = cordy;
    c->sens = sens;
    c->suivant = NULL;  // Aucune autre case suivante lors de la création
    return c;
}

// Désalloue une case et met le pointeur à NULL
void desalouer_case(struct Case ** c) {
    if (*c != NULL) {  // Assurez-vous que la case n'est pas déjà NULL
        free(*c);      // Libération de la mémoire allouée à la case
        *c = NULL;     // Réinitialisation du pointeur à NULL après libération
    }
}

// Crée une nouvelle liste de mouvements vide
struct Liste_Mouvement * creer_liste_mouvement() {
    struct Liste_Mouvement * lm = malloc(sizeof(struct Liste_Mouvement));
    lm->premier = NULL;  // Aucune case au début
    lm->dernier = NULL;  // Aucune case à la fin
    lm->longueur = 0;    // Longueur initiale de la liste est zéro
    return lm;
}

// Vérifie si la liste de mouvements est vide
int est_vide_lm(struct Liste_Mouvement * lm) {
    return (lm->longueur == 0);  // Retourne vrai (1) si la liste est vide
}

// Ajoute une case au début de la liste de mouvements
void ajout_debut_liste_mouvement(struct Liste_Mouvement * lm, struct Case * c) {
    if (est_vide_lm(lm))  // Si la liste est vide, cette nouvelle case est aussi la dernière
        lm->dernier = c;
    
    c->suivant = lm->premier;  // La nouvelle case pointe vers l'ancienne première case
    lm->premier = c;           // La nouvelle case devient la première de la liste
    lm->longueur++;            // Incrémentation de la longueur de la liste
}

// Ajoute une case à la fin de la liste de mouvements
void ajout_fin_liste_mouvement(struct Liste_Mouvement * lm, struct Case * c) {
    c->suivant = NULL;  // La nouvelle case est la dernière, donc pas de suivant
    
    if (est_vide_lm(lm)) {
        lm->premier = c;  // Si la liste est vide, cette nouvelle case est aussi la première
    } else {
        lm->dernier->suivant = c;  // L'ancienne dernière case pointe vers la nouvelle case
    }
    
    lm->dernier = c;  // Mise à jour du dernier pointeur vers la nouvelle case
    lm->longueur++;   // Incrémentation de la longueur de la liste
}

// Extrait la première case de la liste de mouvements et la retourne
struct Case * extraire_case(struct Liste_Mouvement * lm) {
    struct Case * c = lm->premier;  // Sauvegarde de la première case
    
    if (c != NULL) {
        lm->premier = c->suivant;  // Mise à jour du premier pointeur
        lm->longueur--;            // Décrémentation de la longueur de la liste
        if (est_vide_lm(lm)) {
            lm->dernier = NULL;    // Si la liste est maintenant vide, pas de dernier élément
        }
        c->suivant = NULL;         // La case extraite n'a plus de suivant
    }
    
    return c;
}

// Désalloue toute la liste de mouvements et ses cases
void desalouer_liste_mouvement(struct Liste_Mouvement ** lm) {
    if (*lm != NULL) {
        struct Case * c;
        
        // Libération de toutes les cases une par une
        while(!est_vide_lm(*lm)) {
            c = extraire_case(*lm);
            desalouer_case(&c);  // Libération de chaque case extraite
        }
        
        // Libération de la structure de liste elle-même
        free(*lm);
        *lm = NULL;  // Réinitialisation du pointeur de liste à NULL
    }
}

