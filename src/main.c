#include "board.h"
#include <stdio.h>

int main() {
    Board board;
    board.difficulty = 1;
    board.rows = 10;
    board.cols = 10;
    board.num_mines = 10;
    board.placed_flags = 0;

    // Generate the board with a safe starting point at (0, 0)
    set_up_board(&board, 0, 0);

    // Print the generated board
    print_board(&board);
    printf("---------------------\n");
    print_minefield(&board);

    reveal_field(&board, 0, 0);

    print_board(&board);
    printf("---------------------\n");
    print_minefield(&board);



    return 0;
}