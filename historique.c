#include <stdio.h>
#include <stdlib.h>
#include "historique.h"
#include "plateau.h"

extern Plateau plat;

void historique_init (Historique h){
    h.first = NULL;
}

Coup *historique_coup_init (Mvt m){
    Coup *c = malloc(sizeof(Coup));
    c->next = NULL;
    c->mvt = m;
    return c;
}

void historique_free_coup (Coup* c){
    free(c);
}

void historique_detruire_hist (Coup* first){
    if (first->next)
        historique_detruire_hist(first->next);
    historique_free_coup (first);
}

void historique_ajouter_coup (Historique h, Coup* c){
    Coup* current = h->first;
    Coup* pred = NULL;
    while (current){
        current = current->next;
    }
    if (pred)
        pred->next = c;
    else
        h->first = c;
}

int historique_suppr_dernier_coup (Historique h){
    Coup* current = h->first;
    Coup* pred = NULL;
    if (!current)
        return 1;
    while (current->next){
        current = current->next;
    }
    if (pred)
        pred->next = NULL;
    else
        h->first = NULL;
    historique_free_coup(current);
    return 0;
}

void historique_map (Historique h, fonctionCoup f){
    Coup* current = h->first;
    while (current){
        f(current);
        current = current->next;
    }
}

void historique_annuler_coup (