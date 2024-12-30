#ifndef LIST_H
#define LIST_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "hashtable.h"

int loadResults(results ***resultList);
int comp(const void *a, const void *b);
void SortResults(results ***resultList, int count);
int PrintResults(results **resultList, int count, results *results);
void UpdateScoreboard(results *player);

#endif