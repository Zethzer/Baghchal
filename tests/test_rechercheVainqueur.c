#include "rechercheVainqueur.h"

#include "plateau.h"
#include "save.h"
#include "gestionPions.h"
#include <stdio.h>
#include <ncurses.h>

Plateau plat;

int main(void){
	int testsOK=0, codeVainqueur;

	printf("Tests d'intégration de rechercheVainqueur :\n");

	plateau_init();

	save_import("test_vc");
	if(!rechercheVainqueur_depTousTigre())
		++testsOK;

	save_import("test_vc2");
	if(rechercheVainqueur_depChevre())
		++testsOK;
	if(rechercheVainqueur_depTousTigre())
		++testsOK;

	save_import("test_vc3");
	if(!rechercheVainqueur_depChevre())
		++testsOK;

	save_import("test_vc");
	if((codeVainqueur=rechercheVainqueur_vainqueurPresent()) == 2)
		++testsOK;

	save_import("test_vc3");
	if((codeVainqueur=rechercheVainqueur_vainqueurPresent()) == 2)
		++testsOK;

	save_import("test_vc2");
	if((codeVainqueur=rechercheVainqueur_vainqueurPresent()) == 0)
		++testsOK;

	save_import("test_vc4");
	if((codeVainqueur=rechercheVainqueur_vainqueurPresent()) == 1)
		++testsOK;

	printf("\t%d tests réussis sur 8.\n",testsOK);

	return 0;
}