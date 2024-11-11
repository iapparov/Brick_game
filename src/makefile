CC := gcc
RM := rm -rf
BACK = brick_game/
FRONT = gui/
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -lncurses
OBJS_TETRIS := out/tetris.o out/front.o out/fsm_matrix.o out/backend.o
OBJS_TETRIS_TEST := out/front.o out/fsm_matrix.o out/backend.o
SRCS_TETRIS := brick_game/tetris/tetris.c gui/cli/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c
SRCS_TETRIS_TEST := gui/cli/front.c brick_game/tetris/fsm_matrix.c brick_game/tetris/backend.c
all: install

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
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

uninstall: clean
	$(RM) games/tetris

out/%.o: brick_game/tetris/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: gui/cli/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

test: tests/*.check $(OBJS_TETRIS_TEST)
	checkmk clean_mode=1 tests/*.check > test.c
	gcc $(CFLAGS) test.c $(OBJS_TETRIS_TEST) -lcheck -lm -lpthread -o test $(LDFLAGS)
	./test
	rm *.md

gcov_report: test
	gcc $(CFLAGS) -coverage *.c $(SRCS_TETRIS_TEST) -o gcovreport -lcheck -lm $(LDFLAGS)
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	lcov -r gcovreport.info "gui/cli/front.c" -o gcovreport-filtered.info
	genhtml -o report gcovreport-filtered.info
	open report/./index.html
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

clean:
	$(RM) out/*.o tetris games/highscore.md test test.c report *.info *.gz gcovreport highscore.md

rebuild: clean install

clang_check:
	@clang-format -style=Google -n brick_game/*.* brick_game/tetris/*.* gui/cli/*.*

clang_fix:
	@clang-format -style=Google -i brick_game/*.* brick_game/tetris/*.* gui/cli/*.*

.PHONY: all install uninstall test gcov_report clean rebuild run clang_check clang_fix
