#include"scoreboard.h"
#include"hashtable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int comp(const void *a, const void *b){
    return (*(int *)b - *(int *)a);
}

HashTable* LoadResults(FILE *in, HashTable *table){
    char buffer[1000];
    int counter = 0;
    while(fgets(buffer, sizeof(buffer), in)){
        char *nickname = strtok(buffer, ",");
        double score = atof(strtok(NULL, ","));
        results *result = createResults(nickname, score); 
        AddToTable(table, result);
    }
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
        printf("%d. %s wynik: %g", i, nickname, score);
    }
}