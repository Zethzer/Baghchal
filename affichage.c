#include <stdio.h>
#include <string.h>
#include "plateau.h"
#include "affichage.h"

extern Plateau plat;

WINDOW *winCapture, *winHist, *winPlat, *winChat, *winRest;

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
    
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters
                                 * for the vertical and horizontal
                                 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/
    
	return local_win;
}

void affichage_print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color){
	int length, x, y;
	float temp;
    
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
    
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}



WINDOW *affichage_init_case_capture (void){
    winCapture = create_newwin(6, 40, 7, 5);
    char chevrecapture[2];
    chevrecapture[0] = '0'+plat.nbChevreCapture;
    chevrecapture[1] = '\0';
    affichage_print_in_middle(winCapture, 2, 0, 40, "Nombre de chevre capturees :", 0);
    affichage_print_in_middle(winCapture, 3, 0, 40, chevrecapture, 0);
    wnoutrefresh(winCapture);
    return winCapture;
}

WINDOW *affichage_init_historique (void){
    winHist = create_newwin(25, 40, 15, 5);
    affichage_print_in_middle(winHist, 0, 0, 40, " Historique ", COLOR_PAIR(1));
    wnoutrefresh(winHist);
    return winHist;
}

char affichage_char_pion(Cell c){
    return (c.pion == '.')?' ':c.pion;
}

WINDOW *affichage_init_plateau (void){
    winPlat = create_newwin(25, 49, (LINES-25)/2, (COLS-49)/2);
    wbkgd(winPlat, COLOR_PAIR(1));
    for (int ligne = 2; ligne<23; ++ligne){
        wmove(winPlat, ligne, 4);
        if (ligne%5 == 2){
            int lignePlat = (ligne-2)/5;
            wprintw(winPlat, "%c  -----  %c  -----  %c  -----  %c  -----  %c",
                    affichage_char_pion(plat.plateau[0][lignePlat]),
                    affichage_char_pion(plat.plateau[1][lignePlat]),
                    affichage_char_pion(plat.plateau[2][lignePlat]),
                    affichage_char_pion(plat.plateau[3][lignePlat]),
                    affichage_char_pion(plat.plateau[4][lignePlat]));
        }else if (ligne%10 == 4){
            wprintw(winPlat, "|   \\\\    |    //   |   \\\\    |    //   |");
        }else if (ligne%10 == 5){
            wprintw(winPlat, "|    \\\\   |   //    |    \\\\   |   //    |");
        }else if (ligne%10 == 9){
            wprintw(winPlat, "|    //   |   \\\\    |    //   |   \\\\    |");
        }else if (ligne%10 == 0){
            wprintw(winPlat, "|   //    |    \\\\   |   //    |    \\\\   |");
        }
    }
    wnoutrefresh(winPlat);
    return winPlat;
}

WINDOW *affichage_init_FinTour (void){
    WINDOW *winFinTour = create_newwin(7, ((COLS/2)-33)/2, (LINES/2)+6, (COLS/2)+28);
    wbkgd(winFinTour, COLOR_PAIR(2));
    affichage_print_in_middle(winFinTour, 3, 0, ((COLS/2)-33)/2, "Fin de Tour", COLOR_PAIR(1));
    wnoutrefresh(winFinTour);
    return winFinTour;
}

WINDOW *affichage_init_Annuler (void){
    WINDOW *winAnnuler = create_newwin(7, ((COLS/2)-33)/2, (LINES/2)+6, +(3*COLS/4)+13);
    wbkgd(winAnnuler, COLOR_PAIR(3));
    affichage_print_in_middle(winAnnuler, 3, 0, ((COLS/2)-33)/2, "Annuler", COLOR_PAIR(2));
    wnoutrefresh(winAnnuler);
    return winAnnuler;
}

WINDOW *affichage_init_Chat (void){
    winChat = create_newwin((LINES/2)-15, COLS-92, (LINES/2)+14 , 47);
    wnoutrefresh(winChat);
    return winChat;
}

WINDOW *affichage_init_ChevreRestante (void){
    winRest = create_newwin(18, (COLS/2)-31, (LINES-25)/2, (COLS/2)+28);
    affichage_print_in_middle(winRest, 8, 0, (COLS/2)-31, "Il vous reste :", 0);
    affichage_print_in_middle(winRest, 9, 0, (COLS/2)-31, "20 chevres", 0);
    affichage_print_in_middle(winRest, 10, 0, (COLS/2)-31, "a placer", 0);
    wnoutrefresh(winRest);
    return winRest;
}

