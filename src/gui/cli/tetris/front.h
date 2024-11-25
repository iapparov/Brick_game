#ifndef FRONT_H
#define FRONT_H

#include "../../../brick_game/defines.h"

void print_start(void);
void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void draw_block(int y, int x, int color_pair);
void field_print(int field[BOARD_X * 2][BOARD_Y]);
void block_print(int block_pos[8][2], int block_color);
void next_block_print(int block_pos[8][2], int block_color);
void print_stats(int level, int score, int high_score);

#endif
