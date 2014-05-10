#include <stdio.h>
#include <string.h>
#include "plateau.h"

extern Plateau plat;

void save_export (char* nomSave){
    FILE* fic;
    char destination[100] = "save/";
    strcat(destination, nomSave);
    fic = fopen(destination, "w");
    fprintf(fic, "\\board\n");
    for (int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            fprintf(fic, plat.plateau[i][j]);
        }
        fprintf(fic, "\n");
    }
    fprintf(fic, "\\endboard\n\\player %c\n", (plat.tourJoueur)?'T':'G');
    fprintf(fic, "\\phase %d\n", plat.phaseJeu);
    fprintf(fic, "\\captured %d", plat.nbChevreCapture);
    fclose(fic);
}

void save_import (char* nomSave){
    FILE* fic;
    int ligne=0;
    char destination[100] = "save/";
    char ligne[12];
    strcat(destination, nomSave);
    fic = fopen(destination, "r");
    while (fgets(ligne, sizeof(ligne), fic)){
        if (ligne > 0 && ligne <6)
            for (int i=0; i<5; ++i){
                plat.plateau[ligne-1][i] = ligne[i];
            }
        else if (ligne == 7)
            plat.tourJoueur = (ligne[8]=='T')?1:0;
        else if (ligne == 8)
            plat.phaseJeu = atoi(ligne[7]);
        else if (ligne == 9)
            plat.nbChevreCapture = atoi(ligne[10]);
        ++ligne;
    }
}