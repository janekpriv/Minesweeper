#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "board.h"



static void get_user_input(Board *board) 
{
    printf("\e[1;1H\e[2J");

  
    printf("Punkty: %d\n", calculate_points(board));
    print_board(board);

    char action;
    int row, col, status;
    printf("Podaj ruch (f x y lub r x y): ");
    scanf(" %c %d %d", &action, &row, &col);



    


    row--;
    col--;

    
    if (action == 'r') 
    {
        status = reveal_field(board, row, col);
    } 
    else if (action == 'f') 
    {
        status = place_flag(board, row, col);
    } 
    else 
    {
        printf("Nieprawidłowa akcja\n");
    }

    if (status == STATUS_WIN) 
    {
        printf("Wygrałeś grę!\n");
        return; 
    } 
    else if (status == STATUS_LOSS) 
    {
        printf("Przegrałeś!\n");
        return; 
    } 
    else if (status == STATUS_ERROR) 
    {
        printf("Nie można wykonać tej akcji. Spróbuj ponownie.\n");
    }
    get_user_input(board);
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