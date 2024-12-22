#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct results{

    char* nickname;
    double score;
    //int id;

} results;

typedef struct HashTable{
    results** items;
    int size;
    int count;
} HashTable;

int hashfunction(char* str);
results* createResults(char* nickname, double score);
HashTable* createHashTable(int size);
void AddToTable(HashTable *table, results *result);
char* searchHashTable(HashTable* table, char* key);





#endif