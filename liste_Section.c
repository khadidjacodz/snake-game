#include <stdlib.h>
#include <stdio.h>
#include "liste_Section.h"

// Crée une nouvelle section avec une taille et une couleur spécifiées
struct Section * creer_section(int taille, int couleur) {
    // Allocation de mémoire pour une nouvelle section
    struct Section * s = malloc(sizeof(struct Section));
    // Initialisation des propriétés de la section
    s->taille = taille;
    s->couleur = couleur;
    s->suivant = NULL;  // Aucune autre section suivante lors de la création
    return s;
}

// Désalloue une section et met le pointeur à NULL
void desalouer_section(struct Section ** s) {
    if (*s != NULL) {  // Assurez-vous que la section n'est pas déjà NULL
        free(*s);      // Libération de la mémoire allouée à la section
        *s = NULL;     // Réinitialisation du pointeur à NULL après libération
    }
}

// Crée une nouvelle liste vide
struct Liste * creer_liste() {
    struct Liste * l = malloc(sizeof(struct Liste));
    l->premier = NULL;  // Aucune section au début
    l->dernier = NULL;  // Aucune section à la fin
    l->longueur = 0;    // Longueur initiale de la liste est zéro
    return l;
}

// Vérifie si la liste est vide
int est_vide(struct Liste * l) {
    return (l->longueur == 0);  // Retourne vrai (1) si la liste est vide
}

// Ajoute une section au début de la liste
void ajout_debut_liste(struct Liste * l, struct Section * s) {
    if (est_vide(l)) {  // Si la liste est vide, cette nouvelle section est aussi la dernière
        l->dernier = s;
    }
    s->suivant = l->premier;  // La nouvelle section pointe vers l'ancienne première section
    l->premier = s;           // La nouvelle section devient la première de la liste
    l->longueur++;            // Incrémentation de la longueur de la liste
}

// Ajoute une section à la fin de la liste
void ajout_fin_liste(struct Liste * l, struct Section * s) {
    s->suivant = NULL;  // La nouvelle section est la dernière, donc pas de suivant
    if (est_vide(l)) {
        l->premier = s;  // Si la liste est vide, cette nouvelle section est aussi la première
    } else {
        l->dernier->suivant = s;  // L'ancienne dernière section pointe vers la nouvelle section
    }
    l->dernier = s;  // Mise à jour du dernier pointeur vers la nouvelle section
    l->longueur++;  // Incrémentation de la longueur de la liste
}

// Extrait la première section de la liste et la retourne
struct Section * extraire_section(struct Liste * l) {
    struct Section * s = l->premier;  // Sauvegarde de la première section
    if (s != NULL) {
        l->premier = s->suivant;  // Mise à jour du premier pointeur
        l->longueur--;            // Décrémentation de la longueur de la liste
        if (est_vide(l)) {
            l->dernier = NULL;    // Si la liste est maintenant vide, pas de dernier élément
        }
        s->suivant = NULL;        // La section extraite n'a plus de suivant
    }
    return s;
}

// Désalloue toute la liste et ses sections
void desalouer_liste(struct Liste ** l) {
    if (*l != NULL) {
        struct Section * s;
        // Libération de toutes les sections une par une
        while(!est_vide(*l)) {
            s = extraire_section(*l);
            desalouer_section(&s);  // Libération de chaque section extraite
        }
        // Libération de la structure de liste elle-même
        free(*l);
        *l = NULL;  // Réinitialisation du pointeur de liste à NULL
    }
}

