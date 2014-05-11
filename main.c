#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "plateau.h"
#include "affichage.h"
#include "save.h"
#include "rechercheVainqueur.h"

Plateau plat;

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
    int ch;// codeVainqueur, codeTour;
    Historique h;
    // MEVENT event;
    // Pos p;
    // p.x =2;
    // p.y =3;
    
    //initialisation plateau
    plateau_init();
    
    //initialisation Ncurses
    initscr();
    keypad(stdscr, TRUE);
    
    //initialisation affichage
    affichage_init();
    
    /*modification Plateau
    plateau_ajouterChevre(p);
    affichage_maj_plateau_case(p);*/

    historique_init(&h);

    /*while((codeVainqueur=rechercheVainqueur_vainqueurPresent()) == 0){
        if((codeTour=plateau_gestionTour(h)) == 0)
            ;
        else if (codeTour == 1){
            plateau_init();
            historique_init(h);
            affichage_init();
        }
        else if (codeTour == 2)
            ;
            //save_import(affichage_boiteDialogue(1));
    }*/
    
    //attente
    while((ch = getch()) != KEY_F(3)){
        
    }
    endwin();
    return 0;
}

