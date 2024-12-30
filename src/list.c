#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"hashtable.h"
#include"list.h"

int comp(const void *a, const void *b) {
    results *resultA = *(results **)a;
    results *resultB = *(results **)b;

    if (resultA->score > resultB->score) {
        return -1; // Najpierw większe wyniki
    } else if (resultA->score < resultB->score) {
        return 1;
    } else {
        return 0;
    }
}

int loadResults(results ***resultList){
    char buffer[8192];

    FILE *in = fopen("scoreboard.txt","r");
    if(in==NULL){
        fprintf(stderr, "Nie udało się otworzyć pliku");
        return -1;
    }
    int counter = 0;
    while(fgets(buffer, sizeof(buffer), in)){
        char *nickname = strtok(buffer, ",");
        double score = atof(strtok(NULL, ","));
        results *result = createResults(nickname, score);
        (*resultList)[counter]=result;
        counter++;
    }
    fclose(in);
    printf("loaded\n");
    return counter;
}

void SortResults(results ***resultList, int count){

    qsort(resultList, count, sizeof(results *), comp);
    printf("sortedResults\n");

}

int PrintResults(results **resultList, int counter, results *player){

    int IsInTop5 = 1;

    for(int i = 0; i<counter; i++){
        double score = resultList[i]->score;
        char* nickname = resultList[i]->nickname;
        if(player == resultList[i] && i<5){
            IsInTop5 = 0;
        }

        printf("%d. %s wynik: %g\n", i, nickname, score);
    }
    return IsInTop5;
}

void UpdateScoreboard(results *player){
    FILE *in = fopen("scoreboard.txt", "a");
    if(in==NULL){
        printf("Nie udało się otworzyć pliku");
        return;
    }
    fprintf(in,"%s,%g\n",player->nickname, player->score);
    fclose(in);
}