#ifndef FSM_H
#define FSM_H

#include "../../gui/cli/tetris/front.h"
#include "../defines.h"
#include "backend.h"

/**
 * @enum tetris_state
 * @brief States for fsm
 */

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  GAMEOVER,
  PAUSE,
  EXIT_STATE
} tetris_state;

/**
 * @enum UserAction_t
 * @brief Keys that are used in the game
 */

typedef enum {
  NOSIG = 0,
  Down,
  Right,
  Left,
  Action,
  Terminate,
  Pause,
  Start,
  UP
} UserAction_t;

/**
 * @brief Function that is used for interract with user's keyboard
 * @param user_input: Parameter that accepts a specific key
 */
UserAction_t get_signal(UserAction_t user_input);

/**
 * @brief Function for working with a matrix of finite state machines
 * @param sig: Parameter that accepts a specific key
 */
void userInput(UserAction_t sig);

#endif
