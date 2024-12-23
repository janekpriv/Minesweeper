#include "board.h"
#include <stdio.h>

int main() {
    Board board;
    board.difficulty = 1;
    board.rows = 5;
    board.cols = 5;
    board.num_mines = 5;
    board.placed_flags = 0;

    // Generate the board with a safe starting point at (0, 0)
    set_up_board(&board, 0, 0);

    // Print the generated board
    print_board(&board);
    printf("---------------------\n");
    print_minefield(&board);



    return 0;
}