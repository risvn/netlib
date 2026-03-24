#include <ncurses.h>

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}

int main()
{

    initscr();
    cbreak();
    noecho();

    

    WINDOW *menu= newwin(10, 30, 5, 10);
    box(menu, 0, 0);                 // 1. draw border first
    refresh();
    wrefresh(menu);                  // 3. refresh window
    keypad(menu, TRUE);

    char* options[4] ={"file1","file2","file3","file"};
    int n_options=LEN(options);

    int choice;
    int highlight=0;

    while(1){
    for(int i=0;i<n_options;++i){
      if(i==highlight)
             wattron(menu,A_REVERSE);
      mvwprintw(menu,i+1,1, options[i]);
      wattroff(menu,A_REVERSE);
      }
    choice = wgetch(menu);

    switch(choice){
      case KEY_UP:
        highlight--;
        break;

      case KEY_DOWN:
        highlight++;
        break;

      default:
        break;
    }
    

    
    if(highlight < 0)
        highlight = n_options - 1;

    if(highlight >= n_options)
        highlight = 0;

    if(choice==10)
      break;



  }
    
    getch();
    endwin();

    return 0;
}
