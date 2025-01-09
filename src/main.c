#include <stdio.h>
#include <unistd.h>
#include "./include/game.h"
#include "./include/scoreboard.h"
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