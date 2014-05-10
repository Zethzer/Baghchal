#include "gestionPions.h"

#include <stdlib.h>
#include "plateau.h"

extern Plateau plat;

bool gestionPions_estVide(Pos p){
	return(plat.plateau[p.x][p.y].pion == '.');
}

bool gestionPions_estChevre(Pos p){
	return(plat.plateau[p.x][p.y].pion == 'C');
}

bool gestionPions_estTigre(Pos p){
	return(plat.plateau[p.x][p.y].pion == 'T');
}

bool gestionPions_peutPlacer(Pos p){
	return(gestionPions_estVide(p));
}

int gestionPions_sommeImpair(Pos p){
	return((p.x+p.y)%2);
}

Pos gestionPions_multPosSca(int v, Pos p){
	Pos position;

	position.x=p.x*v;
	position.y=p.y*v;

	return(position);
}

Pos gestionPions_addPos(Pos p1, Pos p2){
	Pos p;

	p.x=p1.x+p2.x;
	p.y=p1.y+p2.y;

	return(p);
}

Pos gestionPions_subPos(Pos p1, Pos p2){
	Pos p;

	p.x=p1.x-p2.x;
	p.y=p1.y-p2.y;

	return(p);
}

Pos gestionPions_divPosSca(int v, Pos p){
	Pos position;

	position.x=p.x/v;
	position.y=p.y/v;

	return(position);
}

Pos gestionPions_posMilieu(Pos p1, Pos p2){
	Pos p;

	p=gestionPions_addPos(p1,p2);
	p=gestionPions_divPosSca(2,p);

	return(p);
}

int gestionPions_distLigne(Pos p1, Pos p2){
	return(!abs(p1.x-p2.x)?abs(p1.y-p2.y):(!abs(p1.y-p2.y)?abs(p1.x-p2.x):0));
}

int gestionPions_distDiag(Pos p1, Pos p2){
	return((abs(p1.x-p2.x) == abs(p1.y-p2.y))?abs(p1.x-p2.x):0);
}

bool gestionPions_estDansPlateau(Pos p){
	return((p.x >= 0 && p.x <= 4) && (p.y >= 0 && p.y <= 4));
}

bool gestionPions_peutDeplacer(Mvt m){
	return(gestionPions_estDansPlateau(m.fin) && gestionPions_estVide(m.fin)
	&& ((gestionPions_distLigne(m.deb,m.fin) == 1)
		|| ((!gestionPions_sommeImpair(m.deb))
		&& (gestionPions_distDiag(m.deb,m.fin) == 1))));
}

bool gestionPions_peutSauter(Mvt m){
	return(gestionPions_estTigre(m.deb) && gestionPions_estVide(m.fin)
	&& gestionPions_estDansPlateau(m.fin)
	&& gestionPions_estChevre(gestionPions_posMilieu(m.deb,m.fin))
	&& ((gestionPions_distLigne(m.deb,m.fin) == 2)
		|| ((!gestionPions_sommeImpair(m.deb))
		&& (gestionPions_distDiag(m.deb,m.fin) == 2))));
}

bool gestionPions_DepValide(Mvt m){
	return(gestionPions_peutDeplacer(m) || gestionPions_peutSauter(m));
}

