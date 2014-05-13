#include "gestionPions.h"

#include "plateau.h"
#include <stdio.h>

Plateau plat;

int main(void){
	Pos p, p2;
	Mvt m;
	int testsOK=0, x, y, xfin, yfin, v;

	printf("Tests unitaires de gestionPions :\n");

	plateau_init();

	p.x=2;
	p.y=1;

	plat.plateau[2][1].pion='.';
	if(gestionPions_estVide(p))
		++testsOK;

	plat.plateau[2][1].pion='T';
	if(gestionPions_estTigre(p))
		++testsOK;

	plat.plateau[2][1].pion='C';
	if(gestionPions_estChevre(p))
		++testsOK;

	if(gestionPions_sommeImpair(p))
		++testsOK;

	x=1;
	y=1;
	p=gestionPions_initPos(x,y);
	if(p.x == 1 && p.y == 1)
		++testsOK;

	xfin=2;
	yfin=2;
	p.x=xfin;
	p.y=yfin;
	m=gestionPions_initMvt(x,y,xfin,yfin);
	if(m.deb.x == 1 && m.deb.y == 1 && m.fin.x == 2 && m.fin.y == 2)
		++testsOK;

	v=2;
	p=gestionPions_multPosSca(v,p);
	if(p.x == 4 && p.y == 4)
		++testsOK;

	p.x=2;
	p.y=2;
	p2.x=3;
	p2.y=3;
	p=gestionPions_addPos(p,p2);
	if(p.x == 5 && p.y == 5)
		++testsOK;

	p.x=2;
	p.y=2;
	p2.x=3;
	p2.y=3;
	p=gestionPions_subPos(p2,p);
	if(p.x == 1 && p.y == 1)
		++testsOK;

	p.x=4;
	p.y=4;
	p=gestionPions_divPosSca(v,p);
	if(p.x == 2 && p.y == 2)
		++testsOK;

	p.x=0;
	p.y=0;
	p2.x=0;
	p2.y=1;
	if(gestionPions_distLigne(p,p2) == 1)
		++testsOK;

	p.x=0;
	p.y=0;
	p2.x=2;
	p2.y=2;
	if(gestionPions_distDiag(p,p2) == 2)
		++testsOK;

	p.x=1;
	p.y=2;
	p2.x=12;
	p2.y=24;
	if(gestionPions_estDansPlateau(p))
		++testsOK;
	if(!gestionPions_estDansPlateau(p2))
		++testsOK;

	printf("\t%d tests réussis sur 14.\n",testsOK);

	return 0;
}