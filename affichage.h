#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <ncurses.h>
#include "gestionPions.h"
#include "plateau.h"

/*
 E : aucune
 S : aucune
 Role : Fait appel à toute les fonction d'initialisation des fenêtres d'affichage.
*/
void affichage_init(void);

/*
 E : Dimension (hauteur, largeur) et coordonnées du coin supérieur droit
 S : aucune
 Role : Crée un Fenetre avec un contour rectiligne correspondant aux paramêtres passés
 */
WINDOW *create_newwin(int height, int width, int starty, int startx);

/*
 E : Fenetre, coordonnées du pointeur, largeur du champs dans lequel on écrit, message à écrire, identifiant de la paire de couleur à utiliser.
 S : aucune
 Role : Ecrit un message de la paire de couleur identifiée par color au centre d'une fenetre dont la largeur et le position du pointeur sont passés en parametre
 */
void affichage_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre dans laquelle est affiché le nombre de chevre capturees
 */
WINDOW *affichage_init_case_capture (void);

/*
 E : aucune
 S : aucune
 Role : Initialise la fenetre dans laquelle s'affiche l'historique
 */
WINDOW *affichage_init_historique (void);

/*
 E : une Cellule
 S : un caractère
 Role : renvois le caractère qui correspond au pion présent dans un cellule.
 */
char affichage_char_pion(Cell c);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre dans laquelle se trouve le plateau
 */
WINDOW *affichage_init_plateau (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton de fin de tour
 */
WINDOW *affichage_init_FinTour (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton d'annulation
 */
WINDOW *affichage_init_Annuler (void);

/*
 E : aucune
 S : aucune
 Role : initalisation de la fenetre d'affichage des messages.
 */
WINDOW *affichage_init_Chat (void);

/*
 E : aucune
 S : aucune
 Role : initialisation de la fenetre affichant le nombre de chevres restantes à placer
 */
WINDOW *affichage_init_ChevreRestante (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton d'annulation
 */
WINDOW *affichage_init_new (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton de sauvegarde
 */
WINDOW *affichage_init_save (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton de chargement
 */
WINDOW *affichage_init_load (void);

/*
 E : aucune
 S : aucune
 Role : initialise la fenetre/bouton quitter
 */
WINDOW *affichage_init_exit (void);

/*
 E : Message et identifiant d'une paire de couleur
 S : aucune
 Role : Affiche un message d'une certaine paire de couleur dans la fenetre de chat
 */
void affichage_message (char* Message, int color);

void affichage_message_erreur (char* Message, int color);

void affichage_maj_plateau_case (Pos p);

void affichage_maj_plateau (void);

void affichage_maj_rest (void);

void affichage_maj_capture (void);

void affichage_maj_Hist_etape (Coup* c, int ligne);

void affichage_maj_Hist (Historique h);

void affichage_maj_all (Historique h);

void affichage_scrollup_hist (Historique* h);

void affichage_scrolldown_hist (Historique* h);

void affichage_boiteDialogue(int i, char* str);

WINDOW* affichage_message_victoire (int tigre);

#endif
