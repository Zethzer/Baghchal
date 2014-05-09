#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <form.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color){
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

int main(void){

	FIELD *field[25];
	FORM *form;
	WINDOW *win;
	int rows, cols;

	int startx = 200;
	int starty = 70;
	int i=0;
	
	initscr();

	for(int a=0;a < 5;++a){
		for(int b=0;b < 5;++b){
			field[i]=new_field(80,80,startx,starty,0,0);
			startx += 80;
			++i;
		}
		startx = 200;
		starty += 80;
		++i;
	}

	for(int j=0;j < 25;++j){
		set_field_back(field[j], A_UNDERLINE);
		field_opts_off(field[j], O_AUTOSKIP);
	}

	form=new_form(field);
	scale_form(form,&rows,&cols);

	win=newwin(rows+4,cols+4,4,4);

	/* Set main window and sub window */
    set_form_win(form, win);
    set_form_sub(form, derwin(win, rows, cols, 2, 2));	

    /* Titre */
    box(win, 0, 0);
	print_in_middle(win, 1, 0, cols + 4, "My Form", COLOR_PAIR(1));
	
	/* Refresh all */
	post_form(form);
	wrefresh(win);

	/* Libération mémoire */
	unpost_form(form);
	free_form(form);
	for(int j=0;j < 25;++j)
		free_field(field[i]);
	endwin();

	return 0;
}

