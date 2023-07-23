#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <ncurses.h>

int switch_windows(int active_window);
void create_windows();
void destroy_windows();
void open_file(const char* filename, WINDOW *win);
void save_file(const char* filename, WINDOW *win);

#endif 
