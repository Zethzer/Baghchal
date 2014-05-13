#include "rechercheVainqueur.h"

#include "plateau.h"
#include "gestionPions.h"
#include <stdio.h>

Plateau plat;

int main(void){
	Pos p, pOffset;
	int testsOK=0;

	printf("Tests unitaires rechercheVainqueur :\n");

	plateau_init();

	p.x=1;
	p.y=0;
	p=rechercheVainqueur_positionSuivantePaire(p);
	if(p.x == 0 && p.y == -1)
		++testsOK;

	p.x=0;
	p.y=-1;
	p=rechercheVainqueur_positionSuivantePaire(p);
	if(p.x == -1 && p.y == 0)
		++testsOK;

	p.x=-1;
	p.y=0;
	p=rechercheVainqueur_positionSuivantePaire(p);
	if(p.x == 0 && p.y == 1)
		++testsOK;

	p.x=0;
	p.y=1;
	p=rechercheVainqueur_positionSuivantePaire(p);
	if(p.x == 1 && p.y == 0)
		++testsOK;

	p.x=1;
	p.y=0;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == 1 && p.y == -1)
		++testsOK;
	
	p.x=1;
	p.y=-1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == 0 && p.y == -1)
		++testsOK;
	
	p.x=0;
	p.y=-1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == -1 && p.y == -1)
		++testsOK;
	
	p.x=-1;
	p.y=-1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == -1 && p.y == 0)
		++testsOK;
	
	p.x=-1;
	p.y=0;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == -1 && p.y == 1)
		++testsOK;
	
	p.x=-1;
	p.y=1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == 0 && p.y == 1)
		++testsOK;
	
	p.x=0;
	p.y=1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == 1 && p.y == 1)
		++testsOK;
	
	p.x=1;
	p.y=1;
	p=rechercheVainqueur_positionSuivanteImpaire(p);
	if(p.x == 1 && p.y == 0)
		++testsOK;

	plat.nbChevreCapture=6;
	if(!rechercheVainqueur_chevreCapture(plat.nbChevreCapture))
		++testsOK;

	plat.nbChevreCapture=7;
	if(rechercheVainqueur_chevreCapture(plat.nbChevreCapture))
		++testsOK;

	plat.plateau[2][2].pion='C';
	plat.plateau[3][2].pion='.';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(rechercheVainqueur_testDepChevre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='C';
	plat.plateau[3][2].pion='C';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(rechercheVainqueur_testDepChevre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='C';
	plat.plateau[3][2].pion='T';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(!rechercheVainqueur_testDepChevre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='T';
	plat.plateau[3][2].pion='.';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(rechercheVainqueur_testDepTigre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='T';
	plat.plateau[3][2].pion='C';
	plat.plateau[4][2].pion='.';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(rechercheVainqueur_testDepTigre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='T';
	plat.plateau[3][2].pion='T';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(!rechercheVainqueur_testDepTigre(p,pOffset))
		++testsOK;

	plat.plateau[2][2].pion='T';
	plat.plateau[3][2].pion='C';
	plat.plateau[4][2].pion='C';
	p.x=2;
	p.y=2;
	pOffset.x=1;
	pOffset.y=0;
	if(!rechercheVainqueur_testDepTigre(p,pOffset))
		++testsOK;

	printf("\t%d tests réussis sur 21.\n",testsOK);

	return 0;
}