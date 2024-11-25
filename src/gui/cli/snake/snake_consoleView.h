#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../../../brick_game/snake/snake_Controller.h"
#include "../../../brick_game/defines.h"


extern "C" {
    #include "../../../brick_game/tetris/tetris.h" // подключаем C-заголовок
}

namespace s21{
    enum Choice
    {
        TETRIS = 1,
        SNAKE = 2,
    };

    class snakeConsoleView
    {
        private:
            snakeController *controller;
        public:
            snakeConsoleView(snakeController *c):controller(c){};
            void displayMenu();
            int performChoice();
            void startEventLoop();
            void draw_block(int y, int x, int color_pair);
            void print_stats(int level, int score, int high_score);
            void render(snakeModel::Game_Stats stats);
            void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
            void print_overlay_snake();
            void print_intro();
    };
}


#endif