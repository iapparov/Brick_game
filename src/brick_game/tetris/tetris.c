#include "tetris.h"

int main(void) {
  WIN_INIT(50);
  setlocale(LC_ALL, "");
  print_overlay();
  game_loop();
  endwin();
  return SUCCESS;
}

void game_loop(void) {
  UserAction_t sig = 0;
  srand(time(NULL));
  stats_init();
  bool break_flag = TRUE;
  clock_t start_time;
  double elapsed_time = 0.0;
  start_time = clock();

  while (break_flag) {
    GameInfo_t *stats = updateCurrentState();
    if (stats->state == EXIT_STATE) break_flag = FALSE;

    if (stats->state == MOVING && timer(&start_time, elapsed_time)) {
      userInput(Down);
    }

    userInput(get_signal(sig));

    if (stats->state == MOVING || stats->state == START ||
        stats->state == GAMEOVER || stats->state == PAUSE) {
      sig = GET_USER_INPUT;
    }
  }
}
