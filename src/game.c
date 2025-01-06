#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "board.h"

// -f <plik> row col

void test(char* filename, int row_count, int col_count){

    char board_line[50];
    char moves_line[50];

    char board[50][50];
    // char moves[20][10];


    int counter;

    FILE *in = fopen(in, "r");

    // sprawdzic czy podany rozmiar planszy odpowiada jakiemuś poziomwi trudnosci
    // init board
   

    // for w for (na wiersze i kolumny)
    // w tym inicjujemy plansze
    // sprawdzamy  czy jest mina(-1)

    // ustawic poziom trudnosci w zaleznosci od row_count i col_count i num_mines

    //tu powinnismy byc na linijce z ruchami (pod boardem)
    //jezeli nie mamy to przesuwamy sie w pliku do linijki z ruchami (row_count+1)

    // tu mamy boarda

    //przechodzimy po ruchach 
    //wyrozniamy ruchy z linijki 

    //wywołujemy resztę get_user_input
    

    

    while(counter>row_count){
        fgets(board_line, sizeof(board_line), in);

    }
    while(fgets(moves_line, sizeof(moves_line), in)){

    }

}

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