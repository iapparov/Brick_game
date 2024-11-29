#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../../../brick_game/defines.h"
#include "../../../brick_game/snake/snake_Controller.h"

extern "C" {
#include "../../../brick_game/tetris/tetris.h"  // подключаем C-заголовок
}

/**
 * @brief Choice for the menu.
 * @enum Choice
 */
namespace s21 {
enum Choice { TETRIS = 1, SNAKE = 2, TERMINATE };


/**
 * @brief Class a-la frontend for View .
 * @class snakeConsoleView
 */
class snakeConsoleView {
 private:
  snakeController *controller;

 public:
  snakeConsoleView(snakeController *c) : controller(c){};
  /**
 * @brief Display the menu.
 */
  void displayMenu();

  /**
 * @brief Choice.
 */
  int performChoice();

/**
 * @brief Main cycle.
 */
  void startEventLoop();

/**
 * @brief method for drawing a pixel of body or apple.
 */
  void draw_block(int y, int x, int color_pair);

  /**
 * @brief method for drawing stats.
 */
  void print_stats(int level, int score, int high_score);

  /**
 * @brief method for drawing a pixel of body or apple.
 */
  void render(snakeModel::Game_Stats stats);
  void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

  /**
 * @brief method for snake field.
 */
  void print_overlay_snake();

  /**
 * @brief method for intro and some control.
 */
  void print_intro();

  /**
 * @brief method for printing that game is over.
 */
  void print_gameover();
};
}  // namespace s21

#endif