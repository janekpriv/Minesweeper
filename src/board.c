#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_BLUE "\x1b[34m" 
#define ANSI_GREEN "\x1b[32m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_MAGENTA "\x1b[35m" 
#define ANSI_BLUE "\x1b[34m" 
#define ANSI_GREEN "\x1b[32m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_MAGENTA "\x1b[35m" 
#define ANSI_COLOR_RESET "\x1b[0m"
char message[256];





/**
 * Constructs the Board object with parameters based on difficulty.
 * Prompts the user for input if a custom difficulty is selected.
 * @param difficulty - Game difficulty level
 * @return Initialized Board object
 */
static Board construct_board(int difficulty)
{
    Board board;
    board.difficulty = difficulty;
    switch (difficulty)
    {
    case 1:
        board.rows = 9;
        board.cols = 9;
        board.num_mines = 10;
        break;
    case 2:
        board.rows = 16;
        board.cols = 16;
        board.num_mines = 40;
        break;
    case 3:
        board.rows = 16;
        board.cols = 30;
        board.num_mines = 99;
        break;
    case 0:
        printf("Podaj ilość wierszy: ");
        scanf("%d", &board.rows);
        printf("Podaj ilość kolumn: ");
        scanf("%d", &board.cols);
        printf("Podaj ilość min: ");
        scanf("%d", &board.num_mines);
        if (board.num_mines >= board.rows * board.cols)
        {
            printf("Za dużo min\n");
            exit(1);
        }
        break;
    default:
        printf("Niepoprawny poziom trudności\n");
        exit(1);
    }
    board.placed_flags = 0;
    return board;
}

/**
 * Allocates memory for the minefield and player view arrays.
 * Initializes all fields to their default state.
 * @param board - Pointer to the Board structure
 */
static void initialize_board_fields(Board *board)
{
    board->minefield = (int **)malloc(board->rows * sizeof(int *));
    for (int i = 0; i < board->rows; i++)
    {
        board->minefield[i] = (int *)malloc(board->cols * sizeof(int));
    }

    board->player_view = (int **)malloc(board->rows * sizeof(int *));
    for (int i = 0; i < board->rows; i++)
    {
        board->player_view[i] = (int *)malloc(board->cols * sizeof(int));
    }
}

static void place_mines(Board *board, int start_row, int start_col)
{

    // Place mines randomly, ensuring the first move is safe
    srand(time(NULL));
    int mines_placed = 0;
    while (mines_placed < board->num_mines)
    {
        int row = rand() % board->rows;
        int col = rand() % board->cols;

        // Ensure the mine is not placed at the starting point or already has a mine
        if ((row == start_row && col == start_col) || board->minefield[row][col] == -1)
        {
            continue;
        }

        board->minefield[row][col] = -1; // Place a mine
        mines_placed++;
    }
}

/**
 * Calculates the number of mines in the vicinity of each field.
 * Updates the minefield with the corresponding counts.
 * @param board - Pointer to the Board structure
 */
static void calculate_mine_counts(Board *board)
{
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->minefield[i][j] == -1)
            {
                continue; // Skip mines
            }

            int mine_count = 0;
            for (int k = 0; k < 8; k++)
            {
                int row_offset = i + directions[k][0];
                int col_offset = j + directions[k][1];

                if (
                    row_offset >= 0 && row_offset < board->rows && col_offset >= 0 && col_offset < board->cols && board->minefield[row_offset][col_offset] == -1)
                {
                    mine_count++;
                }
            }

            board->minefield[i][j] = mine_count;
        }
    }
}

Board init_board(int difficulty)
{
    Board board = construct_board(difficulty);
    initialize_board_fields(&board);
    return board;
}

void mine_board(Board *board, int start_row, int start_col)
{
    place_mines(board, start_row, start_col);
    calculate_mine_counts(board);
}

//based on number of mines near particular field color is updated

