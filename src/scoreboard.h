#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include"hashtable.h"
#include<stdio.h>
#include<stdlib.h>



HashTable* LoadResults(FILE *in);
results **sortResults(HashTable *table);
int comp(const void *a, const void *b);




#endif