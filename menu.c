#include <ncurses.h>
#include <stdlib.h>

void menuOptions();
void keyb_menu(int item,int keyb_run,char *str[]);
void displayLoadAndExit();

int choice,timer=2,loop_1,row,col;

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

		    break;

		case KEY_F(8):
			displayLoadAndExit();
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
		  
	napms(1000);
	endwin();
	exit(1);
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

