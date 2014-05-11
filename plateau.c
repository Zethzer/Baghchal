#include "plateau.h"

#include <ncurses.h>
#include <stdlib.h>
#include "evenement.h"
#include "affichage.h"
#include "save.h"

extern Plateau plat;

void plateau_init(){

	plat.nbTigres=4;
	plat.nbChevresSurPlateau=0;
	plat.nbChevresHorsPlateau=20;
	plat.nbChevreCapture=0;
	plat.tourJoueur=0;
	plat.phaseJeu=0;

	plat.plateau[0][0].pion='T';
	plat.plateau[0][4].pion='T';
	plat.plateau[4][0].pion='T';
	plat.plateau[4][4].pion='T';

	for(int i=1;i < 4;++i)
		plat.plateau[0][i].pion='.';
	for(int i=1;i < 4;++i)
		for(int j=0;j < 5;++j)
			plat.plateau[i][j].pion='.';
	for(int i=1;i < 4;++i)
		plat.plateau[4][i].pion='.';

}

void plateau_deplacement(Pos deb, Pos fin){
	plat.plateau[fin.x][fin.y]=plat.plateau[deb.x][deb.y];
	plat.plateau[deb.x][deb.y].pion='.';
}

void plateau_ajouterChevre(Pos p){
	plat.plateau[p.x][p.y].pion='C';
	plat.nbChevresHorsPlateau--;
	plat.nbChevresSurPlateau++;
}

bool plateau_cliquezAnnulerCoup(Pos p){
	return((p.y >= (LINES/2)+6 && p.y <= (LINES/2)+13) && (p.x >= (3*COLS/4)+13
			&& p.x <= (((COLS/2)-33)/2)+(3*COLS/4)+13));
}

bool plateau_cliquezFinTour(Pos p){
	return((p.y >= (LINES/2)+6 && p.y <= (LINES/2)+13) && (p.x >= (COLS/2)+28
			&& p.x <= (((COLS/2)-33)/2)+(COLS/2)+28));
}

int plateau_verifierMenu(Pos p){
	char nomFichierSauv[75];

	if(p.x >= 0 && p.y >= 0 && p.x <= 14 && p.y <= 3)
		return(1);
	else if(p.x >= 15 && p.y >= 0 && p.x <= 29 && p.y <= 3){
		affichage_boiteDialogue(0, nomFichierSauv);
		save_export(nomFichierSauv);
	}
	else if(p.x >= 30 && p.y >= 0 && p.x <= 40 && p.y <= 3)
		return(2);
	else if(p.x >= COLS-11 && p.y >= 0 && p.x <= COLS && p.y <= 3){
		endwin();
		exit(0);
	}

	return(0);
}

int plateau_clic2case (Pos pIn, Pos *pOut){
    pIn.x -= ((COLS-49)/2)+2;
    pIn.y -= ((LINES-25)/2)+1;
    if ((pIn.x%10 <=4) && (pIn.x%10 >=0) && (pIn.y%5 <= 2) && (pIn.y >=0)){
        pOut->x = pIn.x /10;
        pOut->y = pIn.y / 5;
        return(1);
    }else
        return(0);
}

int plateau_clicAnnulerFinirTour(Historique h, Pos pSourisDep){

	if(plateau_cliquezAnnulerCoup(pSourisDep)){
		historique_annuler_coup(&h);
		return(0);
	}
	else
		affichage_message("Vous devez jouer avant d'annuler votre coup.",4);
	if(plateau_cliquezFinTour(pSourisDep))
		return(1);
	else
		affichage_message("Vous devez jouer avant de finir votre tour.",4);
	return(0);
}

