#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include"hashtable.h"
#include<stdio.h>
#include<stdlib.h>



HashTable* LoadResults(FILE *in);
HashTable* sortResults(HashTable* table);




#endif