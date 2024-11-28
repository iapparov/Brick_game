CC := gcc
CPP := g++
RM := rm -rf
BACK = brick_game/
FRONT = gui/
CFLAGS := -Wall -Werror -Wextra
CPPFLAGS := -Wall -Werror -Wextra -std=c++17 -fsanitize=address
LDFLAGS := -lncurses
GTEST=-lgtest -lgtest_main -pthread
COVER=-fprofile-arcs -ftest-coverage
OBJS_BRICKGAME := out/tetris.o out/front.o out/fsm_matrix.o out/backend.o out/main.o out/snake_consoleView.o out/snake_Controller.o out/snake_Model.o
OBJS_TETRIS_TEST := out/front.o out/fsm_matrix.o out/backend.o out/tetris.o
SRCS_BRICKGAME := brick_game/tetris/tetris.c gui/cli/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c brick_game/main.cpp
SRCS_TETRIS_TEST := gui/cli/tetris/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c brick_game/tetris/tetris.c
SRCS_SNAKE_TEST := tests/snake.cc
OBJS_BRICKGAME_TESTS := out/tetris.o out/front.o out/fsm_matrix.o out/backend.o out/snake_consoleView.o out/cover_snake_Controller.o out/cover_snake_Model.o

# Путь к папке с проектом на Qt
QT_PROJECT_DIR := gui/desktop/Snake

all: install

dev: rebuild run

run: 
	@./games/brickgame

install: brickgame
	mkdir -p games
	mv brickgame games/brickgame
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃      'make run' to start the game       ┃"
	@echo "┗=========================================┛"

brickgame: $(OBJS_BRICKGAME)
	$(CPP) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

# Цель для сборки Qt приложения с использованием CMake
qtapp:
	@echo "Building Qt application..."
	mkdir -p $(QT_PROJECT_DIR)/build
	cd $(QT_PROJECT_DIR)/build && cmake .. && make
	@./gui/desktop/Snake/build/Snake.app/Contents/Macos/Snake

uninstall: clean
	$(RM) games/tetris

out/%.o: brick_game/tetris/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: gui/cli/tetris/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: brick_game/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

out/%.o: brick_game/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

out/%.o: brick_game/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

out/cover_%.o: brick_game/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) $(COVER) -c $< -o out/$(@F)

out/%.o: gui/cli/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

test: tests/*.check $(OBJS_TETRIS_TEST)
	checkmk clean_mode=1 tests/*.check > test.c
	gcc $(CFLAGS) test.c $(OBJS_TETRIS_TEST) -lcheck -lm -lpthread -o test $(LDFLAGS)
	./test
	rm *.md

gcov_report: test
	gcc $(CFLAGS) -coverage *.c $(SRCS_TETRIS_TEST) -o gcovreport -lcheck -lm $(LDFLAGS)
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	lcov -r gcovreport.info "*/gui/cli/tetris/*" "*/brick_game/tetris/tetris.c" -o gcovreport-filtered.info
	genhtml -o report gcovreport-filtered.info
	open report/index.html
	mv *.gcno report/
	mv *.gcda report/
	mv *.gcov report/


test_cpp: clean $(OBJS_BRICKGAME) $(OBJS_BRICKGAME_TESTS)
	g++ $(CPPFLAGS) $(COVER) $(SRCS_SNAKE_TEST) $(OBJS_BRICKGAME_TESTS) -o test $(GTEST) -lncurses
	./test

gcov_report_cpp: test_cpp $(OBJS_BRICKGAME_TESTS)
	g++ $(CPPFLAGS) $(COVER) $(SRCS_SNAKE_TEST) $(OBJS_BRICKGAME_TESTS) -o test $(GTEST) -lncurses
	./test
	gcov $(OBJS_BRICKGAME_TESTS)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	open out/index.html
	rm -rf *.gcno *.gcda *.gcov *.info */*.gcno ../*.gcda ../*.gcov ../*.info


clean:
	$(RM) out/* tetris games/highscore.md test test.c report *.info *.gz gcovreport highscore.md Snakehighscore.md /gui/desktop/Snake/build *.gcno *.gcda *.gcov *.info

rebuild: clean install