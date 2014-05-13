#include "gestionPions.h"

#include "plateau.h"
#include <stdio.h>

Plateau plat;

int main(void){
	Pos p, p2;
	Mvt m;
	int testsOK = 0;

	printf("Test d'intégration de gestionPions :\n");

	plateau_init();

	p.x=0;
	p.y=0;
	p2.x=2;
	p2.y=2;
	p=gestionPions_posMilieu(p,p2);
	if(p.x == 1 && p.y == 1)
		++testsOK;

	// Tigre
	plat.plateau[1][1].pion='T';
	plat.plateau[1][0].pion='.';
	m.deb.x=1;
	m.deb.y=1;
	m.fin.x=1;
	m.fin.y=0;
	if(gestionPions_peutDeplacer(m))
		++testsOK;
	m.fin.x=3;
	m.fin.y=0;
	plat.plateau[3][0].pion='.';
	if(!gestionPions_peutDeplacer(m))
		++testsOK;
	plat.plateau[2][2].pion='C';
	plat.plateau[3][3].pion='.';
	m.fin.x=3;
	m.fin.y=3;
	if(gestionPions_peutSauter(m))
		++testsOK;
	plat.plateau[2][2].pion='.';
	if(!gestionPions_peutSauter(m))
		++testsOK;

	//Chèvre
	plat.plateau[3][1].pion='C';
	plat.plateau[3][2].pion='.';
	m.deb.x=3;
	m.deb.y=1;
	m.fin.x=3;
	m.fin.y=2;
	if(gestionPions_peutDeplacer(m))
		++testsOK;
	plat.plateau[3][3].pion='.';
	m.fin.x=3;
	m.fin.y=3;
	if(!gestionPions_peutDeplacer(m))
		++testsOK;


	// Tigre
	plat.plateau[1][1].pion='T';
	m.deb.x=1;
	m.deb.y=1;
	plat.plateau[1][0].pion='.';
	m.fin.x=1;
	m.fin.y=0;
	if(gestionPions_DepValide(m))
		++testsOK;
	plat.plateau[1][1].pion='T';
	plat.plateau[3][0].pion='.';
	m.deb.x=1;
	m.deb.y=1;
	m.fin.x=3;
	m.fin.y=0;
	if(!gestionPions_DepValide(m))
		++testsOK;
	plat.plateau[2][2].pion='C';
	m.fin.x=3;
	m.fin.y=3;
	if(gestionPions_DepValide(m))
		++testsOK;
	plat.plateau[2][2].pion='.';
	if(!gestionPions_DepValide(m))
		++testsOK;

	//Chèvre
	plat.plateau[3][1].pion='C';
	m.deb.x=3;
	m.deb.y=1;
	m.fin.x=3;
	m.fin.y=2;
	if(gestionPions_DepValide(m))
		++testsOK;
	m.fin.x=3;
	m.fin.y=3;
	if(!gestionPions_DepValide(m))
		++testsOK;

	m.deb.x=1;
	m.deb.y=1;
	m.fin.x=3;
	m.fin.y=3;
	if(gestionPions_estSaut(m))
		++testsOK;
	m.fin.x=2;
	m.fin.y=2;
	if(!gestionPions_estSaut(m))
		++testsOK;

	printf("\t%d tests sur 15 réussis.\n",testsOK);

	return 0;
}