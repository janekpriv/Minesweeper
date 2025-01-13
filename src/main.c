#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "./include/game.h"
#include "./include/scoreboard.h"

int main(int argc, char** argv)
{
    int options;
    int f_flag =0;
    char* file_path = NULL;

    while((options = getopt(argc, argv, "f:")) != -1 ){
        switch (options)
        {
        case 'f':
            f_flag = 1;
            file_path = optarg;
            break;

        case '?':

            if(optopt == 'f'){
                fprintf(stderr, "Opcja -f wymaga podania sciezki do pliku\n");
            }else{
                fprintf(stderr, "Nieznana opcja -%c\n", optopt);
            }
            return STATUS_ERROR;
        default:
            fprintf(stderr, "Blędna opcja wywołania -%c\n", optopt);
            return STATUS_ERROR;
        }
    }

    if(file_path && f_flag){
        test(file_path);
    }else{
    game_start();
    display_scoreboard();
    }
    return 0;
}
