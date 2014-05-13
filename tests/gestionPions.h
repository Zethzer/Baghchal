#ifndef __GESTION_PION_H__
#define __GESTION_PION_H__

#include <stdbool.h>

typedef struct pos_s{
	int x;
	int y;
} Pos;

typedef struct mvt_s{
	Pos deb;
	Pos fin;
} Mvt;

/* E : Pos p
 * S : Retourne :
 *		FAUX : La case n'est pas vide
 *		VRAI : La case est vide
 * Rôle : Vérifie si la case est vide.
 */
bool gestionPions_estVide(Pos p);

/* E : Pos p
 * S : Retourne :
 *		FAUX : La case n'est pas chèvre
 *		VRAI : La case est une chèvre
 * Rôle : Vérifie si la case est une chèvre.
 */
bool gestionPions_estChevre(Pos p);

/* E : Pos p
 * S : Retourne :
 *		FAUX : La case n'est pas un tigre
 *		VRAI : La case est un tigre
 * Rôle : Vérifie si la case est un tigre.
 */
bool gestionPions_estTigre(Pos p);

/* E : Pos p
 * S : Retourne :
 *		FAUX : La case ne peut pas recevoir un pion
 *		VRAI : La case peut recevoir un pion
 * Rôle : Vérifie si la case peut recevoir un pion.
 */
bool gestionPions_peutPlacer(Pos p);

/* E : Pos p
 * S : Retourne :
 *		(p.x+p.y)%2
 * Rôle : Vérifie si la case est à coordonnées paire ou impaire.
 */
int gestionPions_sommeImpair(Pos p);

/* E : int X et Y
 * S : Retourne :
 *		p.x=X;
 *		p.y=Y;
 * Rôle : Initialise une position aux coordonnées X et Y.
 */
Pos gestionPions_initPos (int x, int y);

/* E : int XDEB et YDEB, XFIN et YFIN
 * S : Retourne :
 *		m.deb.x=XDEB;
 *		m.deb.y=YDEB;
 *		m.fin.x=XFIN;
 *		m.fin.y=YFIN;
 * Rôle : Initialise un mouvement aux coordonnées XDEB, YDEB, XFIN et YFIN.
 */
Mvt gestionPions_initMvt (int xdeb, int ydeb, int xfin, int yfin);

/* E : Pos P1 et V
 * S : Retourne :
 *		p.x=P1.X*V
 *		p.y=P1.Y*V
 * Rôle : Multiplie une position par un nombre.
 */
Pos gestionPions_multPosSca(int v, Pos p);

/* E : Pos P1 et P2
 * S : Retourne :
 *		p.x=P1.X+P2.X
 *		p.y=P1.X+P1.Y
 * Rôle : Additionne deux positions.
 */
Pos gestionPions_addPos(Pos p1, Pos p2);

/* E : Pos P1 et P2
 * S : Retourne :
 *		p.x=P1.X-P2.X
 *		p.y=P1.X-P1.Y
 * Rôle : Soustrais deux positions.
 */
Pos gestionPions_subPos(Pos p1, Pos p2);

/* E : Pos P1 et V
 * S : Retourne :
 *		p.x=P1.X/V
 *		p.y=P1.Y/V
 * Rôle : Divise une position par un nombre.
 */
Pos gestionPions_divPosSca(int v, Pos p);

/* E : Pos P1 et P2
 * S : Retourne :
 *			p=gestionPions_addPos(P1,P2);
			p=gestionPions_divPosSca(2,p);
 * Rôle : Calcule la position au centre des positions P1, P2.
 */
Pos gestionPions_posMilieu(Pos p1, Pos p2);

/* E : Pos P1 et P2
 * S : Retourne :
 *			1 : Renvoie la distance si c'est une ligne
 *			0 : sinon
 * Rôle : Renvoie la distance suivant une ligne.
 */
int gestionPions_distLigne(Pos p1, Pos p2);

/* E : Pos P1 et P2
 * S : Retourne :
 *			2 : Renvoie la distance si c'est une diagonale
 *			0 : sinon
 * Rôle : Renvoie la distance suivant une diagonale.
 */
int gestionPions_distDiag(Pos p1, Pos p2);

/* E : Pos P
 * S : Retourne :
 *			VRAI : P est dans le plateau
 *			FAUX : P n'est pas dans le plateau
 * Rôle : Vérifie si la position P est dans le plateau
 */
bool gestionPions_estDansPlateau(Pos p);

/* E : Mvt M;
 * S : Retourne :
 *			VRAI : M est possible
 *			FAUX : M n'est pas possible
 * Rôle : Vérifie si un mouvement de déplacement est possible.
 */
bool gestionPions_peutDeplacer(Mvt m);

/* E : Mvt M
 * S : Retourne :
 *			VRAI : M est possible
 *			FAUX : M n'est pas possible
 * Rôle : Vérifie si un mouvement de saut est possible.
 */
bool gestionPions_peutSauter(Mvt m);

/* E : Mvt M
 * S : Retourne :
 *			VRAI : M est valide
 *			FAUX : M n'est pas valide
 * Rôle : Vérifie si un mouvement est valide.
 */
bool gestionPions_DepValide(Mvt m);

/* E : Mvt M
 * S : Retourne :
 *			VRAI : M est un saut
 *			FAUX : M n'est pas un saut
 * Rôle : Vérifie si un mouvement est un saut.
 */
bool gestionPions_estSaut(Mvt m);

#endif

