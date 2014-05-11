#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"
#include "save.h"
#include "plateau.h"

extern Plateau plat;

void save_export (char* nomSave){
    FILE* fic;
    char destination[100] = "save/";
    char phrase [strlen(nomSave) + 32];
    strcat(destination, nomSave);
    fic = fopen(destination, "w");
    fprintf(fic, "\\board\n");
    for (int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            fputc(plat.plateau[i][j].pion, fic);
        }
        fprintf(fic, "\n");
    }
    fprintf(fic, "\\endboard\n\\player %c\n", (plat.tourJoueur)?'T':'G');
    fprintf(fic, "\\phase %d\n", plat.phaseJeu);
    fprintf(fic, "\\captured %d\n", plat.nbChevreCapture);
    fprintf(fic, "\\restante %d\n", plat.nbChevreHorsPlateau);
    fprintf(fic, "\\coupJoue %d", plat.coupJoue);
    fclose(fic);
    strcpy(phrase, "Partie Sauvegardee en tant que ");
    strcat(phrase, nomSave);
    affichage_message(phrase, 5);
}

void save_import (char* nomSave){
    FILE* fic;
    int lig=0;
    char destination[100] = "save/";
    char phrase[strlen(nomSave)+30];
    char ligne[12];
    strcat(destination, nomSave);
    fic = fopen(destination, "r");
    while (fgets(ligne, sizeof(ligne), fic)){
        if (lig > 0 && lig <6)
            for (int i=0; i<5; ++i){
                plat.plateau[lig-1][i].pion = ligne[i];
            }
        else if (lig == 7)
            plat.tourJoueur = (ligne[8]=='T')?1:0;
        else if (lig == 8){
            plat.phaseJeu = atoi(ligne+7);
        }
        else if (lig == 9){
            plat.nbChevreCapture = atoi(ligne+10);
        }
        else if (lig == 10){
            plat.nbChevreHorsPlateau = atoi(ligne+10);
        }
        else if (lig == 11){
            plat.coupJoue = atoi(ligne+10);
        }
        ++lig;
    }
    strcpy(phrase, "Partie Chargee depuis ");
    strcat(phrase, nomSave);
    affichage_message(phrase, 5);
}