#ifndef DEFINES_H
#define DEFINES_H

#include <locale.h>
#include <ncurses.h>

#define WIN_INIT(time)                        \
  {                                           \
    initscr();                                \
    start_color();                            \
    noecho();                                 \
    curs_set(0);                              \
    keypad(stdscr, TRUE);                     \
    timeout(time);                            \
    init_pair(1, COLOR_RED, COLOR_RED);       \
    init_pair(2, COLOR_BLACK, COLOR_GREEN);   \
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);  \
    init_pair(4, COLOR_BLACK, COLOR_BLUE);    \
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA); \
    init_pair(6, COLOR_BLACK, COLOR_CYAN);    \
    init_pair(7, COLOR_BLACK, COLOR_WHITE);   \
    init_pair(0, COLOR_BLACK, COLOR_BLACK);   \
  }

#define SUCCESS 0

#define BOARD_X 10
#define BOARD_Y 20
#define HUD_WIDTH 12  // ширина окошка информации

#define INTRO_MESSAGE "Press ENTER to start"
#define INTRO_MESSAGE_LEN 20
#define GM_MESSAGE "GAME OVER!"
#define GM_MESSAGE_LEN 10
#define BOARDS_BEGIN 2

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')
#define GET_USER_INPUT getch()

#define ESCAPE 27
#define ENTER_KEY 10
#define SPACE_KEY 32

#endif
