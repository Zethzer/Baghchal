#ifndef __RECHERCHER_VAINQUEUR_H__
#define __RECHERCHER_VAINQUEUR_H__

#include <stdbool.h>
#include "gestionPions.h"

/* E : Pos p
 * S : Retourne : p suivante
 * Rôle : Retourne la position suivante p en tournant dans le sens des aiguilles
 * d'une montre quand le pion central est sur une case paire.
 */
Pos rechercheVainqueur_positionSuivantePaire(Pos p);

/* E : Pos p
 * S : Retourne : p suivante
 * Rôle : Retourne la position suivante p en tournant dans le sens des aiguilles
 * d'une montre quand le pion central est sur une case impaire.
 */
Pos rechercheVainqueur_positionSuivanteImpaire(Pos p);

/* E : INT nbChevreCapture
 * S : Retourne un booleen :
 *		FAUX : nbChevreCapture = 7
 *		VRAI : nbChevreCapture < 7
 * Rôle : Vérifie le nombre de chèvres capturées.
 */
bool rechercheVainqueur_chevreCapture(int nbChevreCapture);

/* E : T
 * S : Retourne :
 *		FAUX : Aucune chèvre ne peut se déplacer
 *		VRAI : Au moins une chèvre peut se déplacer
 * Rôle : Vérifie si au moins une chèvre peut se déplacer.
 */
bool rechercheVainqueur_depChevre();

/* E : Position d'un tigre
 * S : Retourne :
 *		FAUX : Aucune case vide autour du tigre
 *		VRAI : Au moins une case vide est atteignable
 * Rôle : Vérifie si un tigre peut se déplacer.
 */
bool rechercheVainqueur_depTigre(Pos pTigre);

/* E : T
 * S : Retourne :
 *		FAUX : Aucun tigre ne peut se deplacer
 *		VRAI : Au moins un tigre peut se déplacer
 * Rôle : Vérifie si au moins un tigre peut se déplacer.
 */
bool rechercheVainqueur_depTousTigre();

/* E : T
 * S : Retourne :
 *		0 : Pas de vainqueur
 *		1 : Tigre vainqueur
 *		2 : Chèvre vainqueur
 * Rôle : Vérifie si un vainqueur est présent.
 */
int rechercheVainqueur_vainqueurPresent();

#endif