Mvt plateau_deplacementPion(int tourJoueur, Pos pSourisDep, Historique h){
	Mvt m;
	Pos pSouris, pSourisArrive, pMilieu;

	m.deb=pSourisDep;
	if(!tourJoueur)
		while(!gestionPions_estChevre(pSourisDep)){
			affichage_message("Ce n'est pas une chevre.",4);
			evenement_recupererEvenement(h,&pSouris);
			m.deb=pSouris;
		}
	else
		while(!gestionPions_estTigre(pSourisDep)){
			affichage_message("Ce n'est pas un tigre.",4);
			evenement_recupererEvenement(h,&pSouris);
			m.deb=pSouris;
		}
	evenement_recupererEvenement(h,&pSouris);
	m.fin=pSourisArrive;
	while(!gestionPions_DepValide(m)){
		affichage_message("Deplacement non valide ! Recommencez.",4);
		evenement_recupererEvenement(h,&pSouris);
		evenement_recupererEvenement(h,&pSouris);
		m.deb=pSouris;
		m.fin=pSourisArrive;
	}
	plateau_deplacement(m.deb,m.fin);
	if(gestionPions_estTigre(m.deb) && gestionPions_estChevre((pMilieu=gestionPions_posMilieu(m.deb,m.fin)))){
		plat.nbChevreCapture++;
		plat.plateau[pMilieu.x][pMilieu.y].pion='.';
	}
	
	return(m);
}

void plateau_placementPion(Pos pSourisDep, Historique h){
	Pos pSouris;
	Coup* c;
	Mvt m;

	while(!gestionPions_estChevre(pSourisDep)){
		affichage_message("Ce n'est pas une chevre.",4);
		evenement_recupererEvenement(h,&pSouris);
	}
	while(!gestionPions_estVide(pSourisDep)){
		affichage_message("Placement non valide ! La case doit etre vide.",4);
		evenement_recupererEvenement(h,&pSouris);
	}
	plateau_ajouterChevre(pSouris);
	m.deb.x=5;
	m.deb.y=4;
	m.fin=pSouris;
	c=historique_init_coup(m, 0, 0, 1, plat.phaseJeu);
	historique_ajouter_coup(&h,c);
}

int plateau_gestionTour(Historique h){
	Mvt m;
	Coup *c;
	int codeRetour, codeBouton;
	bool finTour = false, coupJoue = false;
	Pos pEvent, pPlat;

	while(!finTour)
		if(!plat.tourJoueur){ // Chèvre
			if(!evenement_recupererEvenement(h,&pEvent))
				;
			else
				if(!plat.phaseJeu){ // Placement
					if((codeRetour=plateau_verifierMenu(pEvent)) != 1 && codeRetour)
						return(codeRetour);
					else if(plateau_clic2case(pEvent,&pPlat)){
						if(!coupJoue){
							plateau_placementPion(pPlat,h);
							coupJoue=true;
						}
						else
							affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					}
					if(coupJoue && (codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
						finTour=true;
					else
						coupJoue=false;
				}
				else{ // Déplacement
					if((codeRetour=plateau_verifierMenu(pEvent)) != 1 && codeRetour)
						return(codeRetour);
					else if(plateau_clic2case(pEvent, &pPlat)){
						if(!coupJoue){
							m=plateau_deplacementPion(plat.tourJoueur, pPlat, h);
							c=historique_init_coup(m, 0, 0, 0, 2);
							historique_ajouter_coup(&h,c);
							coupJoue=true;
						}
						else
							affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					}
					if(coupJoue && (codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
						finTour=true;
					else
						coupJoue=false;
				}
		}
		else{ // Tigre
			if(!evenement_recupererEvenement(h,&pEvent))
				;
			else
				if((codeRetour=plateau_verifierMenu(pEvent)) != 1 && codeRetour)
					return(codeRetour);
				else if(plateau_clic2case(pEvent, &pPlat)){
					if(!coupJoue){
						m=plateau_deplacementPion(plat.tourJoueur, pPlat, h);
						c=historique_init_coup(m, 1, gestionPions_estSaut(m), 0, 2);
						historique_ajouter_coup(&h,c);
						coupJoue=true;
					}
					else
						affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
				}
				if(coupJoue && (codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
						finTour=true;
					else
						coupJoue=false;
		}
	return 0;
}
