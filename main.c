#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "plateau.h"
#include "affichage.h"
#include "save.h"
#include "rechercheVainqueur.h"

Plateau plat;

extern WINDOW* winHist;

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
    Historique h;
    Pos p = gestionPions_initPos (2, 3);
    Mvt m = gestionPions_initMvt (1, 1, 0, 0);
    
    Coup* c = historique_init_coup (m, 1, 0, 0 ,0);
    
    affichage_init();
    historique_init(&h);
    plateau_init();
    keypad(stdscr, TRUE);
    
    //Modif plateau
    plateau_ajouterChevre(p);
    affichage_maj_plateau_case(p);
    
    //Modif Historique
    
    for (int i=0; i<22; ++i)
        historique_ajouter_coup (&h, c);
    affichage_maj_Hist(h);
    
    //Attente
    while((ch = getch()) != KEY_F(3)){
        
    }
    endwin();
    return 0;
}

