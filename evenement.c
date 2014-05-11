#include "evenement.h"
#include "affichage.h"

#include <stdbool.h>
#include <ncurses.h>

int evenement_recupererEvenement(Historique h, Pos* pEvent){
	int c;
	MEVENT event;

	keypad(stdscr, true);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	c=(int) getch();
	switch(c){
		case KEY_MOUSE:
			if(getmouse(&event) == OK){
				if(event.bstate & BUTTON1_PRESSED){
					pEvent->x=event.x;
					pEvent->y=event.y;
				}
				return(1);
			}
		break;
		case KEY_UP:
			affichage_scrolldown_hist(h);
			return(0);
		break;
		case KEY_DOWN:
			affichage_scrollup_hist(h);
			return(0);
		break;
	}
}

