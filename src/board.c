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
            for (int d = 0; d < 8; d++) {
                int ni = i + directions[d][0];
                int nj = j + directions[d][1];

                if (ni >= 0 && ni < board->rows && nj >= 0 && nj < board->cols && board->minefield[ni][nj] == -1) {
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

void print_board(const Board *board) {
    // Print the player view of the board
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            printf("[ ");
            if (board->player_view[i][j] == 0) {
                printf("?");
            } else if (board->player_view[i][j] == 1) {
                printf("%d", board->minefield[i][j]);
            } else if (board->player_view[i][j] == 2) {
                printf("F");
            }
            printf(" ]");
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
