#ifndef __JOUER_H__
#define __JOUER_H__

#include <stdbool.h>
#include "gestionPions.h"
#include "historique.h"

/*
 E : un pointeur vers l'historique
 S : aucune
 Role : initialise tout le jeu
 */
void jouer_init(Historique* h);

/*
 E : pointeur vers l'historique
 S : Renvoie
 		- 1 : Clic sur nouveau jeu
 		- 2 : Clic sur charger
 		- 3 : Problème
 Role : Fonction principale de la gestion d'un tour. Vérifie si c'est au tour d'une chèvre ou d'un tigre et gère
 la phase de jeu (Placement ou Déplacement). Fais appel aux fonctions adéquates et gère l'interaction avec le menu principal
 et quitter.
 */
int jouer_gestionTour(Historique* h, Pos pEvent);

/*
 E : pointeur vers l'historique, valeur pour connaitre qui a gagné : 1 pour les tigres, 2 pour les chèvres
 S : Réinitialise le plateau si nouveau jeu ou charge une partie ou quitte le jeu
 Role : Gère l'affichage du message de victoire et la suite des actions :
 			- Nouveau Jeu
 			- Charger
 			- Quitter
 */
void jouer_gestionVainqueur(Historique* h, int v);

#endif