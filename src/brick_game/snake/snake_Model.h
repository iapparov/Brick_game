#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <vector>
#include <random>
#include <utility> // Для std::pair
namespace s21 {

class snakeModel
{
public:
    enum dir {
            UP = 0,
            RIGHT,
            DOWN,
            LEFT
        };
    struct Game_Stats {
    private:
        std::vector<std::pair<int, int>> body_;
        dir direction_;
        int level_;
        int score_;
        int highscore_;
        std::vector<std::pair<int, int>> apple_;
    public:
        Game_Stats() : direction_(UP), level_(1), score_(0), highscore_(0) {};
        std::vector<std::pair<int, int>>& getBody();
        std::vector<std::pair<int, int>>& getApple();
        int getLevel() const;
        int getScore() const;
        int getHighscore() const;
        dir& getDir();
        void setLevel(int level);
        void setScore(int score);
        void setHighscore(int highscore);
        void addBodySegment(int x, int y);
        void addAppleSegment(int x, int y);
        void AppleClear();
    };

private:
    Game_Stats game_stats_;

public:
    snakeModel() : game_stats_() {}
    void spawn();
    void apple_spawn();
    void update_highscore();
    bool isPositionFree(int x, int y);
    bool snake_collide();
    void snake_plus();
    bool check_borders();
    void snake_move_up();
    void snake_move_down();
    void snake_move_left();
    void snake_move_right();
    void snake_move();
    void stats();
    void clear_body();

    const Game_Stats& getGameStats() const;
};

}

#endif