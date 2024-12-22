#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>

results* createResults(char* nickname, double score){

    results* result = malloc(sizeof(result));
    result->nickname = nickname;
    result->score = score;
    return result;
}

HashTable* createHashTable(int size){

    HashTable* table = malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = malloc(table->size * sizeof(results*));
        for (int i = 0; i < table->size; i++) {
            table->items[i] = NULL;
        }
    return table;
}

void AddToTable(HashTable* table, results* result){
    if(table->size == table->count){
        fprintf(stderr, "tabela jest pełna, nieobsługiwana ilość graczy");
        return;
    }
    table->items[table->count] = result;
    table->count++;
}

char* searchHashTable(HashTable* table, char* key){



}
