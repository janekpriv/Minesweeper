#ifndef BOARD_H
#define BOARD_H

typedef struct {
  /**
    0: Easy
    1: Medium
    2: Hard
	3: Custom
*/
    int difficulty;
    int rows;
    int cols;
    int num_mines;
    int placed_flags;

    /**
    -1: Mine
    0-8: 0-8 mine in the vicinity
     */
    int **minefield;

    /**
    0: Closed field    `
    1: Opened field
    2: Flag
    */
    int **player_view;
} Board;

// Function to generate the Minesweeper board
Board set_up_board(int difficulty, int start_row, int start_col);

// Function to print the Minesweeper board
void print_board(const Board *board);

// Function to print the minefield for testing purposes
void print_minefield(const Board *board);

// Function to reveal a field on the board
int reveal_field(const Board *board, int row, int col);

// Function to place a flag on the board
int place_flag(Board *board, int row, int col);

// Function to calculate points based on revealed fields and difficulty
int calculate_points(const Board *board);

#endif // BOARD_H
