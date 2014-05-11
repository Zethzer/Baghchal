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
 S : aucune
 Role : regarde la position du clic et si elle est sur Annuler ou fin de tour applique l'opération correspondante
 */
int plateau_clicAnnulerFinirTour(Historique* h, Pos pSourisDep);

/*
 E : aucune
 S : aucune
 Role : Met à jour la fenetre affichant le nombre de chevres restantes à placer
 */
int plateau_deplacementPion(Pos pSourisDep, Mvt* m, Historique *h);

/*
 E : aucune
 S : aucune
 Role : Met à jour la fenetre affichant le nombre de chevres restantes à placer
 */
int plateau_placementPion(Pos pSourisDep, Historique* h);

/*
 E : une position
 S : Retour:
 * 1 si la position est sur le bouton annuler
 * 0 sinon
 Role : renvois un booleen valant vrai si la position est sur le bouton annuler
 */
int plateau_gestionTour(Historique* h, Pos pEvent);

/*
 E : une position
 S : Retour:
 * 1 si la position est sur le bouton annuler
 * 0 sinon
 Role : renvois un booleen valant vrai si la position est sur le bouton annuler
 */
void plateau_gestionVainqueur(Historique* h, int v);

#endif

