#include"scoreboard.h"
#include"hashtable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int comp(const void *a, const void *b){
    return (*(int *)b - *(int *)a);
}

HashTable* LoadResults(HashTable *table){
    char buffer[1000];
    //int counter = 0;
    FILE *in = fopen("scoreboard.txt","r");
    if(in==NULL){
        fprintf(stderr, "Nie udało się otworzyć pliku");
        return NULL;
    }
    while(fgets(buffer, sizeof(buffer), in)){
        char *nickname = strtok(buffer, ",");
        double score = atof(strtok(NULL, ","));
        results *result = createResults(nickname, score); 
        AddToTable(table, result);
    }
    fclose(in);
    return table;
}
results **sortResults(HashTable *table){
    int count = table->count;
    results **resultList = malloc(sizeof(results)*count);
    for(int i = 0; i<count; i++){
        resultList[i] = table->items[i];
    }
    qsort(resultList, count, sizeof(results), comp);

    return resultList;
}
void printResults(results **resultList){
    for(int i=0; i<5; i++){
        double score = resultList[i]->score;
        char* nickname = resultList[i]->nickname;
        printf("%d. %s wynik: %g\n", i, nickname, score);
    }
}

void updateScoreboard(results *player){
    printf("updatescore\n");
    FILE *in = fopen("scoreboard.txt", "a");
    if(in==NULL){
        printf("Nie udało się otworzyć pliku");
        return;
    }
    fprintf(in,"%s,%g\n",player->nickname, player->score);
    fclose(in);
    
}