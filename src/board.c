#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


void initialize_board_fields(Board *board) {
    // Initialize the board minefield
    board->minefield = (int **)malloc(board->rows * sizeof(int *));
    for (int i = 0; i < board->rows; i++) {
        board->minefield[i] = (int *)malloc(board->cols * sizeof(int));
    }

    // Initialize the player view
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

// Function to calculate the number of mines around each field
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


void set_up_board(Board *board, int start_row, int start_col) {
    initialize_board_fields(board);
    place_mines(board, start_row, start_col);
    calculate_mine_counts(board);
}

// Print the player view of the board
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
int is_within_bounds(const Board *board, int row, int col) {
    return row >= 0 && row < board->rows && col >= 0 && col < board->cols;
}

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

/*
* Function to check if the player has won the game
* Returns 1 if the player has won, 0 otherwise
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
    return 1;
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