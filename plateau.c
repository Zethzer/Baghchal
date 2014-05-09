#include "plateau.h"

#include "gestionPions.h"
#include "rechercheVainqueur.h"

extern Plateau plat;

void plateau_init(){

	plat.nbTigres=4;
	plat.nbChevresSurPlateau=0;
	plat.nbChevresHorsPlateau=20;
	plat.nbChevreCapture=0;
	plat.tourJoueur=0;
	plat.phaseJeu=1;

	plat.plateau[0][0]="T";
	plat.plateau[0][4]="T";
	plat.plateau[4][0]="T";
	plat.plateau[4][4]="T";

	for(int i=1;i < 4;++i)
		plat.plateau[0][i]=".";
	for(int i=1;i < 4;++i)
		for(int j=0;j < 5;++j)
			plat.plateau[i][j]=".";
	for(int i=1;i < 4;++i)
		plat.plateau[4][i]=".";

}

void plateau_gestion(){
	Mvt m;

	if(rechercherVainqueur_vainqueurPresent()){
		printf("Y a un gagnant.");
	}
	else
		/* Deplacement */
		if(gestionPions_DepValide(m))
			printf("OK");
		else
			printf("NOK");
}

