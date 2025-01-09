#include <stdio.h>
#include <unistd.h>
#include "./include/game.h"
#include "./include/scoreboard.h"
// TODO:
//  - wypisywanie planszy w terminalu, nowa plansza co ruch (kolory pol dodatkowo)
// - wczytywanie planszy i ruchow z pliku (getopt)

int main(int argc, char** argv)
{
    game_start();
    display_scoreboard();

    return 0;
}