#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/game.h"
#include "../include/board.h"

// -f <plik> 

void test(char* filename){
    // FILE *in = fopen(in, "r");

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
    

    

    // while(counter>row_count){
    //     fgets(board_line, sizeof(board_line), in);

    // }
    // while(fgets(moves_line, sizeof(moves_line), in)){

    // }


    FILE *in = fopen(filename, "r");

    char buffer[256];

    int number_of_mines = 0;
    int number_of_columns = 0;
    int number_of_rows = 0;
    
    int mine_array[50][50]; 
    int arr_counter = -1;
    

    //read from file, number of colums, rows and mines marked as (1)

    while (fgets(buffer, sizeof(buffer), in)){
        if(buffer[0]!=1 || buffer[0]!=0){
            break;
        }


        for(int i = 0; buffer[i]!= '\0'; i++){
            if(!isspace((unsigned char)buffer[i])){
                number_of_columns++;
                arr_counter++;
            }
            if(buffer[i] == '1'){
                number_of_mines++;
                mine_array[number_of_rows][arr_counter] = 1;
            }
        }
        number_of_rows++;
    }


    // decide if board in loaded file has predefinded difficulty  
    int difficulty;
    switch (number_of_rows){
        case 9:
            if(number_of_columns== 9 && number_of_mines == 10){
                difficulty = 1;
            }
            break;
        case 16:
            if(number_of_columns==16 && number_of_mines == 40){
                difficulty = 2;
            }else if(number_of_columns==30 && number_of_mines==99){
                difficulty = 3;
            }
            break;
        default:
            printf("Nie standardowy poziom trudnosci\n");
            difficulty = 5;
    }   

    Board board = init_board_test(difficulty, number_of_rows, number_of_columns, number_of_mines);

    //load mines to board
    for(int i = 0; i<number_of_rows+1; i++){
        for(int j = 0; j<number_of_columns+1; j++){
            if(mine_array[i][j]==1){
                board.minefield[i][j] = -1;
            }
        }
    }

    char *action;
    int row, col, status;


    while(fgets(buffer, sizeof(buffer), in)!= -1){

        sscanf(buffer, " %c %d %d", &action, &row, &col);
        row--;
        col--;

        if (action == 'r') 
        {
            status = reveal_field(&board, row, col);
        } 
        else if (action == 'f') 
        {
            status = place_flag(&board, row, col);
        } 
        else 
        {
            printf("Nieprawidłowa akcja\n");
            printf("Napraw plik i spróbuj ponownie");
            break;
        }

        if (status == STATUS_WIN) 
        {
            printf("Wygrałeś grę!\n");
            printf("Twoj wynik to: %d\n", calculate_points(&board));
            return; 
        } 
        else if (status == STATUS_LOSS) 
        {
            printf("Przegrałeś!\n");
            printf("Twoj wynik to: %d\n", calculate_points(&board));
            return; 
        } 
        else if (status == STATUS_ERROR) 
        {
            printf("Nie można wykonać tej akcji. Błąd w pliku\n");
            printf("Napraw plik i spróbuj ponownie");
            return;
        }

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
        char name[50];
        printf("Podaj swoje imie: ");
        scanf("%s", &name);
        add_score(name, calculate_points(board));
        return; 
    } 
    else if (status == STATUS_LOSS) 
    {
        printf("Przegrałeś!\n");
        char name[50];
        printf("Podaj swoje imie: ");
        scanf("%s", &name);
        add_score(name, calculate_points(board));
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