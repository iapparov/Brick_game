
# BrickGame v2.0 aka SNAKE
 
## Introduction
Snake Game v2.0 is a classic console-based snake game developed in C++ using the ncurses library. The game features traditional snake gameplay with additional mechanics such as score tracking, game over conditions, and high score persistence.
 
## Features
Classic Snake gameplay with the following mechanics:
- Snake movement controlled by the arrow keys
- Snake grows longer with each food item eaten
- Game over when the snake collides with itself or the borders of the screen
- Displays the current score and high score
- Playable on the console with ncurses for visual display
- Support for all physical buttons on the console:
- Start new game - Enter
- Pause - ‘p’
- End game - Esc
- Move left - Left arrow
- Move right - Right arrow
- Move up - Up arrow
- Move down - Down arrow
- Dynamic game speed, which increases as the snake grows longer
- High score tracking and persistent storage between game sessions
- Simple interface with a grid-based display where the snake and food are shown
 
  
### Score Calculation

-	Each food item eaten increases the score by 1 point.
-	The snake grows by 1 unit for each food item eaten.

### High Score Tracking

- Display of the player's current score and highest score achieved
- Highest score is stored in a file or embedded database and persists between
game sessions
 
### Level Progression

- Progression of levels every 5 points
- Increasing level increases the speed of tetromino falling
- Max level 10
- Max Score 200
 
## Installation

1. Clone the repository.
2. Navigate to the `src/` directory.
3. To install the project run `make install`
4. To start playing run `make run`
 
 
## Usage
 
- Use the arrow keys to move and rotate tetrominoes.
- Press the arrow key to make Snake faster.




# BrickGame v1.0 aka Tetris
 
## Introduction
  BrickGame v1.0 is a console-based Tetris game developed in C using the
ncurses library. It features classic Tetris gameplay with additional mechanics
such as score counting, level progression, and high score tracking.
	![game](game.png)
 
## Features
 - Classic Tetris gameplay with the following mechanics:
    - Rotation of tetrominoes
    - Horizontal movement of tetrominoes
    - Accelerated tetromino falling (by holding the down arrow key)
    - Display of the next tetromino
    - Line clearing
    - Game over when the tetromino reaches the top of the game field
 - Support for all physical buttons on the console:
    - Start new game - Enter
    - Pause - 'p'
    - End game - Esc
    - Move left -  Left arrow
    - Move right -  Right arrow
    - Move down - Down arrow
    - Rotate - Space
 - Matrix-based game field with dimensions corresponding to the console's size
(10x20 pixels)
 - Proper stopping of tetrominoes after reaching the bottom or colliding with
another tetromino
 - Unit tests for the game logic library, achieving at least 90% code coverage
 
  
## Additional mechanics
 
### Score Calculation

- 1 line cleared: 100 points
- 2 lines cleared: 300 points
- 3 lines cleared: 700 points
- 4 lines cleared: 1500 points

### High Score Tracking

- Display of the player's current score and highest score achieved
- Highest score is stored in a file or embedded database and persists between
game sessions
 
### Level Progression

- Progression of levels every 600 points
- Increasing level increases the speed of tetromino falling
 
## Installation

1. Clone the repository.
2. Navigate to the `src/` directory.
3. To install the project run `make install`
4. To start playing run `make run`
 
 
## Usage
 
- Use the arrow keys to move and rotate tetrominoes.
- Press the down arrow key to make tetrominoes fall faster.
- Press the up arrow key to rotate tetrominoes.
 
## Fsm Finite State Machine (FSM) Diagram
  A diagram showing the FSM used in the game logic.
	![FSM](fsm.png)
