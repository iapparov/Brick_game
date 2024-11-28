#ifndef SNAKEMAINWINDOW_H
#define SNAKEMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "gamewidget.h"
#include "../../../brick_game/snake/snake_Controller.h"

class SnakeMainWindow : public QMainWindow {
    Q_OBJECT

public:
    SnakeMainWindow(s21::snakeController *c, QWidget *parent = nullptr);
    ~SnakeMainWindow();

private:
    GameWidget *gameWidget_;
    s21::snakeController *controller_;

    void setupUI();
    void startGame();
};

#endif // SNAKEMAINWINDOW_H
