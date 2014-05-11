#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "plateau.h"
#include "affichage.h"

Plateau plat;

extern WINDOW *winHist;

/*void init(char* nomJoueurC, char* nomJoueurT){
    if(affichage_menu())
        affichage_initJoueurs(nomJoueurC, nomJoueurT);
    else
        affichage_initJoueur();
    affichage_initPlateau();
    plateau_init();
	plateau_gestion();
}*/
                             
int main(void){
    int ch;
    Pos p;
    p.x =2;
    p.y =3;
    
    //initialisation plateau
    plateau_init();
    
    //initialisation Ncurses
    initscr();
    keypad(stdscr, TRUE);
    
    //initialisation affichage
    affichage_init();
    
    //modification Plateau
    plateau_ajouterChevre(p);
    affichage_maj_plateau_case(p);
    
    //Modif Historique
    for (int i=0; i<22; ++i)
        affichage_maj_Hist_etape (NULL, i);
    wrefresh(winHist);
    
    //attente
    while((ch = getch()) != KEY_F(1)){
        
    }
    
    endwin();
}

