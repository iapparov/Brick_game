# BrickGame v2.0: SNAKE & TETRIS

---

## Описание

- Консольная и десктопная реализация классических игр Snake и Tetris.
- Используются C++ (Snake) и C (Tetris), ncurses для консольного интерфейса, Qt для графического.
- Хранение рекордов, уровней, динамическое усложнение, покрытие юнит-тестами.
- Чистая архитектура: разделение на слои **game logic** (бизнес-логика), **presentation** (UI), **datalayer** (работа с файлами).

---

## Структура проекта

```
src/
├── makefile
├── brick_game/
│   ├── defines.h
│   ├── snake/
│   │   ├── snake_Controller.cpp      # Контроллер Snake (MVC)
│   │   ├── snake_Controller.h
│   │   ├── snake_Model.cpp           # Модель Snake (MVC)
│   │   └── snake_Model.h
│   └── tetris/
│       ├── backend.c                 # Подсчёт очков, уровней, рекордов
│       ├── backend.h
│       ├── fsm_matrix.c              # FSM для Tetris
│       ├── fsm.h
│       ├── tetris.c                  # Основная логика Tetris
│       └── tetris.h
├── gui/
│   ├── cli/
│   │   ├── snake/
│   │   │   ├── snake_consoleView.cpp # Отрисовка Snake (CLI)
│   │   │   └── snake_consoleView.h
│   │   └── tetris/
│   │       ├── front.c               # Отрисовка Tetris (CLI)
│   │       └── front.h
│   └── desktop/
│       └── Snake/
│           ├── gamewidget.cpp        # Qt-виджет Snake
│           ├── gamewidget.h
│           ├── main.cpp              # Точка входа Qt
│           ├── snakemainwindow.cpp   # Главное окно Qt
│           └── snakemainwindow.h
├── dvi/
│   ├── Doxyfile                     # Документация Doxygen
│   └── README.md
├── tests/
│   ├── snake.cc                     # Юнит-тесты Snake
│   ├── test_snake.h
│   ├── backend.check                # Тесты Tetris
│   └── fsm.check
└── README.md
```

---

## Основные возможности

- **Snake:** классический геймплей, управление стрелками, увеличение скорости и длины, хранение рекорда, уровни.
- **Tetris:** классический геймплей, вращение фигур, ускорение падения, уровни, хранение рекорда.
- **Два интерфейса:** CLI (ncurses) и Qt (десктоп).
- **Юнит-тесты:** для логики Snake и Tetris.
- **Документация:** Doxygen, README, схемы FSM.

---

## Управление

### Snake (CLI/Qt)
- **Стрелки** — перемещение змейки
- **P** — пауза
- **Q** — выход

### Tetris (CLI)
- **Стрелки** — перемещение и вращение фигур
- **Пробел** — ускорить падение
- **P** — пауза
- **Q** — выход

---

## Сборка и запуск

### Консольная версия

```sh
cd src
make install
make run
```

### Qt-версия (Snake)

```sh
cd src
make qtapp
```

---

## Тестирование и покрытие

```sh
cd src
make test
make gcov_report
```

---

## Документация

- Генерация документации:
  ```sh
  cd src
  make dvi
  open dvi/html/index.html
  ```
- Основная документация: `src/dvi/README.md`
- Конфиг Doxygen: `src/dvi/Doxyfile`

---

## Примечания

- Для запуска CLI-версии требуется ncurses.
- Для Qt-версии требуется установленный Qt5/6.
- Для MacOS: убедитесь, что установлен пакет `ncurses` (`brew install ncurses`).

---

## Архитектура

- **brick_game/** — бизнес-логика Snake и Tetris.
- **gui/** — взаимодействие с пользователем: отрисовка, ввод, меню.
- **dvi/** — документация.
- **tests/** — юнит-тесты.

---

## Авторы

Emil Iapparov

---