#include "evenement.h"

#include <stdbool.h>
#include <ncurses.h>

Pos evenement_recupererEvenementSouris(){
	Pos p;
	int c;
	MEVENT event;

	keypad(stdscr, true);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	c=(int) getch();
	switch(c){
		case KEY_MOUSE:
			if(getmouse(&event) == OK){
				if(event.bstate & BUTTON1_PRESSED){
					p.x=event.x;
					p.y=event.y;
				}
			}
		break;
	}

	return(p);
}

