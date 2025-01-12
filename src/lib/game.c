#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/game.h"
#include "../include/board.h"

void test(char* filename){

    FILE *in = fopen(filename, "r");

    char buffer[256];

    int number_of_mines = 0;
    int number_of_columns = 0;
    int number_of_rows = 0;
    int number_of_tiles = 0;
    
    int mine_array[50][50]; 
    int arr_counter = -1;
    

    //read from file, number of colums, rows and mines marked as (1)



    while (fgets(buffer, sizeof(buffer), in)){
        arr_counter =0;
        if(buffer[0]!='1' && buffer[0]!='0'){
            break;
        }


        for(int i = 0; buffer[i]!= '\0'; i++){
            if(!isspace((unsigned char)buffer[i])){
                number_of_tiles++;
                arr_counter++;
            }
            if(buffer[i] == '1'){
                number_of_mines++;
                mine_array[number_of_rows][arr_counter-1] = 1;
            }
        }
        number_of_rows++;
    }
    number_of_columns = number_of_tiles/number_of_rows;


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
            printf("Niestandardowy poziom trudnosci\n");
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

    calculate_mine_counts(&board);

    char action;
    int row, col, status;

    rewind(in);
    int correct_moves = 0;
    int incorrect_moves = 0;
    int is_win = 0;
    int counter=0;
    while(fgets(buffer, sizeof(buffer), in)!= NULL){
        counter++;
        if(counter<=number_of_rows){
            continue;
            
        }
        printf("\e[1;1H\e[2J");

        print_board(&board);
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
            incorrect_moves++;
            continue;
        }
        

        if (status == STATUS_WIN) 
        {   
            print_board(&board);
            print_board_end(&board);
            printf("Wygrałeś grę!\n");
            is_win=1;
            
            break; 
        } 
        else if (status == STATUS_LOSS) 
        {
            print_board(&board);
            print_board_end(&board);
            printf("Przegrałeś!\n");
      
            break; 
        } 
        else if (status == STATUS_ERROR) 
        {
            incorrect_moves++;
        }else{
            correct_moves++;
        }

    }
    printf("---Podsumowanie testu---\n");
    printf("Poprawne ruchy: %d\n", correct_moves);
    printf("Niepoprawne ruchy: %d\n", incorrect_moves);
    printf("Wygrana %d\n", is_win);

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
        print_board_end(board);
        printf("Wygrałeś grę!\n");
        char name[50];
        printf("Podaj swoje imie: ");
        scanf("%s", &name);
        add_score(name, calculate_points(board));
        return; 
    } 
    else if (status == STATUS_LOSS) 
    {
        print_board_end(board);
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
    printf("1 - latwy\n2 - sredni\n3 - trudny\n0 - wlasny\n");
    scanf("%d", &difficulty);

    Board board = init_board(difficulty);
    print_board(&board);

   
    

    
    int is_within_bounds = 1;
    while(is_within_bounds){
        printf("Odkryj pierwsze pole: ");
        scanf("%d %d", &row, &col);

        if(!(row > board.rows || col > board.cols)){
            is_within_bounds=0;
        }else{
            printf("Pole poza planszą\n");
        }

    }
    

    printf("row: %d, col: %d\n", row, col);
    row--;
    col--;

    mine_board(&board, row, col);
    reveal_field(&board, row, col);

    get_user_input(&board);
}