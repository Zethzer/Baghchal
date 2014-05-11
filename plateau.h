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

void plateau_init();

void plateau_deplacement(Pos deb, Pos fin);

void plateau_ajouterChevre(Pos p);

bool plateau_cliquezAnnulerCoup(Pos p);

bool plateau_cliquezFinTour(Pos p);

int clic2case (Pos pIn, Pos *pOut);

int plateau_clicAnnulerFinirTour(Historique* h, Pos pSourisDep);

int plateau_deplacementPion(Pos pSourisDep, Mvt* m, Historique *h);

void plateau_placementPion(Pos pSourisDep, Historique* h);

int plateau_gestionTour(Historique* h, Pos pEvent);

#endif

