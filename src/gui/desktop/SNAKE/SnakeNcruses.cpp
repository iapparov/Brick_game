// ncurses_input_thread.cpp
#include "SnakeNcurses.h"

NcursesInputThread::NcursesInputThread(s21::snakeController* controller)
    : controller_(controller) {
    // Инициализация ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

NcursesInputThread::~NcursesInputThread() {
    endwin();  // Завершаем работу с ncurses
}

void NcursesInputThread::run() {
    while (true) {
        int ch = getch();  // Получаем символ из консоли
        if (ch == EOF) continue;

        // Передаем команду в контроллер
        if (ch == 27) {  // ESC
            controller_->get_signal(ch);
            qDebug() << "Updating game. Body size:" ;
        } else {
            controller_->get_signal(ch);  // Передаем полученную клавишу
        }

        QThread::msleep(50);  // Небольшая задержка между чтением
    }
}
