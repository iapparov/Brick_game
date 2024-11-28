#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>  // Для работы с событиями клавиш
#include "../../../brick_game/snake/snake_Model.h"  // Подключение вашей модели
#include "../../../brick_game/snake/snake_Controller.h"  // Подключение вашей модели


class GameWidget : public QWidget {
    Q_OBJECT

public:
    GameWidget(s21::snakeController *c, QWidget *parent = nullptr);
    void EnterKey();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QTimer *timer_;
    s21::snakeController *controller_;

    void updateGame();
};

#endif // GAMEWIDGET_H
