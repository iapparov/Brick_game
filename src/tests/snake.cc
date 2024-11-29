#include "test_snake.h"

TEST(Controller1, Controller_Update) {

    s21::snakeModel model;
    s21::snakeController controller(&model);
    controller.update();
    EXPECT_EQ(controller.start_state(), true);
}

TEST(Controller2, START_SPAWN) {

    s21::snakeModel model;
    s21::snakeController controller(&model);
    controller.update();
    controller.QTsig(ENTER_KEY);
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::SPAWN);
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);
}

TEST(Controller2, START_TERMINATE) {

    s21::snakeModel model;
    s21::snakeController controller(&model);
    controller.update();
    controller.QTsig(ESCAPE);
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::EXIT_STATE);
}

TEST(Controller3, MOVING) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::SPAWN);

    controller.update();
    controller.QTsig(KEY_DOWN_CPP);  // Переход в MOVING
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);

    controller.update();
    controller.QTsig(KEY_UP_CPP);  // Переход в MOVING
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);

    controller.update();
    controller.QTsig(KEY_LEFT_CPP);  // Переход в MOVING
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);

    controller.update();
    controller.QTsig(KEY_RIGHT_CPP);  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);
}

TEST(Controller4, PAUSEUNPAUSE) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::SPAWN);

    controller.update();
    controller.QTsig('p');  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::PAUSE);

    controller.QTsig('p');  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);

    controller.QTsig(ESCAPE);  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::EXIT_STATE);
    controller.update();
}

TEST(Controller5, PAUSEEXIT) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::SPAWN);

    controller.update();
    controller.QTsig('p');  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::PAUSE);

    controller.QTsig(ESCAPE);  // Переход в MOVING
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::EXIT_STATE);
}

TEST(Controller6, GAMEOVER) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    for (int i = 0; i<15;i++ ){
        controller.QTsig(KEY_UP_CPP);  // Переход в MOVING
        controller.update();
    }
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::START);
}

TEST(Controller7, getModel) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    for (int i = 0; i<15;i++ ){
        controller.QTsig(KEY_UP_CPP);  // Переход в MOVING
        controller.update();
    }
    EXPECT_EQ(controller.getModel().getScore(), 0);
}

TEST(Controller8, Timer) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    
    controller.update();
    EXPECT_EQ(controller.getState(), s21::snakeController::snake_state::MOVING);
}

TEST(Controller9, GETGAMEOVER) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    
    controller.update();
    EXPECT_EQ(controller.gameover_state(), false);
}

TEST(Model1, Stats) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    
    model.stats();
    controller.update();
    EXPECT_EQ(model.getGameStats().getScore(), 1);
}

TEST(Model2, Level) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    
    for (int i = 0; i<6; ++i){
        model.stats();
    }
    controller.update();
    EXPECT_EQ(model.getGameStats().getLevel(), 2);
    EXPECT_NE(model.getGameStats().getHighscore(), -1);
}

TEST(Model3, Snake_Plus) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    s21::snakeModel::Game_Stats stats;
    
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();

    stats = controller.getModel();
    size_t i = stats.getBody().size();
    controller.update();
    model.snake_plus();
    stats = controller.getModel();
    size_t n = stats.getBody().size();
    EXPECT_NE(n, i);
}

TEST(Model4, SNAKE_MOVE) {
    s21::snakeModel model;
    s21::snakeController controller(&model);
    s21::snakeModel::Game_Stats stats;
    

    controller.update();
    controller.QTsig(ENTER_KEY);  // Переход в SPAWN
    controller.update();
    controller.update();
    stats = controller.getModel();
    int i = stats.getBody().at(0).second;
    controller.update();
    model.snake_move();
    stats = controller.getModel();
    int j = stats.getBody().at(0).second;
    EXPECT_NE(j, i);

    controller.update();
    stats = controller.getModel();
    int a = stats.getBody().at(0).first;
    controller.update();
    controller.QTsig(KEY_RIGHT_CPP);
    controller.update();
    controller.update();
    model.snake_move();
    controller.update();
    stats = controller.getModel();
    int b = stats.getBody().at(0).first;
    EXPECT_NE(a, b);

    controller.update();
    stats = controller.getModel();
    int x = stats.getBody().at(0).second;
    controller.update();
    controller.QTsig(KEY_DOWN_CPP);
    controller.update();
    controller.update();
    model.snake_move();
    controller.update();
    stats = controller.getModel();
    int y = stats.getBody().at(0).second;
    EXPECT_NE(x, y);

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}