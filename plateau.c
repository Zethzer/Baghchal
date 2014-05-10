#include "plateau.h"

#include <ncurses.h>

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

void plateau_gestionTour(Historique h){
	Mvt m;
	Coup *c;
	bool finTour = false, coupJoue = false;
	Pos pSourisDep, pSourisArrive;

	if(!plat.phaseJeu) /* Placement */
		while(!finTour)
			if(!plat.tourJoueur){ /* Chèvre */
				// fonction evenement_positionSouris => recuperer position
				while(!gestionPions_estVide(pSourisArrive) && !coupJoue){
					affichage_message("Placement non valide ! La case doit etre vide.");
					// fonction evenement_positionSouris => recuperer position
				}
				if(!coupJoue){
					plateau_ajouterChevre(pSourisArrive);
					c=historique_coup_init(m);
					historique_ajouter_coup(h,c);
					coupJoue=true;
				}
				else
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.");
				if(plateau_cliquezAnnulerCoup(pSourisDep)){
					historique_annuler_coup(h);
					coupJoue=false;
				}
				else if(plateau_cliquezFinTour(pSourisDep))
					finTour=true;
			}
			else{ /* Tigre */
				// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
				// fonction evenement_positionSouris => recuperer position arrivée
				m.deb=pSourisDep;
				m.fin=pSourisArrive;
				while(!gestionPions_DepValide(m)){
					affichage_message("Deplacement non valide ! Recommencez.");
					// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
					// fonction evenement_positionSouris => recuperer position arrivée
					m.deb=pSourisDep;
					m.fin=pSourisArrive;
				}
				if(!coupJoue){
					plateau_deplacement(m.deb,m.fin);
					c=historique_coup_init(m);
					historique_ajouter_coup(h,c);
					coupJoue=true;
				}
				else
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.");
				if(plateau_cliquezAnnulerCoup(pSourisDep)){
					historique_annuler_coup(h);
					coupJoue=false;
				}
				else if(plateau_cliquezFinTour(pSourisDep))
					finTour=true;
			}
	else /* Déplacement */
		while(!finTour)
			if(!plat.tourJoueur){ /* Chèvre */
				// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
				// fonction evenement_positionSouris => recuperer position arrivée
				m.deb=pSourisDep;
				m.fin=pSourisArrive;
				while(!gestionPions_DepValide(m)){
					affichage_message("Deplacement non valide ! Recommencez.");
					// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
					// fonction evenement_positionSouris => recuperer position arrivée
					m.deb=pSourisDep;
					m.fin=pSourisArrive;
				}
				if(!coupJoue){
					plateau_deplacement(m.deb,m.fin);
					c=historique_coup_init(m);
					historique_ajouter_coup(h,c);
					coupJoue=true;
				}
				else
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.");
				if(plateau_cliquezAnnulerCoup(pSourisDep)){
					historique_annuler_coup(h);
					coupJoue=false;
				}
				else if(plateau_cliquezFinTour(pSourisDep))
					finTour=true;
			}
			else{ /* Tigre */
				// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
				// fonction evenement_positionSouris => recuperer position arrivée
				m.deb=pSourisDep;
				m.fin=pSourisArrive;
				while(!gestionPions_DepValide(m)){
					affichage_message("Deplacement non valide ! Recommencez.");
					// fonction evenement_positionSouris => recuperer position depart (Mettre en évidence en couleur ?)
					// fonction evenement_positionSouris => recuperer position arrivée
					m.deb=pSourisDep;
					m.fin=pSourisArrive;
				}
				if(!coupJoue){
					plateau_deplacement(m.deb,m.fin);
					c=historique_coup_init(m);
					historique_ajouter_coup(h,c);
					coupJoue=true;
				}
				else
					affichage_message("Vous avez deja joue. Annulez votre dernier coup joue pour retenter ou finissez le tour.");
				if(plateau_cliquezAnnulerCoup(pSourisDep)){
					historique_annuler_coup(h);
					coupJoue=false;
				}
				else if(plateau_cliquezFinTour(pSourisDep))
					finTour=true;
			}
}

