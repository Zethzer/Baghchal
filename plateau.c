#include "plateau.h"

#include <ncurses.h>
#include <stdlib.h>
#include "evenement.h"
#include "affichage.h"

extern Plateau plat;

void plateau_init(){

	plat.nbTigres=4;
	plat.nbChevresSurPlateau=0;
	plat.nbChevresHorsPlateau=20;
	plat.nbChevreCapture=0;
	plat.tourJoueur=0;
	plat.phaseJeu=1;

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

	if(p.x >= 0 && p.y >= 0 && p.x <= 14 && p.y <= 3)
		return(1);
	else if(p.x >= 15 && p.y >= 0 && p.x <= 29 && p.y <= 3)
		;
		//save_import(affichage_boiteDialogue(0));
	else if(p.x >= 30 && p.y >= 0 && p.x <= 40 && p.y <= 3)
		return(2);
	else if(p.x >= COLS-11 && p.y >= 0 && p.x <= COLS && p.y <= 3)
		exit(0);

	return(0);
}

int clic2case (Pos pIn, Pos *pOut){
    pIn.x -= ((COLS-49)/2)+2;
    pIn.y -= ((LINES-25)/2)+1;
    if ((pIn.x%10 <=4) && (pIn.x%10 >=0) && (pIn.y%5 <= 2) && (pIn.y >=0)){
        pOut->x = pIn.x /10;
        pOut->y = pIn.y / 5;
        return 1;
    }else
        return 0;
}

int plateau_gestionTour(Historique h){
	Mvt m;
	Coup *c;
	int codeRetour;
	bool finTour = false, coupJoue = false;
	Pos pSourisDep, pSourisArrive;

	if(!plat.phaseJeu) // Placement
		while(!finTour)
			if(!plat.tourJoueur){ // Chèvre
				pSourisDep=evenement_recupererEvenementSouris();
				if((codeRetour=plateau_verifierMenu(pSourisDep)) != 1 && codeRetour)
					return(codeRetour);
				else{
					while(!gestionPions_estChevre(pSourisDep)){
						affichage_message("Ce n'est pas une chevre.",4);
						pSourisDep=evenement_recupererEvenementSouris();
					}
					while(!gestionPions_estVide(pSourisDep) && !coupJoue){
						affichage_message("Placement non valide ! La case doit etre vide.",4);
						pSourisDep=evenement_recupererEvenementSouris();
					}
					if(!coupJoue){
						plateau_ajouterChevre(pSourisDep);
						m.deb.x=-1;
						m.deb.y=-1;
						m.fin=pSourisDep;
						c=historique_coup_init(m, 0, 0, 1, plat.phaseJeu);
						historique_ajouter_coup(h,c);
						coupJoue=true;
					}
					else
						affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					if(plateau_cliquezAnnulerCoup(pSourisDep)){
						historique_annuler_coup(h);
						coupJoue=false;
					}
					else if(plateau_cliquezFinTour(pSourisDep))
						finTour=true;
				}
			}
			else{ // Tigre
				pSourisDep=evenement_recupererEvenementSouris();
				if((codeRetour=plateau_verifierMenu(pSourisDep)) != 1 && codeRetour)
					return(codeRetour);
				else{
					m.deb=pSourisDep;
					while(!gestionPions_estChevre(pSourisDep)){
						affichage_message("Ce n'est pas un tigre.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
					}
					pSourisArrive=evenement_recupererEvenementSouris();
					m.fin=pSourisArrive;
					while(!gestionPions_DepValide(m)){
						affichage_message("Deplacement non valide ! Recommencez.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						pSourisArrive=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
						m.fin=pSourisArrive;
					}
					if(!coupJoue){ // Le cas de manger une chèvre
						plateau_deplacement(m.deb,m.fin);
						c=historique_coup_init(m, 1, gestionPions_estSaut(m), 0, plat.phaseJeu);
						historique_ajouter_coup(h,c);
						coupJoue=true;
					}
					else
						affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					if(plateau_cliquezAnnulerCoup(pSourisDep)){
						historique_annuler_coup(h);
						coupJoue=false;
					}
					else if(plateau_cliquezFinTour(pSourisDep))
						finTour=true;
				}
			}
	else // Déplacement
		while(!finTour)
			if(!plat.tourJoueur){ // Chèvre
				pSourisDep=evenement_recupererEvenementSouris();
				if((codeRetour=plateau_verifierMenu(pSourisDep)) != 1 && codeRetour)
					return(codeRetour);
				else{
					m.deb=pSourisDep;
					while(!gestionPions_estChevre(pSourisDep)){
						affichage_message("Ce n'est pas une chevre.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
					}
					pSourisArrive=evenement_recupererEvenementSouris();
					m.fin=pSourisArrive;
					while(!gestionPions_DepValide(m)){
						affichage_message("Deplacement non valide ! Recommencez.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						pSourisArrive=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
						m.fin=pSourisArrive;
					}
					if(!coupJoue){
						plateau_deplacement(m.deb,m.fin);
						c=historique_coup_init(m, 0, 0, 0, 2);
						historique_ajouter_coup(h,c);
						coupJoue=true;
					}
					else
						affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					if(plateau_cliquezAnnulerCoup(pSourisDep)){
						historique_annuler_coup(h);
						coupJoue=false;
					}
					else if(plateau_cliquezFinTour(pSourisDep))
						finTour=true;
				}
			}
			else{ // Tigre
				pSourisDep=evenement_recupererEvenementSouris();
				if((codeRetour=plateau_verifierMenu(pSourisDep)) != 1 && codeRetour)
					return(codeRetour);
				else{
					m.deb=pSourisDep;
					while(!gestionPions_estTigre(pSourisDep)){
						affichage_message("Ce n'est pas un tigre.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
					}
					pSourisArrive=evenement_recupererEvenementSouris();
					m.fin=pSourisArrive;
					while(!gestionPions_DepValide(m)){
						affichage_message("Deplacement non valide ! Recommencez.",4);
						pSourisDep=evenement_recupererEvenementSouris();
						pSourisArrive=evenement_recupererEvenementSouris();
						m.deb=pSourisDep;
						m.fin=pSourisArrive;
					}
					if(!coupJoue){
						plateau_deplacement(m.deb,m.fin);
						c=historique_coup_init(m, 1, gestionPions_estSaut(m), 0, 2);
						historique_ajouter_coup(h,c);
						coupJoue=true;
					}
					else
						affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.",4);
					if(plateau_cliquezAnnulerCoup(pSourisDep)){
						historique_annuler_coup(h);
						coupJoue=false;
					}
					else if(plateau_cliquezFinTour(pSourisDep))
						finTour=true;
				}
			}
    return 0;
}
