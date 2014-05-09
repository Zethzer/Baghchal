#ifndef __PLATEAU_H__
#define __PLATEAU_H__

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
	Cell plateau;
} Plateau;

void plateau_gestion();

#endif

