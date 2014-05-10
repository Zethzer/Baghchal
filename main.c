#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

Plateau plat;

void init(char* nomJoueurC, char* nomJoueurT);{
    if(affichage_menu())
        affichage_initJoueurs(nomJoueurC, nomJoueurT);
    else
        affichage_initJoueur();
    affichage_initPlateau();
    plateau_init();
	plateau_gestion();
}
                             
int main(void){
    char nomJoueurC[25];
    char nomJoueurT[25];
	init();
    
	return 0;
}

