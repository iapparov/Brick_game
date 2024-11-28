#include "snake_Controller.h"
#include "../defines.h"
#include <iostream>


namespace s21{
    bool snakeController::update()
    {
       
        bool break_flag = TRUE;
            if (state_ == EXIT_STATE) break_flag = FALSE;

            if (state_ == MOVING && timer()) {
            sigact(Move, &break_flag);
            }

            sigact(get_signal(sig_), &break_flag);

            if (state_ == MOVING || state_ == START ||
                state_ == GAMEOVER || state_ == PAUSE) {
            sig_ = GET_USER_INPUT;
            }
        return break_flag;
    }

    void snakeController::QTsig(int sig){
        sig_ = sig;
    }


    snakeController::snakeController(snakeModel *m):model(m),state_(START), sig_(0), start_time_(clock()), elapsed_time_(0.0) {
                srand(time(NULL));
            };

    int snakeController::timer() {
        int timer = 0;
        clock_t current_time = clock();
        elapsed_time_ = (double)(current_time - start_time_);

        if (elapsed_time_ >= 10000 - model->getGameStats().getLevel() * 1) {
            timer = 1;
            start_time_ = clock();
        }
        return timer;
    }

    const snakeModel::Game_Stats& snakeController::getModel() {
        return model->getGameStats();  // Получаем ссылку на game_stats_ через метод модели
    }

    bool snakeController::start_state() const{
        return state_ == START;
    }

    snakeController::snake_state snakeController::getState() {
        return state_;
    }
    

    snakeController::UserAction snakeController::get_signal(int user_input) {
        UserAction rc = NOSIG;

        if (user_input == KEY_DOWN_CPP)
            rc = Down;
        else if (user_input == KEY_LEFT_CPP)
            rc = Left;
        else if (user_input == KEY_RIGHT_CPP)
            rc = Right;
        else if (user_input == KEY_UP_CPP)
            rc = Up;
        else if (user_input == ESCAPE)
            rc = Terminate;
        else if (user_input == ENTER_KEY)
            rc = Start;
        else if (user_input == 'p')
            rc = Pause;

        return rc;
    }


void snakeController::sigact(UserAction user_input, bool *break_flag)
{
    switch (state_)
    {
        case START:
            switch (user_input)
            {
                case Start:
                    state_ = SPAWN;
                    break;
                case Terminate:
                    state_ = EXIT_STATE;
                    break;
                default:
                    break;
            }
            break;
        case SPAWN:
            model->spawn();
            state_ = MOVING;
            break;
        case MOVING:
            switch (user_input)
            {
                case Up:
                    model->snake_move_up();
                    break;
                case Down:
                    model->snake_move_down();
                    break;
                case Right:
                    model->snake_move_right();
                    break;
                case Left:
                    model->snake_move_left();
                    break;
                case Move:
                    model->snake_move();
                    break;
                case Pause:
                    user_input = NOSIG;
                    state_ = PAUSE;
                    break;
                case Terminate:
                    state_ = EXIT_STATE;
                    break;
                default:
                    break;
            }
            
            if (state_ != EXIT_STATE)
            {
                if (model->check_borders())
                    state_ = GAMEOVER;
                else if (model->snake_collide())
                    state_ = REACH;
            }
            break;
        case REACH:
            model->stats();
            model->snake_plus();
            model->apple_spawn();
            state_=MOVING;
            break;
        case GAMEOVER:
            model->clear_body();
            state_=START;
            break;
        case EXIT_STATE:
            model->clear_body();
            state_ = START;
            *break_flag = 0;
            break;
        case PAUSE:
            if (user_input == Pause){
                state_ = MOVING;
            }
            if (user_input == Terminate){
                state_ = EXIT_STATE;
            }
            break;
        default:
            break;
    }
}

}

