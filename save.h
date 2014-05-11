#ifndef __SAVE_H__
#define __SAVE_H__

/*
 E : une chaine de caractère
 S : aucune
 Role : écrit dans un fichier nommé nomSave situé dans le dossier /save les informations sur l'état de la partie. 
 */
void save_export (char* nomSave);

/*
 E : une chaine de caractère
 S : aucune
 Role : charge les informations propres à la partie depuis un fichier nommé nomSave situé dans le dossier /save
 */
void save_import (char* nomSave);

#endif
