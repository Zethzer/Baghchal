#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "plateau.h"
#include "affichage.h"
#include "save.h"
#include "rechercheVainqueur.h"

Plateau plat;

extern WINDOW* winHist;

void init(){
    plateau_init();
    affichage_init();
    historique_init(h);
    keypad(stdscr, TRUE);
}
                             
int main(void){
    int ch, fini = 0;
    Historique h;
    char str[20];
    Pos p = gestionPions_initPos (2, 3);
    Mvt m = gestionPions_initMvt (1, 1, 0, 0);
    Coup* c;

    init(&h);
    
    while (!fini){
        
    }
    
    
    endwin();
    return 0;
}

