#include "scoreboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
* Reads the scores from the file and stores them in the scores array.
*/
static int load_scores(Score scores[], const char *filename) {
    FILE *file = fopen(filename, "r");
    int count = 0;

    if (file != NULL) {
        // Read until the end of the file or the maximum number of scores
        // The format string "%49s (ensure name is no longer than 49chars) %d" reads a string and an integer from each line
        // Equals 2 if both values are read successfully
        while (fscanf(file, "%49s %d", scores[count].name, &scores[count].score) == 2 && count < MAX_SCORES) {
            count++;
        }
        fclose(file);
    }
    return count;
}

/**
* Compares two scores for sorting.
*/
static int comp(const void *a, const void *b) {
    const Score *scoreA = (const Score *)a;
    const Score *scoreB = (const Score *)b;

    // Sortuj malejąco według punktów
    return scoreB->score - scoreA->score;
}

/**
* Sorts the scores in descending order.
*/
static void sort_scores(Score scores[], int count) {
    qsort(scores, count, sizeof(Score), comp);
}

/**
* Saves the scores to the file.
*/
static void save_scores(Score scores[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Nie można otworzyć pliku do zapisu");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
    }
    fclose(file);
}


int add_score(const char *name, int score) {
  	// Use MAX_SCORES + 1 to temporarily hold the new score along with existing scores.
	// This allows sorting and trimming the list to the top MAX_SCORES before saving.
    Score scores[MAX_SCORES + 1];
    int count;

    count = load_scores(scores, SCOREBOARD_FILE);

    strcpy(scores[count].name, name);
    scores[count].score = score;
    count++;

    sort_scores(scores, count);

    // Trim the list to the top MAX_SCORES
    if (count > MAX_SCORES) {
        count = MAX_SCORES;
    }

    save_scores(scores, count, SCOREBOARD_FILE);

    return 1;
}


void display_scoreboard() {
    FILE *file = fopen(SCOREBOARD_FILE, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku tablicy wyników");
        return;
    }

    Score scores[MAX_SCORES];
    int count = 0;

    while (fscanf(file, "%49s %d", scores[count].name, &scores[count].score) == 2 && count < MAX_SCORES) {
        count++;
    }
    fclose(file);

    printf("=== Tablica wyników ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }
}