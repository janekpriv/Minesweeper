#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct results{

    char* nickname;
    double score;

} results;

typedef struct HashTable{
    results** items;
    int size;
    int count;
} HashTable;

int hashfunction(char* str);
results* createResults(char* nickname, char* score);
HashTable* createHashTable(int size);
char* searchHashTable(HashTable* table, char* key);





#endif