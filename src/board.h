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

/**
 * Sets up the Minesweeper board based on the chosen difficulty.
 * Ensures the starting position is safe and places mines randomly.
 * @param difficulty - Game difficulty level
 * @param start_row - Row of the initial player's move
 * @param start_col - Column of the initial player's move
 * @return Configured Board object
 */
Board set_up_board(int difficulty, int start_row, int start_col);

/**
 * Prints the player's view of the board.
 * Displays hidden fields, opened fields, and flags.
 * @param board - Pointer to the Board structure
 */
void print_board(const Board *board);

//TODO: delete after testing
/**
 * Prints the entire minefield (for testing purposes).
 * Displays the mine positions and mine counts.
 * @param board - Pointer to the Board structure
 */
void print_minefield(const Board *board);

/**
 * Reveals a field on the board.
 * If the field is empty (no mines nearby), it recursively reveals neighboring fields.
 * @param board - Pointer to the Board structure
 * @param row - Row of the field to reveal
 * @param col - Column of the field to reveal
 * @return -1 if a mine is revealed, 1 otherwise
 */
int reveal_field(const Board *board, int row, int col);

/**
 * Places or removes a flag at the specified position.
 * Flags cannot exceed the total number of mines.
 * @param board - Pointer to the Board structure
 * @param row - Row of the field to flag
 * @param col - Column of the field to flag
 * @return 1 if successful, 0 if invalid, or 2 if the player wins by placing all flags correctly
 */
int place_flag(Board *board, int row, int col);

/**
 * Calculates the player's score based on revealed fields and game difficulty.
 * @param board - Pointer to the Board structure
 * @return Calculated score
 */
int calculate_points(const Board *board);

#endif // BOARD_H
