#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * Constructs the Board object with parameters based on difficulty.
 * Prompts the user for input if a custom difficulty is selected.
 * @param difficulty - Game difficulty level
 * @return Initialized Board object
 */
Board construct_board(int difficulty){
	Board board;
    board.difficulty = difficulty;
    switch (difficulty) {
        case 0:
            board.rows = 9;
            board.cols = 9;
            board.num_mines = 10;
            break;
        case 1:
            board.rows = 16;
            board.cols = 16;
            board.num_mines = 40;
            break;
        case 2:
            board.rows = 16;
            board.cols = 30;
            board.num_mines = 99;
            break;
        case 3:
            printf("Podaj ilość wierszy: ");
            scanf("%d", &board.rows);
            printf("Podaj ilość kolumn: ");
            scanf("%d", &board.cols);
            printf("Podaj ilość min: ");
            scanf("%d", &board.num_mines);
            if(board.num_mines >= board.rows * board.cols){
                printf("Za dużo min\n");
                exit(1);
            }
            break;
        default:
            printf("Niepoprawny poziom trudności\n");
            exit(1);
    }
    board.placed_flags = 0;
    return board;
}

/**
 * Allocates memory for the minefield and player view arrays.
 * Initializes all fields to their default state.
 * @param board - Pointer to the Board structure
 */
void initialize_board_fields(Board *board) {
    board->minefield = (int **)malloc(board->rows * sizeof(int *));
    for (int i = 0; i < board->rows; i++) {
        board->minefield[i] = (int *)malloc(board->cols * sizeof(int));
    }

    board->player_view = (int **)malloc(board->rows * sizeof(int *));
    for (int i = 0; i < board->rows; i++) {
        board->player_view[i] = (int *)malloc(board->cols * sizeof(int));
    }
}


void place_mines(Board *board, int start_row, int start_col) {

    // Place mines randomly, ensuring the first move is safe
    srand(time(NULL));
    int mines_placed = 0;
    while (mines_placed < board->num_mines) {
        int row = rand() % board->rows;
        int col = rand() % board->cols;

        // Ensure the mine is not placed at the starting point or already has a mine
        if ((row == start_row && col == start_col) || board->minefield[row][col] == -1) {
            continue;
        }

        board->minefield[row][col] = -1; // Place a mine
        mines_placed++;

    }
}

/**
 * Calculates the number of mines in the vicinity of each field.
 * Updates the minefield with the corresponding counts.
 * @param board - Pointer to the Board structure
 */
void calculate_mine_counts(Board *board) {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->minefield[i][j] == -1) {
                continue; // Skip mines
            }

            int mine_count = 0;
            for (int k = 0; k < 8; k++) {
                int row_offset = i + directions[k][0];
                int col_offset = j + directions[k][1];

                if (
                    row_offset >= 0 && row_offset < board->rows
                    && col_offset >= 0 && col_offset < board->cols
                    && board->minefield[row_offset][col_offset] == -1
                    ){
                    	mine_count++;
                }
            }

            board->minefield[i][j] = mine_count;
        }
    }
}


Board set_up_board(int difficulty, int start_row, int start_col) {
  	Board board = construct_board(difficulty);
    initialize_board_fields(&board);
    place_mines(&board, start_row, start_col);
    calculate_mine_counts(&board);
    return board;
}

void print_board(const Board *board) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            printf("[");
            if (board->player_view[i][j] == 0) {
                printf("?");
            } else if (board->player_view[i][j] == 1) {
                printf("%d", board->minefield[i][j]);
            } else if (board->player_view[i][j] == 2) {
                printf("F");
            }
            printf("] ");
        }
        printf("\n");
    }
}

void print_minefield(const Board *board) {
    // Print the board
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            printf("%d ", board->minefield[i][j]);
        }
        printf("\n");
    }
}

/**
 * Checks if a given position is within the bounds of the board.
 * @param board - Pointer to the Board structure
 * @param row - Row index
 * @param col - Column index
 * @return 1 if within bounds, 0 otherwise
 */
int is_within_bounds(const Board *board, int row, int col) {
    return row >= 0 && row < board->rows && col >= 0 && col < board->cols;
}


/**
 * Recursively reveals fields on the board.
 * Stops revealing if a field has a mine count greater than 0.
 * @param board - Pointer to the Board structure
 * @param row - Row of the field to reveal
 * @param col - Column of the field to reveal
 */
void recursive_reveal(const Board *board, int row, int col){
  	if(!is_within_bounds(board, row, col)) return;
	if(board->player_view[row][col] == 1) return;

    board->player_view[row][col] = 1;
    if (board->minefield[row][col] > 0) return;

  	for (int row_offset = -1; row_offset <= 1; row_offset++) {
        for (int col_offset = -1; col_offset <= 1; col_offset++) {
            // Skip the current field
            if (row_offset == 0 && col_offset == 0) {
                continue;
            }
            reveal_field(board, row + row_offset, col + col_offset);
        }
    }
}



int reveal_field(const Board *board, int row, int col){
  	if(!is_within_bounds(board, row, col)) return 0;
    if(board->player_view[row][col] == 1) return 0;
    if(board->minefield[row][col] == -1) return -1;

    recursive_reveal(board, row, col);
    return 1;
}

//TODO: determine returns for diffrent cases
/*
* Function to check if the player has won the game
* Returns 2 if the player has won, 0 otherwise
* Checks if all the mines have been flagged
 */
int check_win(const Board *board){
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->minefield[i][j] == -1 && board->player_view[i][j] !=2) {
                return 0;
            }
        }
    }
    return 2;
}


int place_flag(Board *board, int row, int col){
  	if(!is_within_bounds(board, row, col)) return 0;
    if(board->player_view[row][col] == 1) return 0;
    if(board->placed_flags == board->num_mines && board->player_view[row][col] != 2) return 0;

    if(board->player_view[row][col] == 2){
        board->player_view[row][col] = 0;
    } else {
        board->player_view[row][col] = 2;
        board->placed_flags++;
    }
    if(board->placed_flags == board->num_mines){
        return check_win(board);
    }
    return 1;
}


int calculate_points(const Board *board){
    int points = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->player_view[i][j] == 1) {
                points++;
            }
        }
    }
    return points * board->difficulty;
}
//TODO: implement revealing all fields if player wins, to calculate the final score