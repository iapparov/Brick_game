#include "../gui/cli/snake/snake_consoleView.h"

int main(void) {
  WIN_INIT(50);
  setlocale(LC_ALL, "");
  s21::snakeModel model;
  s21::snakeController controller(&model);
  s21::snakeConsoleView view(&controller);
  view.startEventLoop();
  endwin();
  return SUCCESS;
}