// #include <ncurses.h>
// #include <stdlib.h>
// #include <string.h>
// #define CTRL_KEY(k) ((k) & 0x1f)
//
//
//
// int main(int argc, char* argv[]) {
//     initscr();
//     start_color();
//     cbreak();
//     noecho();
//     keypad(stdscr, TRUE);
//     curs_set(0);
//
//     init_pair(1, COLOR_WHITE, COLOR_BLUE);
//     active_window = 1;
//
//     create_windows();
//
//     int ch;
//     bool quit = false;
//     char filename[256] = {0};
//     while (!quit) {
//         ch = getch();
//         switch (ch) {
//             case CTRL_KEY('q'):   
//                 quit = true;
//                 break;
//             case CTRL_F(1):    
//                 switch_windows();
//                 break;
//             case CTRL_F(2):   
//                 mvmprintw(LINES -1, 0, "Введите имя файла: ");
//                 echo();
//                 getstr(filename);
//                 noecho();
//                 open_file(filename, active_window == 1 ? win1 : win2);
//                 break;
//             case KEY_F(3):  
//                 mvmprintw(LINES -1, 0, "Введите имя файла для сохранения: ");
//                 echo();
//                 getstr(filename);
//                 noecho();
//                 save_file(filename, active_window == 1 ? win1 : win2);
//                 break;
//         }
//     }
//
//     destroy_windows();
//     endwin();
//
//     return 0;
// }
