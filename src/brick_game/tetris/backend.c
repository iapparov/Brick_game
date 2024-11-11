#include "backend.h"

#include "../defines.h"

void block_init(int figure_number, int current_block_pos[8][2]) {
  int i_block_f[8][2] = {{8, 0}, {8, 1}, {8, 2}, {8, 3},
                         {9, 0}, {9, 1}, {9, 2}, {9, 3}};
  int j_block_f[8][2] = {{8, 0}, {9, 0}, {10, 0}, {11, 0},
                         {8, 1}, {9, 1}, {8, 2},  {9, 2}};
  int l_block_f[8][2] = {{8, 0},  {9, 0},  {10, 0}, {11, 0},
                         {10, 1}, {11, 1}, {10, 2}, {11, 2}};
  int o_block_f[8][2] = {{8, 0}, {9, 0}, {10, 0}, {11, 0},
                         {8, 1}, {9, 1}, {10, 1}, {11, 1}};
  int s_block_f[8][2] = {{8, 1},  {9, 1},  {10, 1}, {11, 1},
                         {10, 0}, {11, 0}, {12, 0}, {13, 0}};
  int t_block_f[8][2] = {{8, 0},  {9, 0},  {10, 0}, {11, 0},
                         {12, 0}, {13, 0}, {10, 1}, {11, 1}};
  int z_block_f[8][2] = {{8, 0},  {9, 0},  {10, 0}, {11, 0},
                         {10, 1}, {11, 1}, {12, 1}, {13, 1}};
  switch (figure_number) {
    case 1:
      block_init_case(current_block_pos, i_block_f);
      break;
    case 2:
      block_init_case(current_block_pos, j_block_f);
      break;
    case 3:
      block_init_case(current_block_pos, l_block_f);
      break;
    case 4:
      block_init_case(current_block_pos, o_block_f);
      break;
    case 5:
      block_init_case(current_block_pos, s_block_f);
      break;
    case 6:
      block_init_case(current_block_pos, t_block_f);
      break;
    case 7:
      block_init_case(current_block_pos, z_block_f);
      break;
  }
}

void block_init_case(int current_block_pos[8][2], int block_f[8][2]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      current_block_pos[i][j] = block_f[i][j];
    }
  }
}

void stats_init(void) {
  GameInfo_t *stats = updateCurrentState();
  stats->score = 0;
  stats->level = 1;
  stats->high_score = update_highscore(stats->score);
  for (int i = 0; i < BOARD_X * 2; i++) {
    for (int j = 0; j < BOARD_Y; j++) {
      stats->field[i][j] = 0;
    }
  }
  stats->next_block_type = rand() % 7 + 1;
  stats->state = 0;
}

void i_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[8] = {-2, -1, 0, 1, 1, 2, 3, 4};
  int y_offsets[8] = {2, 1, 0, -1, 2, 1, 0, -1};

  int sign = (*current_rotate == 0) ? 1 : -1;

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + (sign * x_offsets[i])]
             [current_block_pos[i][1] + (sign * y_offsets[i])] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; ++i) {
      current_block_pos[i][0] += sign * x_offsets[i];
      current_block_pos[i][1] += sign * y_offsets[i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = 1 - *current_rotate;
  }
}

void j_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[4][8] = {{0, 0, 0, 0, 4, 4, 4, 4},
                         {2, 2, 0, 0, -2, -2, -4, -4},
                         {-2, -2, 0, 0, 2, 2, 0, 0},
                         {0, 0, 0, 0, -4, -4, 0, 0}};

  int y_offsets[4][8] = {{1, 1, 1, 1, 0, 0, 0, 0},
                         {-1, -1, 0, 0, 1, 1, 0, 0},
                         {1, 1, 0, 0, -1, -1, -2, -2},
                         {-1, -1, -1, -1, 0, 0, 2, 2}};

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + x_offsets[*current_rotate][i]]
             [current_block_pos[i][1] + y_offsets[*current_rotate][i]] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; ++i) {
      current_block_pos[i][0] += x_offsets[*current_rotate][i];
      current_block_pos[i][1] += y_offsets[*current_rotate][i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = (*current_rotate + 1) % 4;
  }
}

