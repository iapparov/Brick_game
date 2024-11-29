#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "snake_Model.h"

namespace s21{

    class snakeController 
    {
        public:
            snakeModel *model;
            typedef enum {
                START = 0,
                SPAWN,
                MOVING,
                REACH,
                GAMEOVER,
                PAUSE,
                EXIT_STATE
            } snake_state;

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
            void QTsig(int sig);
            snake_state getState();
            bool start_state() const;
            bool gameover_state() const;
            bool update();
            int timer();
            const snakeModel::Game_Stats& getModel(); 
            UserAction get_signal(int user_input);
            void sigact(UserAction user_input, bool *break_flag);
    };
}

#endif