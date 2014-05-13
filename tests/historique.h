#ifndef __HISTORIQUE_H__
#define __HISTORIQUE_H__

#include "gestionPions.h"

typedef struct coup_s{
    Mvt mvt;
    int tigre;
    int chevre_mange;
    int placement_chevre;
    int phase;
    int joueur;
    struct coup_s* pred;
    struct coup_s* next;
}Coup;

typedef struct historique_s{
    Coup *first;
    int nbCoups;
    int premierAffiche;
}Historique;

typedef void (*fonctionCoup)(Coup *c, int ligne);

/*
 E : aucune
 S : un historque
 Role : Initialise un historique avec les valeurs de départ
 */
void historique_init (Historique* h);

/*
 E : un mouvement trois booleens un entier décrivant la phase actuelle, un entier décrivant un jouer
 S : un pointeur vers un coup
 Role : cree un coup aillant les caractéristiques passées en parametres
 */
Coup *historique_init_coup (Mvt m, int tigre, int chevre_mange, int placement_chevre, int phase, int joueur);

/*
 E : un pointeur vers un coup
 S : aucune
 Role : libere la mémoire occupée par le coup
 */
void historique_free_coup (Coup* c);

/*
 E : Un pointeur vers un coups
 S : aucune
 Role : Libère la mémoire de tous les coups à partir du coup passé en paramètre inclus. 
 */
void historique_detruire_hist (Coup* first);

/*
 E : un pointeur vers un historique, un pointeur vers un coup
 S : aucune
 Role : ajoute un coup à la fin de l'historique
 */
void historique_ajouter_coup (Historique* h, Coup* c);

/*
 E : un pointeur vers un historique
 S : aucune
 Role : Supprime le dernier coup de l'historique
 */
int historique_suppr_dernier_coup (Historique* h);

/*
 E : un historique
 S : un pointeur vers un coup
 Role : renvois un pointeur vers le dernier coup de l'historique
 */
Coup *historique_dernier_coup (Historique h);

/*
 E : un historique, une fonction
 S : aucune
 Role : Applique la fonction à tous les coups de l'historique. (Sert à l'affichage)
 */
void historique_map (Historique h, fonctionCoup f);

/*
 E : un pointeur vers un historique
 S : aucune
 Role : Annule le dernier coup de l'historique (ramène le jeu à l'état ou il était avant ce coup)
 */
void historique_annuler_coup (Historique* h);

#endif
