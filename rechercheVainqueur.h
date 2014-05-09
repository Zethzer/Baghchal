#ifndef __RECHERCHER_VAINQUEUR_H__
#define __RECHERCHER_VAINQUEUR_H__

Pos rechercheVainqueur_positionSuivante(Pos p);
bool rechercheVainqueur_chevreCapture(int nbChevreCapture);
bool rechercheVainqueur_depChevre();
bool rechercheVainqueur_depTigre(Pos pTigre);
bool rechercheVainqueur_depTousTigre();

/* E : T
 * S : Retourne :
 *		0 : Pas de vainqueur
 *		1 : Tigre vainqueur
 *		2 : Chèvre vainqueur
 */
int rechercheVainqueur_vainqueurPresent();

#endif

