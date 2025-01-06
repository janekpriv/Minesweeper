#include "board.h"
#include "scoreboard.h"
#include <stdio.h>
#include <unistd.h>
#include "game.h"
// TODO:
//  - wypisywanie planszy w terminalu, nowa plansza co ruch (kolory pol dodatkowo)
// - testy ważniejszych funkcjonalności
// - wczytywanie planszy i ruchow z pliku (getopt)
// - zapisywanie wynikow do pliku

int main(int argc, char** argv)
{
    



    game_start();



    display_scoreboard();

    return 0;
}