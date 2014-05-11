#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <stdbool.h>
#include "gestionPions.h"
#include "historique.h"

typedef struct cell_s{
	char pion;
} Cell;

typedef struct plat_s{
	Cell plateau[6][5];
	int nbTigres;
	int nbChevresSurPlateau;
	int nbChevresHorsPlateau;
	int nbChevreCapture;
	int tourJoueur;
	int phaseJeu;
	int coupJoue;
} Plateau;

/*
 E : un pointeur vers l'historique
 S : aucune
 Role : initialise tout le jeu
 */
void init(Historique* h);

/*
 E : aucune
 S : aucune
 Role : initialise le plateau de jeu
 */
void plateau_init();

/*
 E : position de debut, position de fin
 S : aucune
 Role : Effectue le déplacement de deb vers fin
 */
void plateau_deplacement(Pos deb, Pos fin);

/*
 E : une position
 S : aucune
 Role : ajoute un chevre à la position p
 */
void plateau_ajouterChevre(Pos p);

/*
 E : une position
 S : Retour:
        * 1 si la position est sur le bouton annuler
        * 0 sinon
 Role : renvois un booleen valant vrai si la position est sur le bouton annuler
 */
bool plateau_cliquezAnnulerCoup(Pos p);

/*
 E : une position
 S : Retour:
        * 1 si la position est sur le bouton fin du tour
        * 0 sinon
 Role : renvois un booleen valant vrai si la position est sur le bouton fin du tour
 */
bool plateau_cliquezFinTour(Pos p);

/*
 E : position
 S : position
 Role : renvois une position dans le plateau virtuel associée a celle en entrée prise sur la fenetre
 */
int clic2case (Pos pIn, Pos *pOut);

/*
 E : pointeur vers l'historique, position
 S : booleen
 Role : regarde la position du clic et si elle est sur Annuler ou fin de tour applique l'opération correspondante
 */
int plateau_clicAnnulerFinirTour(Historique* h, Pos pSourisDep);

/*
 E : position de départ du mouvement, pointeur vers le mouvement, pointeur vers l'historique
 S : Retourne 1 en cas de problème
 Role : Vérifie le contenu de la position de départ suivant le joueur : Si OK, demande la position
 d'arrivée, vérifie la validité du mouvement, l'applique sur le plateau, vérifie le saut et met à jour
 les chèvres capturés si c'est le cas
 */
int plateau_deplacementPion(Pos pSourisDep, Mvt* m, Historique *h);

/*
 E : position de départ, pointeur vers l'historique
 S : Retourne 1 en cas de problème
 Role : Vérifie le contenu de la position suivant si la case est vide ou non. Si OK, place le
 pion, met à jour le plateau.
 */
int plateau_placementPion(Pos pSourisDep, Historique* h);

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
int plateau_gestionTour(Historique* h, Pos pEvent);

/*
 E : pointeur vers l'historique, valeur pour connaitre qui a gagné : 1 pour les tigres, 2 pour les chèvres
 S : Réinitialise le plateau si nouveau jeu ou charge une partie ou quitte le jeu
 Role : Gère l'affichage du message de victoire et la suite des actions :
 			- Nouveau Jeu
 			- Charger
 			- Quitter
 */
void plateau_gestionVainqueur(Historique* h, int v);

#endif

