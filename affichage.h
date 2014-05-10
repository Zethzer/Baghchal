#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <ncurses.h>

void affichage_init(void);

WINDOW *create_newwin(int height, int width, int starty, int startx);

void affichage_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

WINDOW *affichage_init_case_capture (void);

WINDOW *affichage_init_historique (void);

char affichage_char_pion(Cell c);

WINDOW *affichage_init_plateau (void);

WINDOW *affichage_init_FinTour (void);

WINDOW *affichage_init_Annuler (void);

WINDOW *affichage_init_Chat (void);

WINDOW *affichage_init_ChevreRestante (void);

WINDOW *affichage_init_new (void);

WINDOW *affichage_init_save (void);

WINDOW *affichage_init_load (void);

WINDOW *affichage_init_exit (void);

void affichage_message (char* Message, int color);

void affichage_maj_plateau_case (Pos p);

#endif
