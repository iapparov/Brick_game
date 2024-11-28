// ncurses_input_thread.h
#ifndef NCURSES_INPUT_THREAD_H
#define NCURSES_INPUT_THREAD_H

#include <QThread>
#include <ncurses.h>
#include "../../../brick_game/snake/snake_Controller.h"
#undef scroll
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#undef timeout
#include <QtCore/QTimer>
#include <QtCore/QObject>



class NcursesInputThread : public QThread {
    Q_OBJECT

public:
    NcursesInputThread(s21::snakeController* controller);
    ~NcursesInputThread();

protected:
    void run() override;

private:
    s21::snakeController* controller_;
};

#endif // NCURSES_INPUT_THREAD_H
