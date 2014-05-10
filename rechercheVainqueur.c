#include "rechercheVainqueur.h"

#include "gestionPions.h"

extern Plateau plat;

Pos rechercheVainqueur_positionSuivantePaire(Pos p){
	Pos position = p;

	if(p.x == 1 && p.y == 0){
		p.x=0;
		p.y=-1;
	}
	else if(p.x == 0 && p.y == -1){
		p.x=-1;
		p.y=0;
	}
	else if(p.x == -1 && p.y == 0){
		p.x=0;
		p.y=1;
	}
	else{
		p.x=0;
		p.y=1;
	}

	return(position);
}

Pos rechercheVainqueur_positionSuivanteImpaire(Pos p){
	Position position = p;

	if(p.x == 1 && p.y == 0){
		p.x=1;
		p.y=-1;
	}
	else if(p.x == 1 && p.y == -1){
		p.x=0;
		p.y=-1;
	}
	else if(p.x == 0 && p.y == -1){
		p.x=-1;
		p.y=-1;
	}
	else if(p.x == -1 && p.y == -1){
		p.x=-1;
		p.y=0;
	}
	else if(p.x == -1 && p.y == 0){
		p.x=-1;
		p.y=0;
	}
	else if(p.x == -1 && p.y == 1){
		p.x=-1;
		p.y=1;
	}
	else if(p.x == 0 && p.y == 1){
		p.x=0;
		p.y=1;
	}
	else{
		p.x=1;
		p.y=1;
	}

	return(position);
}

bool rechercheVainqueur_chevreCapture(int nbChevreCapture){
	return(nbChevreCapture == 7);
}

bool rechercheVainqueur_depChevre(){
	Pos p, pOffset;
	pOffset.x=1;
	pOffset.y=0;

	for(int i=0;i < 5;++i)
		for(int j=0;j < 5;++j){
			p.x=i;
			p.y=j;
			if(gestionPions_estVide(p) && gestionPions_sommeImpair(p))
				for(int i=0;i < 4;++i){
					if(gestionPions_estDansPlateau(gestionPions_addPos(p,pOffset)) && !gestionPions_estTigre(gestionPions_addPos(p,pOffset)))
						return(true);
					p=rechercheVainqueur_positionSuivantePair(p);
				}
			else if(gestionPions_estVide(p))
				for(int i=0;i < 8;++i){
					if(gestionPions_estDansPlateau(gestionPions_addPos(p,pOffset)) && !gestionPions_estTigre(gestionPions_addPos(p,pOffset)))
						return(true);
					p=rechercheVainqueur_positionSuivanteImpair(p);
				}
		}

	return(false);
}

bool rechercheVainqueur_depTigre(Pos posT){
	Pos p;
	p.x=1;
	p.y=0;

	if(gestionPions_sommeImpair(posT))
		for(int i=0;i < 4;++i){
			if(gestionPions_estDansPlateau(gestionPions_addPos(posT,p)) && gestionPions_estVide(gestionPions_addPos(posT,p)))
				return(true);
			else if(gestionPions_estChevre(gestionPions_addPos(posT,p)) && gestionPions_estVide(gestionPions_addPos(posT,gestionPions_multPosSca(2,p))))
				return(true);
			p=rechercheVainqueur_positionSuivantePair(p);
		}
	else
		for(int i=0;i < 8;++i){
			if(gestionPions_estDansPlateau(gestionPions_addPos(posT,p)) && gestionPions_estVide(gestionPions_addPos(posT,p)))
				return(true);
			else if(gestionPions_estChevre(gestionPions_addPos(posT,p)) && gestionPions_estVide(gestionPions_addPos(posT,gestionPions_multPosSca(2,p))))
				return(true);
			p=rechercheVainqueur_positionSuivanteImpair(p);
		}

	return(false);
}

bool rechercheVainqueur_depTousTigre(){
	Pos p;

	for(int i=0;i < 5;++i)
		for(int j=0;j < 5;++j){
			p.x=i;
			p.y=j;
			if(gestionPions_estTigre(p))
				if(rechercheVainqueur_depTigre(plat.plateau[i][j])){
					return(true);
				}
		}

	return(false);
}

int rechercheVainqueur_vainqueurPresent(){
	if(rechercheVainqueur_chevreCapture(plat.nbChevreCapture) == 7)
		return 1;
	else if(!rechercheVainqueur_depTousTigre() || !rechercheVainqueur_depChevre())
		return 2;
	else
		return 0;
}

