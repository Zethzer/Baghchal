#include "evenement.h"

#include <ncurses.h>

Pos evenement_recupererEvenementSouris(){
	Pos p;
	char c;
	MEVENT event;

	mousemask(BUTTON1_PRESSED | BUTTON1_RELEASED, NULL);

	c=getch();
	switch(c){
		case KEY_MOUSE:
			if(get_mouse(&event) == OK){
				if(event.bstate && BUTTON1_PRESSED){
					p.x=event.x;
					p.y=event.y;
				}
			}
	}

	return(p);
}

