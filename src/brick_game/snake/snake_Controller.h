#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "snake_Model.h"

namespace s21{

    class snakeController 
    {
        private:
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
            snake_state state_;
            int sig_;
            clock_t start_time_;
            double elapsed_time_;
        public:
            snakeController(snakeModel *m):model(m), sig_(0), start_time_(clock()), elapsed_time_(0.0) {
                srand(time(NULL));
            };
            bool start_state() const;
            bool update();
            int timer();
            const snakeModel::Game_Stats& getModel(); 
            UserAction get_signal(int user_input);
            void sigact(UserAction user_input, bool *break_flag);
    };
}

#endif