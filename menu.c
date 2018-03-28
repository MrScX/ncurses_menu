#include <ncurses.h>
#include <stdlib.h>

void menuOptions();
void keyb_menu(int item,int keyb_run,char *str[]);
void displayLoadAndExit();
void about();

int choice,loop_1,row,col;

char *menu[3]= {
    "Home",
    "FAQ",
    "Help"
};

int main(){

	initscr();
	cbreak();
	getmaxyx(stdscr,row,col);

	menuOptions();
	getch();
	endwin();

	return 0;
}

void menuOptions(){

	int key,menuitem= 0,keyb_run= 3;
	napms(2000);
	clear();
	start_color();
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(1,COLOR_GREEN,COLOR_BLACK);

	bkgd(COLOR_PAIR(1));
	printw("--------------------------------------------------------------------------------\n");
	mvprintw(1,25,"Welcome to Ncurses!\n");
	printw("--------------------------------------------------------------------------------\n");
	mvprintw(20,25,"{Use arrow keys to navigate and enter to select}");
	attron(A_BOLD);
	mvprintw(row-1,0,"F1 - Exit");
	mvprintw(row-1,col-12,"F8 - About");
	attroff(A_BOLD);
	refresh();
	keyb_menu(menuitem,keyb_run,menu);
	noecho();
	keypad(stdscr,TRUE);

	do{

	key= getch();

	switch(key){

	    case KEY_DOWN:
			menuitem++;

			if(menuitem>2)
				menuitem=0;
				break;

		case KEY_UP:
			menuitem--;
			if(menuitem < 0) menuitem= 2;
			break;

	    case KEY_F(1):
			displayLoadAndExit();
			napms(1000);
			endwin();
			exit(1);

		    break;

		case KEY_F(8):
			displayLoadAndExit();
			clear();
			about();
		    break;

		case '\n':
		    break;

	    default:
		    mvprintw(15,25,"Wrong key pressed! Please enter choice again.\n");
		    refresh();
		    menuOptions();
	    }

	    keyb_menu(menuitem,keyb_run,menu);

	}while(key!='\n');

	echo();
}

void displayLoadAndExit(){

	attron(COLOR_PAIR(2)|A_BOLD);
	mvaddstr(16,25,"Loading");

	for(loop_1=0;loop_1<7;loop_1++){
		addch('.');
		napms(100);
		refresh();
	}

	attroff(COLOR_PAIR(2)|A_BOLD);
}

void keyb_menu(int item,int keyb_run,char *str[]){

	int c;

	for(c=0;c<keyb_run;c++){

		if(c==item)
			attron(A_REVERSE | A_BOLD);

		mvaddstr(7+(c*2),30,str[c]);
		attroff(A_REVERSE | A_BOLD);
	}

	move(0,0);

	refresh();
}

void about(){
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	printw("---------------------------------------------------------------------------\n");
	mvprintw(1,25,"About Ncurses\n");
	printw("---------------------------------------------------------------------------\n");
	attron(COLOR_PAIR(4)|A_BOLD);
	mvprintw(6,3,"ncurses (new curses) is a programming library providing an application\nprogramming interface (API) that allows the programmer to write text-based user interfaces\nin a terminal-independent manner. It is a toolkit for developing 'GUI-like'\napplication software that runs under a terminal emulator. It also optimizes screen changes, in order to reduce the latency experienced when using remote shells.\n");
	attroff(COLOR_PAIR(4)|A_BOLD);
	mvprintw(22,25,"{Press Enter to go back to previous menu.}\n");
	refresh();
	getch();
	menuOptions();
}
