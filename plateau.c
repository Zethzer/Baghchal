#include "plateau.h"

#include <ncurses.h>
#include <stdlib.h>
#include "evenement.h"
#include "affichage.h"
#include "save.h"

extern Plateau plat;
extern WINDOW *winRest;

void plateau_init(){

	plat.nbTigres=4;
	plat.nbChevresSurPlateau=0;
	plat.nbChevresHorsPlateau=20;
	plat.nbChevreCapture=0;
	plat.tourJoueur=0;
	plat.phaseJeu=0;
	plat.coupJoue=0;

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
	affichage_maj_rest();
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
	char nomFichierSauv[100];

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
    wmove(winRest, 3, 4);
    wprintw(winRest, "%d %d", pIn.x, pIn.y);
    wrefresh(winRest);
    if ((pIn.x%10 <=4) && (pIn.x%10 >= 0) && (pIn.y%5 <= 2) && (pIn.y%5 >=0) && (pIn.x <= 50) && (pIn.y <= 25)){
        pOut->x = pIn.x /10;
        pOut->y = pIn.y / 5;
    wmove(winRest, 4, 4);
    wprintw(winRest, "%d %d", pOut->x, pOut->y);
    wrefresh(winRest);
        return(1);
    }else
        return(0);
}

int plateau_clicAnnulerFinirTour(Historique* h, Pos pSourisDep){

	if(plateau_cliquezAnnulerCoup(pSourisDep)){
		historique_annuler_coup(h);
		return(0);
	}
	if(plateau_cliquezFinTour(pSourisDep)){
		plat.tourJoueur=!(plat.tourJoueur);
		plat.coupJoue=0;
		return(1);
	}
	return(0);
}

int plateau_deplacementPion(Pos pSourisDep, Mvt* m, Historique *h){
	Pos pMilieu, pSourisArrive, pPlat;

	m->deb=pSourisDep;
	if(!plat.tourJoueur){
		if(!gestionPions_estChevre(pSourisDep)){
			affichage_message("Ce n'est pas une chevre.",4);
			return(1);
		}
	}
	else{
		if(!gestionPions_estTigre(pSourisDep)){
			affichage_message("Ce n'est pas un tigre.",4);
			return(1);
		}
	}
	affichage_message("Choisissez la destination.",5);
	evenement_recupererEvenement(h,&pSourisArrive);
	if(plateau_clic2case(pSourisArrive,&pPlat))
		m->fin=pPlat;
	if(!gestionPions_DepValide(*m)){
		affichage_message("Deplacement non valide ! Recommencez.",4);
		return(1);
	}
	plateau_deplacement(m->deb,m->fin);
	if(gestionPions_estTigre(m->deb) && gestionPions_estChevre((pMilieu=gestionPions_posMilieu(m->deb,m->fin)))){
		plat.nbChevreCapture++;
		plat.plateau[pMilieu.x][pMilieu.y].pion='.';
	}
	
	return(0);
}

void plateau_placementPion(Pos pSourisDep, Historique* h){
	Coup* c;
	Mvt m;

	if(!gestionPions_estVide(pSourisDep))
		affichage_message("Placement non valide ! La case doit etre vide.",4);
	else{
		plateau_ajouterChevre(pSourisDep);
		m.deb.x=5;
		m.deb.y=4;
		m.fin=pSourisDep;
		c=historique_init_coup(m, 0, 0, 1, plat.phaseJeu, plat.tourJoueur);
		historique_ajouter_coup(h,c);
	}
}

int plateau_gestionTour(Historique* h, Pos pEvent){
	Mvt m;
	Coup *c;
	int codeRetour, codeBouton;
	Pos pPlat;

	if(!plat.tourJoueur){ // Chèvre
		wmove(winRest,2,5);
		wprintw(winRest,"y=%d x=%d",pEvent.y,pEvent.x);
		wrefresh(winRest);
		if((codeRetour=plateau_verifierMenu(pEvent)) != 1 && codeRetour)
			return(codeRetour);
		if(!plat.phaseJeu){ // Placement
			if(plateau_clic2case(pEvent,&pPlat)){
				if(!plat.coupJoue){
					plateau_placementPion(pPlat,h);
					plat.coupJoue=1;
				}
				else
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
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
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
			}
			if((codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
				return(0);
		}
	}
	else{ // Tigre
		if((codeRetour=plateau_verifierMenu(pEvent)) != 1 && codeRetour)
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
				affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
		}
		if((codeBouton=plateau_clicAnnulerFinirTour(h,pEvent)))
			return(0);
	}

	return(0);
}
