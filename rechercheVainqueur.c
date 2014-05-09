#include "rechercheVainqueur.h"

#include "gestionPions.h"

extern Plateau plat;

Pos rechercheVainqueur_positionSuivante(Pos p){

}

bool rechercheVainqueur_chevreCapture(int nbChevreCapture){

}

bool rechercheVainqueur_depChevre(){
	Pos p;
	bool depOk = false;

	for(int i=0;i < 4;++i)
		for(int j=0;j < 4;++j){
			p.x=i;
			p.y=j;
			if(gestionPions_estVide(p))
				/* Vérifier si elle est entouré de tigre
				 Au moins une case n'est pas entouré de tigre : chevre peut se deplacer 
				 Toutes les cases entourés de tigre : chevre bloqués : WIN */
		}

	return(depOk);
}

bool rechercheVainqueur_depTigre(Pos pTigre){
	Pos p;
	p.x=1;
	p.y=0;

	for(int i=0;i < 4;++i){
		if(gestionPions_estVide(posT+p))
			return true;
		else if(gestionPions_estChevre(posT+p) && gestionPions_estVide(posT+2*p))
			return true;
		p=rechercheVainqueur_positionSuivante(p);
	}

	return(false);
}

bool rechercheVainqueur_depTousTigre(){
	Pos p;
	bool depOk = false;

	for(int i=0;i < 4;++i)
		for(int j=0;j < 4;++j){
			p.x=i;
			p.y=j;
			if(gestionPions_estTigre(p))
				if(rechercheVainqueur_depTigre(plat.plateau[i][j])){
					depOk=true;
					i=5;
					j=5;
				}
				else
					depOk=false;
		}

	return(depOk);
}

int rechercheVainqueur_vainqueurPresent(){
	if(rechercheVainqueur_chevreCapture(plat.nbChevreCapture) == 7)
		return 1;
	else if(!rechercheVainqueur_depTigre() || !rechercheVainqueur_depChevre())
		return 2;
	else
		return 0;
}

