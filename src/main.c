#include "board.h"
#include "scoreboard.h"
#include <stdio.h>
#include "game.h"
// TODO:
//  - wypisywanie planszy w terminalu, nowa plansza co ruch (kolory pol dodatkowo)
////  - czytanie ruchow gracza (funkcje do odsłaniania pola i stawiania flagi sa) +
//// - pokazywanie wyniki (co ruch i tabela na koncu, sa funkcje do tego) +
// - testy działania całej aplikacji i ważniejszych funkcjonalności
// - wczytywanie planszy i ruchow z pliku (getopt)

int main()
{
    game_start();

    display_scoreboard();

    return 0;
}