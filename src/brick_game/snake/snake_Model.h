#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <random>
#include <utility>  // Для std::pair
#include <vector>
namespace s21 {
/**
 * @brief Class a-la backend for Body, Apple, stats.
 * @class snameModel
 */
class snakeModel {
 public:
  /**
   * @brief enum for moving direction .
   * @enum dir
   */
  enum dir { UP = 0, RIGHT, DOWN, LEFT };
  struct Game_Stats {
   private:
    std::vector<std::pair<int, int>> body_;
    dir direction_;
    int level_;
    int score_;
    int highscore_;
    std::vector<std::pair<int, int>> apple_;

   public:
    Game_Stats() : direction_(UP), level_(1), score_(0), highscore_(0){};
    std::vector<std::pair<int, int>>& getBody();
    std::vector<std::pair<int, int>>& getApple();

    /**
     * @brief setters and getters for variables.
     */
    int getLevel() const;
    int getScore() const;
    int getHighscore() const;
    dir& getDir();
    void setLevel(int level);
    void setScore(int score);
    void setHighscore(int highscore);

    /**
     * @brief add snake segment.
     */
    void addBodySegment(int x, int y);

    /**
     * @brief make the new apple.
     */
    void addAppleSegment(int x, int y);

    /**
     * @brief delete an apple that was eaten.
     */
    void AppleClear();
  };

 private:
  Game_Stats game_stats_;

 public:
  snakeModel() : game_stats_() {}

  /**
   * @brief main spawn for snake and apple.
   */
  void spawn();

  /**
   * @brief apple spawn.
   */
  void apple_spawn();

  /**
   * @brief method for updating highscore.
   */
  void update_highscore();

  /**
   * @brief check which avoid spawn an apple in the snake.
   */
  bool isPositionFree(int x, int y);

  /**
   * @brief chech if snake collide an apple.
   */
  bool snake_collide();

  /**
   * @brief increase snake.
   */
  void snake_plus();

  /**
   * @brief check snake collinding with field borders.
   */
  bool check_borders();

  /**
   * @brief change direction of snake.
   *
   */
  void snake_move_up();
  void snake_move_down();
  void snake_move_left();
  void snake_move_right();

  /**
   * @brief moving snake.
   */
  void snake_move();

  /**
   * @brief initialization score level and highscore.
   */
  void stats();

  /**
   * @brief clear snake after gameover.
   */
  void clear_body();

  const Game_Stats& getGameStats() const;
};

}  // namespace s21

#endif