void color_print(const Board *board, int row, int col){
    if(board->minefield[row][col]==1){
        print(ANSI_BLUE "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==2){
    print(ANSI_GREEN "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==3){
    print(ANSI_MAGENTA "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==3){
    print(ANSI_CYAN "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
}

//based on number of mines near particular field color is updated

void color_print(const Board *board, int row, int col){
    if(board->minefield[row][col]==1){
        print(ANSI_BLUE "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==2){
    print(ANSI_GREEN "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==3){
    print(ANSI_MAGENTA "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
    if(board->minefield[row][col]==3){
    print(ANSI_CYAN "%d" ANSI_COLOR_RESET,board->minefield[row][col]);
    }
}


void print_board(const Board *board)
{
    printf("%s\n", message);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            printf("[");
            if (board->player_view[i][j] == 0)
            {
                printf("?");
            }
            else if (board->player_view[i][j] == 1)
            {
                color_print(board, i, j);
                
            }
            else if (board->player_view[i][j] == 2)
            {
                printf(ANSI_COLOR_RED "F" ANSI_COLOR_RESET);
            }
            printf("] ");
        }
        printf("\n");
    }
}

void print_minefield(const Board *board)
{
    // Print the board
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            printf("%d ", board->minefield[i][j]);
        }
        printf("\n");
    }
}

/**
 * Checks if a given position is within the bounds of the board.
 * @param board - Pointer to the Board structure
 * @param row - Row index
 * @param col - Column index
 * @return STATUS_OK< if within bounds, STATUS_ERROR otherwise
 */
static int is_within_bounds(const Board *board, int row, int col)
{
    if( row >= 0 && row < board->rows && col >= 0 && col < board->cols){
        return STATUS_OK;
    }
    return STATUS_ERROR;
}

/**
 * Recursively reveals fields on the board.
 * Stops revealing if a field has a mine count greater than 0.
 * @param board - Pointer to the Board structure
 * @param row - Row of the field to reveal
 * @param col - Column of the field to reveal
 */
static void recursive_reveal(const Board *board, int row, int col)
{
    if (!is_within_bounds(board, row, col))
        return;
    if (board->player_view[row][col] == 1)
        return;

    board->player_view[row][col] = 1;
    if (board->minefield[row][col] > 0)
        return;

    for (int row_offset = -1; row_offset <= 1; row_offset++)
    {
        for (int col_offset = -1; col_offset <= 1; col_offset++)
        {
            // Skip the current field
            if (row_offset == 0 && col_offset == 0)
            {
                continue;
            }
            recursive_reveal(board, row + row_offset, col + col_offset);
        }
    }
}

int reveal_field(const Board *board, int row, int col)
{
    if (!is_within_bounds(board, row, col)){
        set_message("Pole poza planszą");
        return STATUS_ERROR;
    }
        
    if (board->player_view[row][col] == 1){
        set_message("Pole już odkryte");
        return STATUS_ERROR;
    }
        
    if (board->minefield[row][col] == -1){
        return STATUS_LOSS;
    }

    recursive_reveal(board, row, col);
    set_message("Odkryto pole");
    return STATUS_OK;
}


/**
 * Function to check if the player has won the game
 * Checks if all the mines have been flagged
 * Checks if all the non-mine fields have been revealed
 * @param board - Pointer to the Board structure
 * @return STATUS_WIN if the player has won, STATUS_OK otherwise
 */
static int check_win(const Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->minefield[i][j] == -1 && board->player_view[i][j] != 2)
            {
                return STATUS_OK;
            }
        }
    }

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->minefield[i][j] == -1 && board->player_view[i][j] == 0)
            {
                return STATUS_OK;
            }
        }
    }

    return STATUS_WIN;
}

int place_flag(Board *board, int row, int col)
{
    if (!is_within_bounds(board, row, col)){
        set_message("Pole poza planszą");
        return STATUS_ERROR;
    }
        
    if (board->player_view[row][col] == 1){
        set_message("Nie możesz postawić flagi na odkrytym polu");
        return STATUS_ERROR;
    }
        
    if (board->placed_flags == board->num_mines && board->player_view[row][col] != 2){
        set_message("Nie możesz postawić więcej flag");
        return STATUS_ERROR;
    }
        

    if (board->player_view[row][col] == 2)
    {
        board->player_view[row][col] = 0;
    }
    else
    {
        board->player_view[row][col] = 2;
        board->placed_flags++;
    }
    if (board->placed_flags == board->num_mines)
    {
        return check_win(board);
    }
    set_message("Postawiono flagę");
    return STATUS_OK;
}

int calculate_points(const Board *board)
{
    int points = 0;
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->player_view[i][j] == 1)
            {
                points++;
            }
        }
    }
    return points * board->difficulty;
}

void set_message(const char* msg)
{
    snprintf(message, sizeof(message), "%s", msg);
}

// TODO: implement revealing all fields if player wins, to calculate the final score