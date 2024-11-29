#include "gamewidget.h"

GameWidget::GameWidget(s21::snakeController *c, QWidget *parent)
    : controller_(c), QWidget(parent) {
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &GameWidget::updateGame);
  timer_->start(100);  // Обновление каждые 10 мс
  setFocusPolicy(Qt::StrongFocus);
  setFocus();  // Даем фокус этому виджету
}

void GameWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  // Отрисовка игрового поля
  painter.setPen(QPen(Qt::black, 3));  // Черная кисть толщиной 3 пикселя
  painter.setBrush(Qt::NoBrush);

  // Рисуем прямоугольник (рамку)
  QRect rect(55, 55, width() - 370, height() - 135);  // Внутри виджета
  painter.drawRect(rect);
  painter.setPen(Qt::NoPen);

  // Получаем статистику игры
  controller_->update();
  s21::snakeModel::Game_Stats stats_ = controller_->getModel();

  // Отрисовка тела змейки
  for (size_t i = 0; i < stats_.getBody().size(); i++) {
    painter.setBrush(Qt::green);
    painter.drawRect(stats_.getBody().at(i).first * 20,
                     stats_.getBody().at(i).second * 20, 20, 20);
  }

  // Отрисовка яблока
  for (size_t i = 0; i < stats_.getApple().size(); i++) {
    painter.setBrush(Qt::red);
    painter.drawRect(stats_.getApple().at(i).first * 20,
                     stats_.getApple().at(i).second * 20, 20, 20);
  }

  // Отрисовка статистики (Level, Score, Highscore)
  QRect statsRect(width() - 250, 55, 200,
                  150);  // Создаем прямоугольник для статистики
  painter.setPen(QPen(Qt::black));
  painter.setBrush(Qt::lightGray);
  painter.drawRect(statsRect);  // Отрисовка фона для статистики

  painter.setPen(QPen(Qt::black));
  painter.setFont(QFont("Arial", 14));  // Настроим шрифт

  // Устанавливаем начальную высоту для первого текста
  int yPos = statsRect.top() + 10;  // Начинаем с 10 пикселей от верхней границы

  // Отображаем текст статистики с отступами
  painter.drawText(statsRect.left() + 10, yPos,
                   "Level: " + QString::number(stats_.getLevel()));
  yPos += 30;  // Добавляем отступ после первого текста

  painter.drawText(statsRect.left() + 10, yPos,
                   "Score: " + QString::number(stats_.getScore()));
  yPos += 30;  // Добавляем отступ после второго текста

  painter.drawText(statsRect.left() + 10, yPos,
                   "Highscore: " + QString::number(stats_.getHighscore()));
}

void GameWidget::updateGame() {
  update();  // Перерисовка
             // timer_->stop();
}

void GameWidget::EnterKey() { controller_->QTsig(10); }

void GameWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return) {
    controller_->QTsig(10);  // Вызов метода с передачей 10
  } else if (event->key() == Qt::Key_Left) {
    controller_->QTsig(260);  // Например, передача 1 для движения влево
  } else if (event->key() == Qt::Key_Right) {
    controller_->QTsig(261);  // Передача 2 для движения вправо
  } else if (event->key() == Qt::Key_Up) {
    controller_->QTsig(259);  // Передача 3 для движения вверх
  } else if (event->key() == Qt::Key_Down) {
    controller_->QTsig(258);  // Передача 4 для движения вниз
  } else if (event->key() == Qt::Key_Escape) {
    controller_->QTsig(27);  // Передача 5, например, для выхода
  } else if (event->key() == Qt::Key_P) {
    controller_->QTsig(112);  // Передача 6 для паузы
  }

  QWidget::keyPressEvent(event);  // Важно вызвать родительский метод
}
