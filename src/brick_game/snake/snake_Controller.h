#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "snake_Model.h"

namespace s21 {
/**
 * @brief FSM of snake.
 * @class snakeController
 */
class snakeController {
 public:
  snakeModel *model;

  /**
   * @brief FSM STATES.
   * @enum snake_state
   */
  typedef enum {
    START = 0,
    SPAWN,
    MOVING,
    REACH,
    GAMEOVER,
    PAUSE,
    EXIT_STATE
  } snake_state;

  /**
   * @brief action buttons to control.
   * @enum UserAction
   */
  typedef enum {
    NOSIG = 0,
    Down,
    Right,
    Left,
    Up,
    Terminate,
    Pause,
    Start,
    Move
  } UserAction;

 private:
  snake_state state_;
  int sig_;
  clock_t start_time_;
  double elapsed_time_;
  bool gameover_;

 public:
  snakeController(snakeModel *m);

  /**
   * @brief action buttons to control from QT.
   */
  void QTsig(int sig);

  /**
   * @brief get actual state.
   */
  snake_state getState();

  /**
   * @brief set start state.
   */
  bool start_state() const;

  /**
   * @brief check gameover state.
   */
  bool gameover_state() const;

  /**
   * @brief main method for FSM workin.
   */
  bool update();

  /**
   * @brief timer for snake Moving.
   */
  int timer();

  /**
   * @brief method to get model and send to front.
   */
  const snakeModel::Game_Stats &getModel();

  /**
   * @brief methods for processing user action.
   */
  UserAction get_signal(int user_input);
  void sigact(UserAction user_input, bool *break_flag);
};
}  // namespace s21

#endif