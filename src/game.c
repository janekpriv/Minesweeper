#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "board.h"

static void get_user_input(Board *board)
{
    printf("\e[1;1H\e[2J");
    printf("%d\n", calculate_points(board));
    print_board(board);

    char action;
    int row, col;
    scanf(" %c %d %d", &action, &row, &col);
    row--;
    col--;
    printf("action: %c, row: %d, col: %d\n", action, row, col);

    if (action == 'r')
    {
        printf("revealed\n");
        if (reveal_field(board, col, row) == -1)
        {
            printf("Przegrałeś\n");
        }
        else
        {

            get_user_input(board);
        }
    }
    else if (action == 'f')
    {
        int tmp = place_flag(board, col, row);
        if (tmp != 2)
        {
            get_user_input(board);
        }
    }
    else
    {
        printf("Nie ma takiej akcji\n");
    }
}

void game_start()
{

    int row, col;
    int difficulty;
    printf("Wybierz poziom trudnosci:\n");
    printf("1 - latwy\n 2 - sredni\n 3 - trudny\n0 - wlasny\n");
    scanf("%d", &difficulty);

    Board board = init_board(difficulty);
    print_board(&board);

    printf("Odkryj pierwsze pole: ");

    scanf("%d %d", &row, &col);
    printf("row: %d, col: %d\n", row, col);
    row--;
    col--;

    mine_board(&board, col, row);
    reveal_field(&board, col, row);

    get_user_input(&board);
}