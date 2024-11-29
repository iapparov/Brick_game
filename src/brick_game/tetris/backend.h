#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../defines.h"

/**
 * @brief Structure that keeps common information about game.
 * @struct GameInfo_t
 */
typedef struct {
  int field[BOARD_X * 2][BOARD_Y];
  int next_block_pos[8][2];
  int score;
  int high_score;
  int level;
  int current_block_pos[8][2];
  int current_block_type;
  int next_block_type;
  int current_rotate;
  int state;
} GameInfo_t;

/**
 * @brief All type of blocks.
 * @enum Block
 */
typedef enum {
  i_block_color = 1,
  j_block_color,
  l_block_color,
  o_block_color,
  s_block_color,
  t_block_color,
  z_block_color
} Block;

/**
 * @brief Function for blocks initialization
 * @param figure_number: parameter from 1 to 7 from BLOCK enum
 * @param current_block_pos: parameter from struct GameInfo_t with current block
 * coordinates
 */
void block_init(int figure_number, int current_block_pos[8][2]);

/**
 * @brief Function for stats and field initialization like score, highscore,
 * field, and level
 */
void stats_init(void);

/**
 * @brief Subfunction for block_init that initialize blocks
 */
void block_init_case(int current_block_pos[8][2], int block_f[8][2]);

/**
 * @brief Functions for rotating blocks
 * @param current_block_pos: parameter from struct GameInfo_t with current block
 * coordinates
 * @param current_rotate: pointer for current rotate block (0-3)
 * @param field: parameter that includes field information
 */
void i_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);
void j_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);
void l_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);
void s_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);
void t_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);
void z_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]);

/**
 * @brief Functions for updating stats during the
 * @param check: parameter contains info about how many lines were deleted
 * @param score: pointer for score
 * @param field: pointer for level
 * @param high_score: pointer for high_score
 */
void game_stats(int check, int *score, int *level, int *high_score);

/**
 * @brief Functions update field when one or more lines are filled
 * @param field: parameter for current field
 * @return score from 1 to 4, if score == -1 the game is over
 */
int attaching(int field[BOARD_X * 2][BOARD_Y]);

/**
 * @brief Function preventing going out field (X-coordinates) during rotation
 * @param current_block_pos: parameter from struct GameInfo_t with current block
 * coordinates
 */
void side_rotate_check(int current_block_pos[8][2]);

/**
 * @brief Function preventing going out field (Y-coordinates) during rotation
 * @param current_block_pos: parameter from struct GameInfo_t with current block
 * coordinates
 */
void side_rotate_check_Y(int current_block_pos[8][2]);

/**
 * @brief Function updates actual high score and saves it in a file
 * @param curret_score: parameter for current score
 */
int update_highscore(int current_score);

/**
 * @brief Function for speed of game, finds elapsed time
 * @param start_time: parameter for current time
 * @param elapsed_time: parameter for elapsed time
 * @return if ellapsed time more than we need it return 1 and block move down
 */
int timer(clock_t *start_time, double elapsed_time);

/**
 * @brief update Current State.
 *
 * Initialises GameInfo_t as static variable inside.
 *
 * @return GameInfo_t*
 */
GameInfo_t *updateCurrentState(void);

/**
 * @brief Function checking free lines in the field for block spawning
 * @param field: parameter for current field
 * @param block: parameter for spawning block
 * @return if there are enough free lines it returns 1 and block will be spawned
 */
int check_spawn(int field[BOARD_X * 2][BOARD_Y], int block[8][2]);

#endif