void l_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[4][8] = {{0, 0, 0, 0, 2, 2, 2, 2},
                         {0, 0, -2, -2, -4, -4, -2, -2},
                         {0, 0, 2, 2, 4, 4, -2, -2},
                         {0, 0, 0, 0, -2, -2, 2, 2}};

  int y_offsets[4][8] = {{2, 2, 2, 2, 1, 1, -1, -1},
                         {-2, -2, -1, -1, 0, 0, 1, 1},
                         {0, 0, -1, -1, -2, -2, -1, -1},
                         {0, 0, 0, 0, 1, 1, 1, 1}};

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + x_offsets[*current_rotate][i]]
             [current_block_pos[i][1] + y_offsets[*current_rotate][i]] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; ++i) {
      current_block_pos[i][0] += x_offsets[*current_rotate][i];
      current_block_pos[i][1] += y_offsets[*current_rotate][i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = (*current_rotate + 1) % 4;
  }
}

void s_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[8] = {0, 0, -2, -2, 0, 0, -2, -2};
  int y_offsets[8] = {-1, -1, 0, 0, 1, 1, 2, 2};

  int sign = (*current_rotate == 0) ? 1 : -1;

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + (sign * x_offsets[i])]
             [current_block_pos[i][1] + (sign * y_offsets[i])] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][0] += sign * x_offsets[i];
      current_block_pos[i][1] += sign * y_offsets[i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = 1 - *current_rotate;
  }
}

void z_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[8] = {0, 0, 0, 0, 0, 0, -4, -4};
  int y_offsets[8] = {1, 1, 1, 1, -1, -1, 1, 1};

  int sign = (*current_rotate == 0) ? 1 : -1;

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + (sign * x_offsets[i])]
             [current_block_pos[i][1] + (sign * y_offsets[i])] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][0] += sign * x_offsets[i];
      current_block_pos[i][1] += sign * y_offsets[i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = 1 - *current_rotate;
  }
}

void t_block_rotate(int current_block_pos[8][2], int *current_rotate,
                    int field[BOARD_X * 2][BOARD_Y]) {
  int x_offsets[4][8] = {
      {2, 2, 0, 0, -2, -2, -2, -2},
      {-2, -2, 0, 0, 2, 2, 2, 2},
      {2, 2, 0, 0, -2, -2, 2, 2},
      {-2, -2, 0, 0, 2, 2, -2, -2},
  };

  int y_offsets[4][8] = {{-1, -1, 0, 0, 1, 1, -1, -1},
                         {1, 1, 0, 0, -1, -1, -1, -1},
                         {-1, -1, 0, 0, 1, 1, 1, 1},
                         {1, 1, 0, 0, -1, -1, 1, 1}};

  int check_field = 1;
  for (int i = 0; i < 8; i++) {
    if (field[current_block_pos[i][0] + x_offsets[*current_rotate][i]]
             [current_block_pos[i][1] + y_offsets[*current_rotate][i]] != 0) {
      check_field = 0;
    }
  }
  if (check_field) {
    for (int i = 0; i < 8; ++i) {
      current_block_pos[i][0] += x_offsets[*current_rotate][i];
      current_block_pos[i][1] += y_offsets[*current_rotate][i];
    }
    side_rotate_check(current_block_pos);
    side_rotate_check_Y(current_block_pos);
    *current_rotate = (*current_rotate + 1) % 4;
  }
}

void game_stats(int check, int *score, int *level, int *high_score) {
  switch (check) {
    case 1: {
      *score = *score + 100;
    } break;
    case 2:
      *score = *score + 300;
      break;
    case 3:
      *score = *score + 700;
      break;
    case 4:
      *score = *score + 1500;
      break;
    default:
      break;
  }
  *level = *score / 600 + 1;
  *high_score = update_highscore(*score);
}

