#ifndef __GESTION_PION_H__
#define __GESTION_PION_H__

#include <stdbool.h>

typedef struct pos_s{
	int x;
	int y;
} Pos;

typedef struct mvt_s{
	Pos deb;
	Pos fin;
} Mvt;

bool gestionPions_estVide(Pos p);

bool gestionPions_estChevre(Pos p);

bool gestionPions_estTigre(Pos p);

bool gestionPions_peutPlacer(Pos p);

int gestionPions_sommeImpair(Pos p);

Pos gestionPions_initPos (int x, int y);

Mvt gestionPions_initMvt (int xdeb, int ydeb, int xfin, int yfin);

Pos gestionPions_multPosSca(int v, Pos p);

Pos gestionPions_addPos(Pos p1, Pos p2);

Pos gestionPions_subPos(Pos p1, Pos p2);

Pos gestionPions_divPosSca(int v, Pos p);

Pos gestionPions_posMilieu(Pos p1, Pos p2);

int gestionPions_distLigne(Pos p1, Pos p2);

int gestionPions_distDiag(Pos p1, Pos p2);

bool gestionPions_estDansPlateau(Pos p);

bool gestionPions_peutDeplacer(Mvt m);

bool gestionPions_peutSauter(Mvt m);

bool gestionPions_DepValide(Mvt m);

bool gestionPions_estSaut(Mvt m);

#endif

