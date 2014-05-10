#ifndef Bagh_chal_historique_h
#define Bagh_chal_historique_h

typedef struct coup_s{
    Mvt mvt;
    struct coup_s* next;
}Coup;

typedef struct historique_s{
    Coup *first;
}Historique;

typedef void (*fonctionCoup)(Coup *c);

void historique_init (Historique h);

Coup *historique_coup_init (Mvt m);

void historique_free_coup (Coup* c);

void historique_detruire_hist (Coup* first);

void historique_ajouter_coup (Historique h, Coup* c);

int historique_suppr_dernier_coup (Historique h);

void historique_map (Historique h, fonctionCoup f);

#endif