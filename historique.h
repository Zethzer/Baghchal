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

void historique_init (Historique* h);

Coup *historique_init_coup (Mvt m, int tigre, int chevre_mange, int placement_chevre, int phase, int joueur);

void historique_free_coup (Coup* c);

void historique_detruire_hist (Coup* first);

void historique_ajouter_coup (Historique* h, Coup* c);

int historique_suppr_dernier_coup (Historique* h);

Coup *historique_dernier_coup (Historique h);

void historique_map (Historique h, fonctionCoup f);

void historique_annuler_coup (Historique* h);

#endif
