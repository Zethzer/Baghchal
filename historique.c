#include <stdio.h>
#include <stdlib.h>
#include "historique.h"
#include "plateau.h"

extern Plateau plat;

void historique_init (Historique* h){
    h->first = NULL;
    h->premierAffiche = 0;
    h->nbCoups = 0;
}

Coup *historique_coup_init (Mvt m, int tigre, int chevre_mange, int placement_chevre, int phase){
    Coup *c = malloc(sizeof(Coup));
    c->next = NULL;
    c->mvt = m;
    c->tigre = tigre;
    c->chevre_mange = chevre_mange;
    c->placement_chevre = placement_chevre;
    c->phase = phase;
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

void historique_ajouter_coup (Historique* h, Coup* c){
    Coup* current = h->first;
    Coup* pred = NULL;
    while (current){
        current = current->next;
    }
    if (pred)
        pred->next = c;
    else
        h->first = c;
    ++h->nbCoups;
    if (h->nbCoups > 21)
        ++h->premierAffiche;
}

int historique_suppr_dernier_coup (Historique* h){
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
    Coup* current = h.first;
    if (!current)
        return NULL;
    while (current->next){
        current = current->next;
    }
    return current;
}

void historique_map (Historique h, fonctionCoup f){
    Coup* current = h.first;
    int ligne = 0;
    while (current){
        if (ligne >= h.premierAffiche && ligne-h.premierAffiche <= 21)
            f(current, ligne);
        current = current->next;
        ++ligne;
    }
}

void historique_annuler_coup (Historique* h){
    Coup* dernier = historique_dernier_coup(*h);
    if (dernier->placement_chevre)
        plat.plateau[dernier->mvt.fin.x][dernier->mvt.fin.y].pion = '.';
    else
        plateau_deplacement(dernier->mvt.fin, dernier->mvt.deb);
    if (dernier->chevre_mange)
        plateau_ajouterChevre(gestionPions_posMilieu(dernier->mvt.fin, dernier->mvt.deb));
    if (dernier->phase != plat.phaseJeu)
        plat.phaseJeu = 1;
    historique_suppr_dernier_coup(h);
}