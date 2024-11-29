#include "snake_Model.h"

#include <iostream>
namespace s21 {
void snakeModel::stats() {
  game_stats_.setScore(game_stats_.getScore() + 1);
  update_highscore();
  if (game_stats_.getScore() % 5 == 0 && game_stats_.getLevel() <= 10) {
    game_stats_.setLevel(game_stats_.getLevel() + 1);
  }
}

void snakeModel::spawn() {
  // game_stats_.addBodySegment(11,10);
  game_stats_.addBodySegment(11, 10);
  // game_stats_.addBodySegment(11,11);
  game_stats_.addBodySegment(11, 11);
  game_stats_.addBodySegment(11, 12);
  game_stats_.addBodySegment(11, 13);
  apple_spawn();
}

void snakeModel::update_highscore() {
  FILE* file;
  int highscore = game_stats_.getScore();

  file = fopen("Snakehighscore.md", "r");
  if (file == NULL) {
    file = fopen("Snakehighscore.md", "w");
    if (file == NULL) {
      perror("Ошибка при создании файла");
      exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", game_stats_.getScore());
    fclose(file);
  } else {
    fscanf(file, "%d", &highscore);
    fclose(file);
    if (game_stats_.getScore() > highscore) {
      file = fopen("Snakehighscore.md", "w");
      if (file == NULL) {
        perror("Ошибка при открытии файла для записи");
        exit(EXIT_FAILURE);
      }
      fprintf(file, "%d\n", game_stats_.getScore());
      highscore = game_stats_.getScore();
    }
    fclose(file);
  }
  game_stats_.setHighscore(highscore);
}

void snakeModel::apple_spawn() {
  game_stats_.AppleClear();
  std::random_device rd;  // Источник энтропии
  std::mt19937 gen(rd());  // Генератор на основе Mersenne Twister

  // Определяем диапазон случайных чисел
  std::uniform_int_distribution<> dist(3, 10);  // Диапазон от 1 до 100
  std::uniform_int_distribution<> dist_y(3, 21);  // Диапазон от 1 до 100

  // Генерируем случайное число
  int random_x, random_y;

  do {
    random_x = 2 * dist(gen) + 1;
    random_y = dist_y(gen);
  } while (
      !isPositionFree(random_x, random_y));  // Проверяем, свободна ли позиция

  // game_stats_.addAppleSegment(random_x, random_y);
  game_stats_.addAppleSegment(random_x, random_y);
}

bool snakeModel::isPositionFree(int x, int y) {
  // Проверяем, находится ли позиция (x, y) в теле змейки
  for (size_t i = 0; i < game_stats_.getBody().size(); i++) {
    if (game_stats_.getBody().at(i).first == x &&
        game_stats_.getBody().at(i).second == y) {
      return false;  // Позиция занята
    }
  }
  return true;  // Позиция свободна
}

void snakeModel::clear_body() {
  game_stats_.AppleClear();
  game_stats_.getBody().clear();
  game_stats_.setLevel(1);
  game_stats_.setScore(0);
  game_stats_.setHighscore(0);
  update_highscore();
  game_stats_.getDir() = UP;
}

bool snakeModel::snake_collide() {
  bool flag = false;
  if (game_stats_.getBody().at(0).first == game_stats_.getApple().at(0).first &&
      game_stats_.getBody().at(0).second == game_stats_.getApple().at(0).second)
    flag = true;
  // if (game_stats_.getBody().at(1).first == game_stats_.getApple().at(0).first
  // &&
  //     game_stats_.getBody().at(1).second ==
  //     game_stats_.getApple().at(0).second) flag = true;
  // if (game_stats_.getBody().at(0).first == game_stats_.getApple().at(1).first
  // &&
  //     game_stats_.getBody().at(0).second ==
  //     game_stats_.getApple().at(1).second) flag = true;
  // if (game_stats_.getBody().at(1).first == game_stats_.getApple().at(1).first
  // &&
  //     game_stats_.getBody().at(1).second ==
  //     game_stats_.getApple().at(1).second) flag = true;

  return flag;
}

void snakeModel::snake_plus() {
  int last_x = game_stats_.getBody().back().first;
  int last_y = game_stats_.getBody().back().second;
  int pre_last_x =
      game_stats_.getBody().at(game_stats_.getBody().size() - 2).first;
  int pre_last_y =
      game_stats_.getBody().at(game_stats_.getBody().size() - 2).second;
  if (last_x - pre_last_x == 0 && last_y - pre_last_y == -1)
    game_stats_.addBodySegment(last_x, last_y - 1);
  else if (last_x - pre_last_x == 0 && last_y - pre_last_y == 1)
    game_stats_.addBodySegment(last_x, last_y + 1);
  else if (last_x - pre_last_x == -1 && last_y - pre_last_y == 0)
    game_stats_.addBodySegment(last_x - 1, last_y);
  else
    game_stats_.addBodySegment(last_x + 1, last_y);
}

bool snakeModel::check_borders() {
  bool border_flag = false;
  if (game_stats_.getBody().at(0).first < 3 ||
      game_stats_.getBody().at(0).first > 22)
    border_flag = true;
  if (game_stats_.getBody().at(0).second < 3 ||
      game_stats_.getBody().at(0).second > 22)
    border_flag = true;

  for (size_t i = 1; i < game_stats_.getBody().size(); ++i) {
    if (game_stats_.getBody().at(0).first ==
            game_stats_.getBody().at(i).first &&
        game_stats_.getBody().at(0).second ==
            game_stats_.getBody().at(i).second)
      border_flag = true;
  }

  return border_flag;
}

void snakeModel::snake_move() {
  // Получаем текущую голову змейки
  auto& body = game_stats_.getBody();

  // Новая позиция головы
  int new_x = body[0].first;
  int new_y = body[0].second;
  // int new_x2 = body[1].first;
  // int new_y2 = body[1].second;

  // Обновляем координаты головы в зависимости от направления
  switch (game_stats_.getDir()) {
    case UP:
      new_y -= 1;
      // new_y2 -= 1;
      break;
    case DOWN:
      new_y += 1;
      // new_y2 += 1;
      break;
    case RIGHT:
      new_x += 1;
#ifdef CONSOLE
      new_x += 1;
#endif
      // new_x2 += 2;
      break;
    case LEFT:
      new_x -= 1;
#ifdef CONSOLE
      new_x -= 1;
#endif
      // new_x2 -= 2;
      break;
  }

  // Двигаем тело змейки
  for (size_t i = body.size() - 1; i > 0; --i) {
    body[i] = body[i - 1];  // Каждый сегмент тела берет координаты предыдущего
  }

  // Обновляем координаты головы
  body[0] = {new_x, new_y};
  // body[1] = {new_x2, new_y2};
}

void snakeModel::snake_move_up() {
  // Смена направления на "вверх"
  if (game_stats_.getDir() != DOWN) {  // Нельзя развернуться обратно
                                       // Получаем тело змейки
    auto& body = game_stats_.getBody();
    auto& dir = game_stats_.getDir();
    dir = UP;
    // Новая позиция головы
    int new_x = body[0].first;  // Текущая X-координата головы
    int new_y = body[0].second - 1;  // Сдвиг вверх (уменьшение Y-координаты)
    // int new_x2 = body[1].first; // Текущая X-координата головы
    // int new_y2 = body[1].second-1; // Сдвиг вверх (уменьшение Y-координаты)

    // Двигаем тело змейки (с конца в начало)
    for (size_t i = body.size() - 1; i > 0; --i) {
      body[i] = body[i - 1];  // Каждый сегмент занимает место предыдущего
    }

    // Обновляем координаты головы
    body[0] = {new_x, new_y};
    // body[1] = {new_x2, new_y2};
  }
}

void snakeModel::snake_move_down() {
  if (game_stats_.getDir() != UP) {  // Нельзя развернуться обратно
    auto& body = game_stats_.getBody();
    auto& dir = game_stats_.getDir();
    dir = DOWN;

    // Новая позиция головы
    int new_x = body[0].first;  // Текущая X-координата головы
    int new_y = body[0].second + 1;  // Сдвиг вверх (уменьшение Y-координаты)
    // int new_x2 = body[1].first; // Текущая X-координата головы
    // int new_y2 = body[1].second+1; // Сдвиг вверх (уменьшение Y-координаты)

    // Двигаем тело змейки (с конца в начало)
    for (size_t i = body.size() - 1; i > 0; --i) {
      body[i] = body[i - 1];  // Каждый сегмент занимает место предыдущего
    }

    // Обновляем координаты головы
    body[0] = {new_x, new_y};
    // body[1] = {new_x2, new_y2};
  }
}
void snakeModel::snake_move_left() {
  if (game_stats_.getDir() != RIGHT) {  // Нельзя развернуться обратно
    auto& body = game_stats_.getBody();
    auto& dir = game_stats_.getDir();
    dir = LEFT;
    // Новая позиция головы
    int new_x = body[0].first - 1;  // Текущая X-координата головы
    int new_y = body[0].second;  // Сдвиг вверх (уменьшение Y-координаты)
#ifdef CONSOLE
    new_x -= 1;
#endif
    // int new_x2 = body[1].first-2; // Текущая X-координата головы
    // int new_y2 = body[1].second; // Сдвиг вверх (уменьшение Y-координаты)

    // Двигаем тело змейки (с конца в начало)
    for (size_t i = body.size() - 1; i > 0; --i) {
      body[i] = body[i - 1];  // Каждый сегмент занимает место предыдущего
    }

    // Обновляем координаты головы
    body[0] = {new_x, new_y};
    // body[1] = {new_x2, new_y2};
  }
}
void snakeModel::snake_move_right() {
  if (game_stats_.getDir() != LEFT) {  // Нельзя развернуться обратно
    auto& body = game_stats_.getBody();
    auto& dir = game_stats_.getDir();
    dir = RIGHT;
    // Новая позиция головы
    int new_x = body[0].first + 1;  // Текущая X-координата головы
    int new_y = body[0].second;  // Сдвиг вверх (уменьшение Y-координаты)
#ifdef CONSOLE
    new_x += 1;
#endif
    // int new_x2 = body[1].first+2; // Текущая X-координата головы
    // int new_y2 = body[1].second; // Сдвиг вверх (уменьшение Y-координаты)

    // Двигаем тело змейки (с конца в начало)
    for (size_t i = body.size() - 1; i > 0; --i) {
      body[i] = body[i - 1];  // Каждый сегмент занимает место предыдущего
    }

    // Обновляем координаты головы
    body[0] = {new_x, new_y};
    // body[1] = {new_x2, new_y2};
  }
}

void snakeModel::Game_Stats::AppleClear() { apple_.clear(); }

snakeModel::dir& snakeModel::Game_Stats::getDir() { return direction_; }

std::vector<std::pair<int, int>>& snakeModel::Game_Stats::getBody() {
  return body_;
}

std::vector<std::pair<int, int>>& snakeModel::Game_Stats::getApple() {
  return apple_;
}

int snakeModel::Game_Stats::getLevel() const { return level_; }

int snakeModel::Game_Stats::getScore() const { return score_; }

int snakeModel::Game_Stats::getHighscore() const { return highscore_; }

void snakeModel::Game_Stats::setLevel(int level) { level_ = level; }

void snakeModel::Game_Stats::setScore(int score) { score_ = score; }

void snakeModel::Game_Stats::setHighscore(int highscore) {
  highscore_ = highscore;
}

void snakeModel::Game_Stats::addBodySegment(int x, int y) {
  body_.emplace_back(x, y);
}

void snakeModel::Game_Stats::addAppleSegment(int x, int y) {
  apple_.emplace_back(x, y);
}

const snakeModel::Game_Stats& snakeModel::getGameStats() const {
  return game_stats_;
}
}  // namespace s21