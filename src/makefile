CC := gcc
CPP := g++
RM := rm -rf
BACK = brick_game/
FRONT = gui/
CFLAGS := -Wall -Werror -Wextra
CPPFLAGS := -Wall -Werror -Wextra -std=c++17
LDFLAGS := -lncurses
OBJS_TETRIS := out/tetris.o out/front.o out/fsm_matrix.o out/backend.o out/main.o out/snake_consoleView.o out/snake_Controller.o out/snake_Model.o
OBJS_TETRIS_TEST := out/front.o out/fsm_matrix.o out/backend.o
SRCS_TETRIS := brick_game/tetris/tetris.c gui/cli/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c brick_game/main.cpp
SRCS_TETRIS_TEST := gui/cli/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c


all: install

dev: rebuild run

run: 
	@./games/tetris

install: tetris
	mkdir -p games
	mv tetris games/tetris
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃      'make run' to start the game       ┃"
	@echo "┗=========================================┛"

tetris: $(OBJS_TETRIS)
	$(CPP) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

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

out/%.o: gui/cli/snake/%.cpp
	mkdir -p out
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o tetris games/highscore.md test test.c report *.info *.gz gcovreport highscore.md

rebuild: clean install