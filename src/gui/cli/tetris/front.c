#include "front.h"

void print_overlay(void) {
  print_rectangle(0, BOARD_Y + 1, 0,
                  BOARD_X * 2 + 1);  // Большое поле слева игровое
  print_rectangle(0, BOARD_Y + 1, BOARD_X * 2 + 2,
                  BOARD_X * 2 + HUD_WIDTH + 3);  // Поле информации большое

  print_rectangle(1, 4, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);
  print_rectangle(5, 8, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);
  print_rectangle(9, 12, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);
  print_rectangle(13, 19, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);

  MVPRINTW(2, BOARD_X * 2 + 6, "LEVEL");
  MVPRINTW(6, BOARD_X * 2 + 6, "SCORE");
  MVPRINTW(10, BOARD_X * 2 + 5, "HIGHSCORE");
  MVPRINTW(14, BOARD_X * 2 + 5, "NEXT OBJ");

  MVPRINTW(BOARD_Y / 2, (BOARD_X * 2 - INTRO_MESSAGE_LEN) / 2 + 1,
           INTRO_MESSAGE);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);   // левый верхний угол
  MVADDCH(top_y, right_x, ACS_URCORNER);  // правый верхний угол
  MVADDCH(bottom_y, left_x, ACS_LLCORNER);  // нижний левый угол
  MVADDCH(bottom_y, right_x, ACS_LRCORNER);  // нижний правый угол

  for (int i = left_x + 1; i < right_x; i++) {
    MVADDCH(top_y, i, ACS_HLINE);     // верхняя сторона
    MVADDCH(bottom_y, i, ACS_HLINE);  // нижняя сторона
  }

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);   // левая сторона
    MVADDCH(i, right_x, ACS_VLINE);  // правая сторона
  }
}

void draw_block(int y, int x, int color_pair) {
  attron(COLOR_PAIR(color_pair));
  mvprintw(y, x, " ");
  attroff(COLOR_PAIR(color_pair));
}

void field_print(int field[BOARD_X * 2][BOARD_Y]) {
  for (int i = 0; i < BOARD_X * 2 - 1; ++i) {
    for (int j = 0; j < BOARD_Y; ++j) {
      if (field[i][j] == 0) {
        mvprintw(j + 3, i + 3, "  ");
      } else {
        draw_block(j + 3, i + 3, field[i][j]);
      }
    }
  }
}

void block_print(int block_pos[8][2], int block_color) {
  for (int i = 0; i < 8; i++) {
    draw_block(block_pos[i][1] + 3, block_pos[i][0] + 3, block_color);
  }
}

void next_block_print(int block_pos[8][2], int block_color) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      draw_block(i + 17, j + 26, 0);
    }
  }
  for (int i = 0; i < 8; i++) {
    if (block_color == 1) {
      draw_block(block_pos[i][1] + 17, block_pos[i][0] + 22, block_color);
    } else if (block_color == 4) {
      draw_block(block_pos[i][1] + 18, block_pos[i][0] + 21, block_color);
    } else {
      draw_block(block_pos[i][1] + 18, block_pos[i][0] + 20, block_color);
    }
  }
}

void print_stats(int level, int score, int high_score) {
  mvprintw(5, BOARD_X * 2 + 9, "    ");
  mvprintw(9, BOARD_X * 2 + 9, "    ");
  mvprintw(13, BOARD_X * 2 + 9, "    ");
  mvprintw(5, BOARD_X * 2 + 9, "%d", level);
  mvprintw(9, BOARD_X * 2 + 9, "%d", score);
  mvprintw(13, BOARD_X * 2 + 9, "%d", high_score);
}
