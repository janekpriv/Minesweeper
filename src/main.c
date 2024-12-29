#include "board.h"
#include <stdio.h>

int main() {


    // Generate the board with a safe starting point at (0, 0)
    Board board = set_up_board(3, 0, 0);

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