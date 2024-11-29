#include "./ui_snakemainwindow.h"
// #include "SnakeNcurses.h"
#include "snakemainwindow.h"

SnakeMainWindow::SnakeMainWindow(s21::snakeController *c, QWidget *parent)
    : controller_(c), QMainWindow(parent) {
  setupUI();
  setWindowTitle("Snake Game");
  resize(800, 600);  // Размер окна
  // Создание и запуск потока для ncurses
  // NcursesInputThread* inputThread = new NcursesInputThread(controller_);
  // inputThread->start();  // Запуск потока
}

void SnakeMainWindow::setupUI() {
  gameWidget_ = new GameWidget(controller_, this);
  setCentralWidget(gameWidget_);

  // Кнопка запуска
  QPushButton *startButton = new QPushButton("Start Game", this);
  connect(startButton, &QPushButton::clicked, this,
          &SnakeMainWindow::startGame);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(gameWidget_);
  layout->addWidget(startButton);

  QWidget *central = new QWidget(this);
  central->setLayout(layout);
  setCentralWidget(central);
}

void SnakeMainWindow::startGame() {
  gameWidget_->EnterKey();
  gameWidget_->update();  // Обновление начального состояния
}