int attaching(int field[BOARD_X * 2][BOARD_Y]) {
  int score = 0;
  for (int j = 0; j < BOARD_Y; ++j) {
    int filled = 1;
    for (int i = 0; i < BOARD_X * 2; ++i) {
      if (field[i][j] == 0) {
        filled = 0;
        break;
      }
    }

    if (filled) {
      score++;
      for (int col = j; col > 0; --col) {
        for (int row = 0; row < BOARD_X * 2; ++row) {
          field[row][col] = field[row][col - 1];
        }
      }

      for (int row = 0; row < BOARD_X * 2; ++row) {
        field[row][0] = 0;
      }
    }
  }
  int filled, unfilled = 0;
  for (int i = 0; i < BOARD_X * 2; i++) {
    if (field[i][0] == 0) {
      filled = 1;
    }
    if (field[i][0] != 0) {
      unfilled = 1;
    }
  }
  if (filled && unfilled) {
    score = -1;
  }
  return score;
}

int check_spawn(int field[BOARD_X * 2][BOARD_Y], int block[8][2]) {
  int check = 1;
  for (int i = 0; i < 8; i++) {
    if (field[block[i][0]][block[i][1]] != 0) check = 0;
  }
  return check;
}

void side_rotate_check(int current_block_pos[8][2]) {
  int check = 0;
  for (int i = 0; i < 8; i++) {
    if (current_block_pos[i][0] > 19 && current_block_pos[i][0] > check) {
      check = current_block_pos[i][0];
    }
  }
  if (check > 0) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][0] -= check - 19;
    }
  }

  check = 20;
  for (int i = 0; i < 8; i++) {
    if (current_block_pos[i][0] < 0 && current_block_pos[i][0] < check) {
      check = current_block_pos[i][0];
    }
  }
  if (check < 20) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][0] += -check;
    }
  }
}

void side_rotate_check_Y(int current_block_pos[8][2]) {
  int check = 0;
  for (int i = 0; i < 8; i++) {
    if (current_block_pos[i][1] > 19 && current_block_pos[i][1] > check) {
      check = current_block_pos[i][1];
    }
  }
  if (check > 0) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][1] -= check - 19;
    }
  }

  check = 20;
  for (int i = 0; i < 8; i++) {
    if (current_block_pos[i][1] < 0 && current_block_pos[i][1] < check) {
      check = current_block_pos[i][1];
    }
  }
  if (check < 20) {
    for (int i = 0; i < 8; i++) {
      current_block_pos[i][1] += -check;
    }
  }
}

int update_highscore(int current_score) {
  FILE *file;
  int highscore = 0;

  file = fopen("highscore.md", "r");
  if (file == NULL) {
    file = fopen("highscore.md", "w");
    if (file == NULL) {
      perror("Ошибка при создании файла");
      exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", current_score);
    fclose(file);
  } else {
    fscanf(file, "%d", &highscore);
    fclose(file);
    if (current_score > highscore) {
      file = fopen("highscore.md", "w");
      if (file == NULL) {
        perror("Ошибка при открытии файла для записи");
        exit(EXIT_FAILURE);
      }
      fprintf(file, "%d\n", current_score);
      highscore = current_score;
    }
    fclose(file);
  }
  return highscore;
}

int timer(clock_t *start_time, double elapsed_time) {
  int timer = 0;
  GameInfo_t *stats = updateCurrentState();
  clock_t current_time = clock();
  elapsed_time = (double)(current_time - *start_time);

  if (elapsed_time >= 2000 - stats->level * 160) {
    timer = 1;
    *start_time = clock();
  }
  return timer;
}

GameInfo_t *updateCurrentState(void) {
  static GameInfo_t stats;
  return &stats;
}
