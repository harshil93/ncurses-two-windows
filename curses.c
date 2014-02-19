#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();		
	raw();				 
	noecho();
	keypad(stdscr, TRUE);		
	height = LINES-5;
	width = COLS;
	starty = 0;	
	startx = 0;
	refresh();
	my_win = create_newwin(height, width, starty, startx);
	move(LINES-1,0);
	int cur_cols = 0;

	int my_win_buffer_len = 0;
	char my_win_buffer_line[1000];
	int cur_rows = 0;
	while((ch = getch()) != KEY_F(1))
	{	

		switch(ch){
			case '\n':
				move(LINES-1,0);
				cur_cols = 0;
				int i;
				for (i = 0; i < COLS; ++i)
				{
					addch(' ');
				}
				cur_rows++;
				if(cur_rows == LINES-3){
					werase(my_win);
					wrefresh(my_win);
					cur_rows = 0;
				}
				my_win_buffer_line[my_win_buffer_len++]='\n';
				my_win_buffer_line[my_win_buffer_len++]='\0';
				wprintw(my_win,my_win_buffer_line);
				wrefresh(my_win);
				my_win_buffer_len = 0;
				break;
			case KEY_BACKSPACE:
				cur_cols--;
				move(LINES-1,cur_cols);
				addch(' ');
				move(LINES-1,cur_cols);
				my_win_buffer_len--;
				break;
			case KEY_F(4):
				erase();
				werase(my_win);
				delwin(my_win);
				goto end;
				break;
			default:
				move(LINES-1,cur_cols);
				my_win_buffer_line[my_win_buffer_len++] = ch;
				addch(ch);
				cur_cols++;
		}
				
	}
	end:
	endwin();			/* End curses mode		  */
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);		/* Show that box 		*/
	return local_win;
}

