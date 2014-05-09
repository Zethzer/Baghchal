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
Pos gestionPions_posMilieu(Pos p1, Pos p2);
int gestionPions_distLigne(Pos p1, Pos p2);
int gestionPions_distDiag(Pos p1, Pos p2);
bool gestionPions_estDansPlateau(Pos p);
bool gestionPions_peutDeplacer(Mvt m);
bool gestionPions_peutSauter(Mvt m);
bool gestionPions_DepValide(Mvt m);

#endif

