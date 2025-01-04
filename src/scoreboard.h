#ifndef SCOREBOARD_H
#define SCOREBOARD_H


#define MAX_SCORES 100
#define SCOREBOARD_FILE "data/scoreboard.txt"

typedef struct {
  char name[50];
  int score;
} Score;

/**
* Loads the scores from the file.
*/
int add_score(const char *name, int score);

/**
* Saves the scores to the file.
*/
void display_scoreboard();

#endif // SCOREBOARD_H