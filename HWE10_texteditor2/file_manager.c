#include <stdio.h>
#include <ncurses.h>
#include "file_manager.h"

int switch_windows(int active_window) {
    return active_window == 1 ? 2 : 1;
}

WINDOW* win1;
WINDOW* win2;
int active_window = 1;

void create_windows() {
    int height, width;
    getmaxyx(stdscr, height, width);

    int half_width = width / 2;
    win1 = newwin(height, half_width, 0, 0);
    win2 = newwin(height, half_width, 0, half_width);

    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    wrefresh(win1);
    wrefresh(win2);
}

void destroy_windows() {
    delwin(win1);
    delwin(win2);
}

void open_file(const char* filename, WINDOW *win) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        wclear(win);
        mvwprintw(win, 1, 1, "%s", "Ошибка открытия файла");
    } else {
        wclear(win);
        char buffer[1024];
        int line = 1;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            mvwprintw(win, line, 1, "%s", buffer);
            line++;
        }
        fclose(file);
    }
    wrefresh(win);
}

void save_file(const char* filename, WINDOW *win) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        wclear(win);
        mvwprintw(win, 1, 1, "%s", "Ошибка сохранения файла");
    } else {
        int maxy, maxx;
        getmaxyx(win, maxy, maxx);
        for (int y = 1; y < maxy; y++) {
            char buffer[maxx+1];
            mvwinnstr(win, y, 1, buffer, maxx);
            fprintf(file, "%s\n", buffer);
        }
        fclose(file);
    }
    wrefresh(win);
}

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    create_windows();

    int ch;
    char filename[256];
    while ((ch = getch()) != 'q') { 
        switch (ch) {
            case KEY_F(1):    
                active_window = switch_windows(active_window);
                break;
            case KEY_F(2):  
                mvprintw(LINES - 1, 0, "Введите имя файла: ");
                echo();
                getstr(filename);
                noecho();
                open_file(filename, active_window == 1 ? win1 : win2);
                break;
            case KEY_F(3):  
                mvprintw(LINES - 1, 0, "Введите имя файла для сохранения: ");
                echo();
                getstr(filename);
                noecho();
                save_file(filename, active_window == 1 ? win1 : win2);
                break;
        }
    }

    destroy_windows();
    endwin();
    return 0;
}
