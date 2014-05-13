#include "jouer.h"

#include <ncurses.h>
#include "evenement.h"
#include "plateau.h"
#include "affichage.h"
#include "save.h"

extern Plateau plat;
extern WINDOW *winChat;

void jouer_init(Historique* h){
	clear();
	plateau_init();
	affichage_init();
	historique_init(h);
}

int jouer_gestionTour(Historique* h, Pos pEvent){
	Mvt m;
	Coup *c;
	int codeRetour, codeBouton;
	Pos pPlat;

	if(!plat.tourJoueur){ // Chèvre
		if((codeRetour=plateau_verifierMenu(pEvent)) >= 1)
			return(codeRetour);
		if(!plat.phaseJeu){ // Placement
			if(plateau_clic2case(pEvent,&pPlat)){
				if(!plat.coupJoue){
					plat.coupJoue=plateau_placementPion(pPlat,h);
				}
				else
					affichage_message_erreur("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",2);
			}
			if((codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
				return(0);
		}
		else{ // Déplacement
			if(plateau_clic2case(pEvent, &pPlat)){
				if(!plat.coupJoue){
					if(plateau_deplacementPion(pPlat, &m, h))
						return(3);
					else{
						c=historique_init_coup(m, 1, gestionPions_estSaut(m), 0, 2, plat.tourJoueur);
						historique_ajouter_coup(h,c);
						plat.coupJoue=1;
					}
				}
				else
					affichage_message_erreur("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",2);
			}
			if((codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
				return(0);
		}
	}
	else{ // Tigre
		if((codeRetour=plateau_verifierMenu(pEvent)) >= 1)
			return(codeRetour);
		else if(plateau_clic2case(pEvent, &pPlat)){
			if(!plat.coupJoue){
				if(plateau_deplacementPion(pPlat, &m, h))
					return(3);
				else{
					c=historique_init_coup(m, 1, gestionPions_estSaut(m), 0, 2, plat.tourJoueur);
					historique_ajouter_coup(h,c);
					plat.coupJoue=true;
				}
			}
			else
				affichage_message_erreur("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",2);
		}
		if((codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
			return(0);
	}

	return(0);
}

void jouer_gestionVainqueur(Historique* h, int v){
	int codeRetour;
	char nomFichierChar[100];
	WINDOW *winWin;
	Pos pMenu;

	wclear(winChat);

	if(v == 1)
		winWin=affichage_message_victoire(1);
	else
		winWin=affichage_message_victoire(0);

	do{
		evenement_recupererEvenement(h,&pMenu);
		codeRetour=plateau_verifierMenu(pMenu);
		if(codeRetour == 1){
			delwin(winWin);
			jouer_init(h);
		}
		else if(codeRetour == 2){
			affichage_boiteDialogue(1, nomFichierChar);
			save_import(nomFichierChar);
			delwin(winWin);
			clear();
			historique_init(h);
			affichage_maj_Hist(*h);
			affichage_init();
		}
	}while(codeRetour != 1 && codeRetour != 2);
	
}

