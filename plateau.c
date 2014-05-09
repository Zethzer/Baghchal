#include "plateau.h"

#include "gestionPions.h"
#include "rechercheVainqueur.h"

extern Plateau plat;

void plateau_init(){

	plat.nbChevres=20;
	plat.nbTigres=4;

	plat.plateau[0][0]="T";
	plat.plateau[0][4]="T";
	plat.plateau[4][0]="T";
	plat.plateau[4][4]="T";
}

void plateau_gestion(){
	Mvt m;

	if(rechercherVainqueur_vainqueurPresent()){
		printf("Y a un gagnant.");
	}
	else
		if(gestionPions_DepValide(m))
			printf("OK");
		else
			printf("NOK");
}

