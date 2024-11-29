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

brickgame: CPPFLAGS += -DCONSOLE
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

out/%.o: gui/cli/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

out/cover_%.o: brick_game/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) $(COVER) -c $< -o out/$(@F)

test: clean $(OBJS_BRICKGAME) $(OBJS_BRICKGAME_TESTS) tests/*.check $(OBJS_TETRIS_TEST)
	checkmk clean_mode=1 tests/*.check > test.c
	gcc $(CFLAGS) test.c $(OBJS_TETRIS_TEST) -lcheck -lm -lpthread -o test_tetris $(LDFLAGS)
	g++ $(CPPFLAGS) $(COVER) $(SRCS_SNAKE_TEST) $(OBJS_BRICKGAME_TESTS) -o test_snake $(GTEST) -lncurses
	./test_snake
	./test_tetris
	rm *.md

gcov_report: test
	gcc $(CFLAGS) -coverage *.c $(SRCS_TETRIS_TEST) -o gcovreport -lcheck -lm $(LDFLAGS)
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	lcov -r gcovreport.info "*/gui/cli/tetris/*" "*/brick_game/tetris/tetris.c"  "*/v1/*" "*/usr/*"  -o gcovreport-filtered.info
	genhtml -o report gcovreport-filtered.info
	open report/index.html
	mv *.gcno report/
	mv *.gcda report/
	mv *.gcov report/


dvi: dvi_clean
	doxygen dvi/Doxyfile
	mv html dvi
	open dvi/html/index.html

dvi_clean:
	$(RM) dvi/html

dist:
	@mkdir -p dist
	@cp -r $(BACK) dist
	@cp -r $(FRONT) dist
	@cp -r dvi dist/  
	@tar -czvf tetris.tar.gz -C dist .
	@rm -rf dist tetris
	@echo "Distribution package created: /tetris.tar.gz"

clang_check:
	@clang-format -style=Google -n brick_game/*.* brick_game/tetris/*.* gui/cli/*.*

clang_fix:
	@clang-format -style=Google -i brick_game/*.* brick_game/tetris/*.* gui/cli/tetris/*.* brick_game/snake/*.* gui/cli/snake/*.* gui/desktop/snake*.*

clean: dvi_clean
	$(RM) out/* tetris games/highscore.md games/brickgame test test.c report *.info *.gz gcovreport highscore.md Snakehighscore.md /gui/desktop/Snake/build *.gcno *.gcda *.gcov *.info test_snake test_tetris 

rebuild: clean install