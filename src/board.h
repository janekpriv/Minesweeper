#ifndef BOARD_H
#define BOARD_H

#define STATUS_OK 1
#define STATUS_LOSS -1
#define STATUS_WIN 2
#define STATUS_ERROR 0

typedef struct
{
  /**
    1: Easy
    2: Medium
    3: Hard
  4: Custom
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
 * @param difficulty - Game difficulty level
 * @return Initialized Board object
 */
Board init_board(int difficulty);

/**
 * Places mines randomly, ensuring the first move is safe.
 * @param board - Pointer to the Board structure
 * @param start_row - Row of the initial player's move
 * @param start_col - Column of the initial player's move
 */
void mine_board(Board *board, int start_row, int start_col);

/**
 * Prints the player's view of the board.
 * Displays hidden fields, opened fields, and flags.
 * @param board - Pointer to the Board structure
 */
void print_board(const Board *board);

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
 * @return STATUS_LOSS if a mine is revealed, STATUS_OK otherwise
 */
int reveal_field(const Board *board, int row, int col);

/**
 * Places or removes a flag at the specified position.
 * Flags cannot exceed the total number of mines.
 * @param board - Pointer to the Board structure
 * @param row - Row of the field to flag
 * @param col - Column of the field to flag
 * @return STATUS_OK if successful, STATUS_ERROR if invalid, or STATUS_WIN if the player wins by placing all flags correctly
 */
int place_flag(Board *board, int row, int col);

/**
 * Calculates the player's score based on revealed fields and game difficulty.
 * @param board - Pointer to the Board structure
 * @return Calculated score
 */
int calculate_points(const Board *board);

/**
 * Sets the message to be displayed with on top of the board.
 * @param msg - Message to display
 */
void set_message(const char* msg);


#endif // BOARD_H
