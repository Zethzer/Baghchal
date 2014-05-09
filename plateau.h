#ifndef __PLATEAU_H__
#define __PLATEAU_H__

typedef struct cell_s{
	char pion;
} Cell;

typedef struct plat_s{
	Cell plateau[5][5];
	int nbTigres;
	int nbChevres;
	int nbChevreCapture;
<<<<<<< HEAD
=======
	Cell plateau
>>>>>>> 2d05dd4b15d94876e878956acba4def2c3f9230b
} Plateau;

void plateau_gestion();

#endif

