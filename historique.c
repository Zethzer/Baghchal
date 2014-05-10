#include <stdio.h>
#include <stdlib.h>
#include "historique.h"
#include "plateau.h"
#include "gestionPions.h"

extern Plateau plat;

void historique_init (Historique h){
    h.first = NULL;
}

Coup *historique_coup_init (Mvt m, int chevre_mange){
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

Coup *historique_dernier_coup (Historique h){
    Coup* current = h->first;
    if (!current)
        return NULL;
    while (current->next){
        current = current->next;
    }
    return current;
}

void historique_map (Historique h, fonctionCoup f){
    Coup* current = h->first;
    while (current){
        f(current);
        current = current->next;
    }
}

void historique_annuler_coup (Historique h){
    Coup* dernier = historique_dernier_coup(h);
    plateau_deplacement(dernier->mvt.fin, dernier->mvt.deb);
    if (dernier->chevre_mange)
        plateau_ajouterChevre(gestionPions_posMilieu(dernier->mvt.fin, dernier->mvt.deb));
    historique_suppr_dernier_coup(h);
}



























