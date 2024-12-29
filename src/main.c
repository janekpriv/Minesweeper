#include<stdlib.h>
#include<stdio.h>

#include "scoreboard.h"
#include "hashtable.h"



int main(int argc, char** argv){

    double score;
    char* nickname = malloc(30*sizeof(char)); //dynamiczna alokacja do scanf
    int maxPlayers = 10;

    FILE *in = fopen("scoreboard.txt","r");
    if(in==NULL){
        fprintf(stderr, "Nie udało się otworzyć pliku");
        return 1;
    }
    //pobieranie od uzytkownika nazwy
    printf("Podaj swoj nick\n"); 
    scanf("%s",nickname);

    HashTable* table = createHashTable(maxPlayers);
    printf("wygernerowano hashtablice");

     //renderowanie planszy


    score = 129; //tymczasowo testowo

    //po otrzymaniu wyniku gracza
    
    results *result = createResults(nickname, score);
    printf("1\n");
    updateScoreboard(result);
    printf("2\n");
    LoadResults(table);
    printf("3\n");
    sortResults(table);
    printf("4\n");
    results** resultList = sortResults(table);
    printf("6\n");
    printResults(resultList);
    printf("zakonczyl dzialanie");

   




    return 0;
}