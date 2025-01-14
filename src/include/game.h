#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "scoreboard.h"

/**
 * Initializes the game.
 */
void game_start();

/**
 * Test the game with a file.
 * @param filename - Name of the file to test
 */
void test(char* filename);

#endif // GAME_H