WINDOW *affichage_init_new (void){
    WINDOW *winNew = create_newwin(3, 15, 0, 0);
    wbkgd(winNew, COLOR_PAIR(1));
    affichage_print_in_middle(winNew, 1, 0, 14, "Nouveau Jeu",0);
    wnoutrefresh(winNew);
    return winNew;
}

WINDOW *affichage_init_save (void){
    WINDOW *winSave = create_newwin(3, 15, 0, 15);
    wbkgd(winSave, COLOR_PAIR(1));
    affichage_print_in_middle(winSave, 1, 0, 15, "Sauvegarder",0);
    wnoutrefresh(winSave);
    return winSave;
}

WINDOW *affichage_init_load (void){
    WINDOW *winLoad = create_newwin(3, 11, 0, 30);
    wbkgd(winLoad, COLOR_PAIR(1));
    affichage_print_in_middle(winLoad, 1, 0, 11, "Charger",0);
    wnoutrefresh(winLoad);
    return winLoad;
}

WINDOW *affichage_init_exit (void){
    WINDOW *winExit = create_newwin(3, 11, 0, COLS-11);
    wbkgd(winExit, COLOR_PAIR(2));
    affichage_print_in_middle(winExit, 1, 0, 11, "Quitter",0);
    wnoutrefresh(winExit);
    return winExit;
}

void affichage_init(void){
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    affichage_print_in_middle(NULL, 3, 0, COLS, "Bagh Chal", 0);
    affichage_init_case_capture();
    affichage_init_historique();
    affichage_init_plateau();
    affichage_init_Chat();
    affichage_message("Bonjour", 5);
    affichage_init_ChevreRestante();
    affichage_init_FinTour();
    affichage_init_Annuler();
    affichage_init_new();
    affichage_init_save();
    affichage_init_load();
    affichage_init_exit();
    doupdate();
}

void affichage_message (char* Message, int color){
    wclear(winChat);
    affichage_init_Chat();
    wmove(winChat, 1, 1);
    wattron(winChat, COLOR_PAIR(color));
    wprintw(winChat, Message);
    wattroff(winChat, COLOR_PAIR(color));
    wrefresh(winChat);
}

void affichage_maj_plateau_case (Pos p){
    wmove(winPlat, 2+5*p.y, 4+10*p.x);
    wprintw(winPlat, "%c", affichage_char_pion(plat.plateau[p.x][p.y]));
    wrefresh(winPlat);
}

void affichage_maj_plateau (void){
    for (int x = 0; x<5; ++x)
        for (int y = 0; y<5; ++y) {
            Pos p;
            p.x = x;
            p.y = y;
            affichage_maj_plateau_case(p);
        }
}

void affichage_maj_rest (void){
    char phrase[11];
    phrase[0] = '0' + plat.nbChevresHorsPlateau / 10;
    phrase[1] = '0' + plat.nbChevresHorsPlateau % 10;
    phrase[2] = '\0';
    strcat(phrase, " chevres");
    affichage_print_in_middle(winRest, 9, 0, (COLS/2)-31, phrase, 0);
}

void affichage_maj_capture (void){
    char phrase[2];
    phrase[0] = '0' + plat.nbChevreCapture;
    phrase[1] = '\0';
    affichage_print_in_middle(winCapture, 3, 0, 40, phrase, 0);
}

void affichage_maj_Hist_etape (Coup* c, int ligne){
    wmove(winHist, ligne+2, 1);
    if (c->placement_chevre)
        wprintw(winHist, "Chevre : placement en (%d,%d)", c->mvt.fin.x, c->mvt.fin.y);
    else
        wprintw(winHist, "%s : %s de (%d,%d) a (%d,%d)", c->tigre?"Tigre":"Chevre",c->chevre_mange?"mange":"deplacement", c->mvt.deb.x, c->mvt.deb.y, c->mvt.fin.x, c->mvt.fin.y);
}

void affichage_maj_Hist (Historique h){
    wclear(winHist);
    affichage_init_historique();
    historique_map(h, affichage_maj_Hist_etape);
    wrefresh(winHist);
}

void affichage_scrollup_hist (Historique* h){
    if(h->premierAffiche){
        --h->premierAffiche;
        affichage_maj_Hist (*h);
    }
}

void affichage_scrolldown_hist (Historique* h){
    if(h->nbCoups - h->premierAffiche == 23){
        ++h->premierAffiche;
        affichage_maj_Hist (*h);
    }
}

void affichage_boiteDialogue(int load, char* str){
    affichage_message(load?"Chargement":"Sauvegarde", 5);
    affichage_print_in_middle(winChat, 3, 0, 50, "Entrer le nom du fichier de sauvegarde : ", 0);
    wrefresh(winChat);
    wmove(winChat, 4, 4);
    wgetstr(winChat, str);
}




























