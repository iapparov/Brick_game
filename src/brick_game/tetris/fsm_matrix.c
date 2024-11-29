#include "fsm.h"

// This is a finite state machine realisation based on matrix of "actions".
/*
    Function sigact() takes an action function from fsm_table.
    Game state defines an index of line in matrix (where to get).
    User signal defines an index of column in matrix (what to get).

    Pros:
        1) By instantly taking needed action, speed of processing is higher than
   switch-case realisation. 2) Code is easy to read. 3) Flexible (easy to add
   new state) Cons: 1) More memory usage.
*/

typedef void (*action)(GameInfo_t *stats);

void spawn(GameInfo_t *stats);
void movedown(GameInfo_t *stats);
void moveright(GameInfo_t *stats);
void moveleft(GameInfo_t *stats);
void rotate(GameInfo_t *stats);
void gameover(GameInfo_t *stats);
void exitstate(GameInfo_t *stats);
void pause(GameInfo_t *stats);
int check_collide(GameInfo_t *stats);

action fsm_table[6][8] = {
    {NULL, NULL, NULL, NULL, NULL, exitstate, NULL, spawn},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, movedown, moveright, moveleft, rotate, exitstate, pause, NULL},
    {gameover, gameover, gameover, gameover, exitstate, gameover, gameover,
     gameover},
    {NULL, NULL, NULL, NULL, NULL, exitstate, pause, NULL},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
     exitstate, exitstate}};

void userInput(UserAction_t sig) {
  action act = NULL;
  GameInfo_t *stats = updateCurrentState();
  act = fsm_table[stats->state][sig];

  if (act) {
    act(stats);
  }
}

UserAction_t get_signal(UserAction_t user_input) {
  UserAction_t rc = NOSIG;

  if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == ESCAPE)
    rc = Terminate;
  else if (user_input == ENTER_KEY)
    rc = Start;
  else if (user_input == SPACE_KEY)
    rc = Action;
  else if (user_input == 'p')
    rc = Pause;

  return rc;
}

void spawn(GameInfo_t *stats) {
  stats->current_block_type = stats->next_block_type;
  stats->next_block_type = rand() % 7 + 1;
  block_init(stats->current_block_type, stats->current_block_pos);
  block_init(stats->next_block_type, stats->next_block_pos);
  stats->current_rotate = 0;
  if (check_spawn(stats->field, stats->current_block_pos)) {
    stats->state = MOVING;
  } else {
    stats->state = GAMEOVER;
  }
}

void movedown(GameInfo_t *stats) {
  if (!check_collide(stats)) {
    for (int i = 0; i < 8; i++) {
      stats->current_block_pos[i][1] += 1;
    }
  }
}

void moveright(GameInfo_t *stats) {
  int check = 0;
  for (int i = 0; i < 8; i++) {
    if (stats->current_block_pos[i][0] == 18 ||
        stats->field[stats->current_block_pos[i][0] + 1]
                    [stats->current_block_pos[i][1]] != 0)
      check = 1;
  }
  if (!check) {
    for (int i = 0; i < 8; i++) {
      stats->current_block_pos[i][0] += 2;
    }
  }
}

void moveleft(GameInfo_t *stats) {
  int check = 0;
  for (int i = 0; i < 8; i++) {
    if (stats->current_block_pos[i][0] == 0 ||
        stats->field[stats->current_block_pos[i][0] - 1]
                    [stats->current_block_pos[i][1]] != 0)
      check = 1;
  }
  if (!check) {
    for (int i = 0; i < 8; i++) {
      stats->current_block_pos[i][0] -= 2;
    }
  }
}

void rotate(GameInfo_t *stats) {
  switch (stats->current_block_type) {
    case 1:
      i_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    case 2:
      j_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    case 3:
      l_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    case 5:
      s_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    case 6:
      t_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    case 7:
      z_block_rotate(stats->current_block_pos, &stats->current_rotate,
                     stats->field);
      break;
    default:
      break;
  }
}

int check_collide(GameInfo_t *stats) {
  int check = 0;

  for (int i = 0; i < 8; i++) {
    if (stats->current_block_pos[i][1] + 2 <= BOARD_Y)
      if (stats->field[stats->current_block_pos[i][0]]
                      [stats->current_block_pos[i][1] + 1] == 0)
        continue;
      else {
        check = 1;
      }
    else {
      check = 1;
    }
  }

  if (check) {
    for (int i = 0; i < 8; i++) {
      stats->field[stats->current_block_pos[i][0]]
                  [stats->current_block_pos[i][1]] = stats->current_block_type;
    }

    int score = attaching(stats->field);
    if (score >= 0) {
      game_stats(score, &stats->score, &stats->level, &stats->high_score);
      stats->state = SPAWN;
    } else {
      stats->state = GAMEOVER;
    }
  }
  return check;
}

void gameover(GameInfo_t *stats) {
  MVPRINTW(BOARD_Y / 2, (BOARD_X * 2 - GM_MESSAGE_LEN) / 2 + 1, GM_MESSAGE);
  MVPRINTW(BOARD_Y / 2 + 2, (BOARD_X * 2 - INTRO_MESSAGE_LEN) / 2 + 1,
           INTRO_MESSAGE);

  stats->state = START;
  stats_init();
}

void exitstate(GameInfo_t *stats) { stats->state = EXIT_STATE; }

void pause(GameInfo_t *stats) {
  if (stats->state != PAUSE) {
    stats->state = PAUSE;
  } else {
    stats->state = MOVING;
  }
}
