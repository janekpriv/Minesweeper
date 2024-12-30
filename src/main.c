#include<stdlib.h>
#include<stdio.h>

#include "scoreboard.h"
#include "hashtable.h"
#include "list.h"



int main(int argc, char** argv){

    double score;
    char* nickname = malloc(30*sizeof(char)); //dynamiczna alokacja do scanf
    int maxPlayers = 100;

    FILE *in = fopen("scoreboard.txt","r");
    if(in==NULL){
        fprintf(stderr, "Nie udało się otworzyć pliku");
        return 1;
    }
    //pobieranie od uzytkownika nazwy
    printf("Podaj swoj nick\n"); 
    scanf("%s",nickname);

    results **resulsList = malloc(sizeof(results)*maxPlayers);

    //HashTable* table = createHashTable(maxPlayers);
    

     //renderowanie planszy


    score = 129; //tymczasowo testowo

    //po otrzymaniu wyniku gracza
    results *result = createResults(nickname, score);
    UpdateScoreboard(result);
    int counter = loadResults(&resulsList); //zwraca ilosc graczy w pliku  
    loadResults(&resulsList);
    printf("counter: %d\n", counter);
    SortResults(&resulsList, counter);
    int top5 = PrintResults(resulsList, counter, result);
    PrintResults(resulsList, counter, result);
    if(!top5){
        printf("%s, %g\n",result->nickname, result->score);
    }

   




    return 0;
}