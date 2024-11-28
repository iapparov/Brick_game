#include "snake_consoleView.h"
#include <iostream>

namespace s21{

    void snakeConsoleView::startEventLoop() {
        
        bool flag = true;
        while (flag){

            switch (performChoice())
            {
            case TETRIS:{
                clear();
                print_overlay();
                game_loop();
                break;
            }
            case SNAKE:{
                while (controller->update()) {
                    render(controller->getModel());  // Рисуем текущую модель
                }
                break;
            case TERMINATE:
                flag = false;
                break;
            default:
                clear();
                displayMenu();
                break;
        }
        }
        

        }
    }

    void snakeConsoleView::render(snakeModel::Game_Stats stats){
        clear();
        if (controller->start_state()){
            print_intro();
        }
        print_overlay_snake();
        for (size_t i=0; i<stats.getBody().size(); i++){
            draw_block(stats.getBody().at(i).second, stats.getBody().at(i).first, 1);
            draw_block(stats.getBody().at(i).second, stats.getBody().at(i).first+1, 1);
        }
        for (size_t i=0; i<stats.getApple().size(); i++){
            draw_block(stats.getApple().at(i).second, stats.getApple().at(i).first, 2);
            draw_block(stats.getApple().at(i).second, stats.getApple().at(i).first+1, 2);
        }
        print_stats(stats.getLevel(), stats.getScore(), stats.getHighscore());
    }

    void snakeConsoleView::print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
        MVADDCH(top_y, left_x, ACS_ULCORNER);   // левый верхний угол
        MVADDCH(top_y, right_x, ACS_URCORNER);  // правый верхний угол
        MVADDCH(bottom_y, left_x, ACS_LLCORNER);  // нижний левый угол
        MVADDCH(bottom_y, right_x, ACS_LRCORNER);  // нижний правый угол

        for (int i = left_x + 1; i < right_x; i++) {
            MVADDCH(top_y, i, ACS_HLINE);     // верхняя сторона
            MVADDCH(bottom_y, i, ACS_HLINE);  // нижняя сторона
        }

        for (int i = top_y + 1; i < bottom_y; i++) {
            MVADDCH(i, left_x, ACS_VLINE);   // левая сторона
            MVADDCH(i, right_x, ACS_VLINE);  // правая сторона
        }
    }
    
    void snakeConsoleView::displayMenu(){
        print_rectangle(0, BOARD_Y + 1, 0,
                        BOARD_X * 2 + 1);  // Большое поле слева игровое
        print_rectangle(0, BOARD_Y + 1, BOARD_X * 2 + 2,
                        BOARD_X * 2 + HUD_WIDTH + 3);  // Поле информации большое

        MVPRINTW(BOARD_Y / 2, (BOARD_X * 2 - CHOOSE_MESSAGE_LEN) / 2 + 1,
                CHOOSE_MESSAGE);
        MVPRINTW(BOARD_Y / 2 + 1, (BOARD_X * 2 - CHOOSE_TETRIS_LEN) / 2 + 2,
                CHOOSE_TETRIS);
        MVPRINTW(BOARD_Y / 2 + 2, (BOARD_X * 2 - CHOOSE_SNAKE_LEN) / 2 + 1,
                CHOOSE_SNAKE);
    } 

    int snakeConsoleView::performChoice(){
        int Choice = 0;
        char char_Choice = GET_USER_INPUT;
        if (char_Choice == '1')
            Choice = TETRIS;
        if (char_Choice == '2')
            Choice = SNAKE;
        if (char_Choice == ESCAPE)
            Choice = TERMINATE;
        return Choice;
    }

    void snakeConsoleView::draw_block(int y, int x, int color_pair) {
        attron(COLOR_PAIR(color_pair));
        mvprintw(y, x, " ");
        attroff(COLOR_PAIR(color_pair));
    }

    void snakeConsoleView::print_stats(int level, int score, int high_score) {
        mvprintw(5, BOARD_X * 2 + 9, "    ");
        mvprintw(9, BOARD_X * 2 + 9, "    ");
        mvprintw(13, BOARD_X * 2 + 9, "    ");
        mvprintw(5, BOARD_X * 2 + 9, "%d", level);
        mvprintw(9, BOARD_X * 2 + 9, "%d", score);
        mvprintw(13, BOARD_X * 2 + 9, "%d", high_score);
    }

    void snakeConsoleView::print_overlay_snake() {
        print_rectangle(0, BOARD_Y + 1, 0,
                        BOARD_X * 2 + 1);  // Большое поле слева игровое
        print_rectangle(0, BOARD_Y + 1, BOARD_X * 2 + 2,
                        BOARD_X * 2 + HUD_WIDTH + 3);  // Поле информации большое

        print_rectangle(1, 4, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);
        print_rectangle(5, 8, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);
        print_rectangle(9, 12, BOARD_X * 2 + 3, BOARD_X * 2 + HUD_WIDTH + 2);

        MVPRINTW(2, BOARD_X * 2 + 6, "LEVEL");
        MVPRINTW(6, BOARD_X * 2 + 6, "SCORE");
        MVPRINTW(10, BOARD_X * 2 + 5, "HIGHSCORE");
        }
    
    void snakeConsoleView::print_intro(){
        MVPRINTW(BOARD_Y / 2, (BOARD_X * 2 - INTRO_MESSAGE_LEN) / 2 + 1,
        INTRO_MESSAGE);
        MVPRINTW(BOARD_Y / 2+2, (BOARD_X * 2 - BACK_MENU_MESSAGE_LEN) / 2 + 3,
        BACK_MENU_MESSAGE);
    }
}
