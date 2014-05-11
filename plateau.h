#ifndef __PLATEAU_H__
#define __PLATEAU_H__

#include <stdbool.h>
#include "gestionPions.h"
#include "historique.h"

typedef struct cell_s{
	char pion;
} Cell;

typedef struct plat_s{
	Cell plateau[5][5];
	int nbTigres;
	int nbChevresSurPlateau;
	int nbChevresHorsPlateau;
	int nbChevreCapture;
	int tourJoueur;
	int phaseJeu;
} Plateau;

void plateau_init();

void plateau_deplacement(Pos deb, Pos fin);

void plateau_ajouterChevre(Pos p);

bool plateau_cliquezAnnulerCoup(Pos p);

bool plateau_cliquezFinTour(Pos p);

int clic2case (Pos pIn, Pos *pOut);

Mvt plateau_deplacementPion(int tourJoueur, Pos pSourisDep);

int plateau_gestionTour(Historique h);

#endif

