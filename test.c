#include <ncurses.h>
#include <stdbool.h>

#include "plateau.h"
#include "affichage.h"
#include "save.h"
#include "rechercheVainqueur.h"
#include "evenement.h"

Plateau plat;

int main(void){
	// Déclarations
	Historique h;
	char nomFichierChar[100];
	int codeVainqueur, codeTour;
	Pos pEvent;

	// Initialisation
	initscr();
	goto start;

start:
	plateau_init();
	affichage_init();
	historique_init(&h);

	while(!(codeVainqueur=rechercheVainqueur_vainqueurPresent())){
		affichage_maj_all(h);
		if(plat.tourJoueur)
			affichage_message("Joueur Tigre, a vous de jouer.",5);
		else
			affichage_message("Joueur chevre, a vous de jouer.",5);
		if(!evenement_recupererEvenement(&h,&pEvent))
				;
		else{
			if(!(codeTour=plateau_gestionTour(&h,pEvent))){
				if(!plat.nbChevresHorsPlateau)
					plat.phaseJeu=1;
			}
			else if(codeTour == 1)
				goto start;
			else if(codeTour == 2){
				affichage_boiteDialogue(1, nomFichierChar);
				save_import(nomFichierChar);
			}
		}
	}
	if(codeVainqueur == 1)
		;
		// Effacer la fenêtre
		// Menu : Nouveau, Charger, Quitter
		// Message : Tigre vainqueur
	else
		;
		// Effacer la fenêtre
		// Menu : Nouveau, Charger, Quitter
		// Message : Chèvre vainqueur

	endwin();
	return 0;
}