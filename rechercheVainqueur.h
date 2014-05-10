#ifndef __RECHERCHER_VAINQUEUR_H__
#define __RECHERCHER_VAINQUEUR_H__

#include <stdbool.h>
#include "gestionPions.h"

Pos rechercheVainqueur_positionSuivantePaire(Pos p);

Pos rechercheVainqueur_positionSuivanteImpaire(Pos p);

bool rechercheVainqueur_chevreCapture(int nbChevreCapture);

bool rechercheVainqueur_depChevre();

bool rechercheVainqueur_depTigre(Pos pTigre);

bool rechercheVainqueur_depTousTigre();

/* Rôle : Vérifie si un vainqueur est présent.
 * E : T
 * S : Retourne :
 *		0 : Pas de vainqueur
 *		1 : Tigre vainqueur
 *		2 : Chèvre vainqueur
 */
int rechercheVainqueur_vainqueurPresent();

#endif

