#ifndef __EVENEMENT_H__
#define __EVENEMENT_H__

#include "gestionPions.h"
#include "historique.h"

/*
 E : un pointeur vers l'historique
 S : Retourne : 
    La position d'un clic
    ET :
        * 1 si il y a eu un clic
        * 0 si il y a eu autre chose
 Role : récupère les coordonnées d'un clic ou s'occupe de déclencher le scrolling de l'historique si UP ou DOWN est pressé.
 */
int evenement_recupererEvenement(Historique* h, Pos* pEvent);

#endif