#ifndef SCOREBOARD_H
#define SCOREBOARD_H


#define MAX_SCORES 100
#define SCOREBOARD_FILE "data/scoreboard.txt"

typedef struct {
  char name[50];
  int score;
} Score;

/**
* Adds a score to the scoreboard.
* @param name - Name of the player
* @param score - Score of the player
*/
void add_score(const char *name, int score);

/**
* Shows the scoreboard.
*/
int display_scoreboard();

#endif // SCOREBOARD_H