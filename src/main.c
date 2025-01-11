#include <stdio.h>
#include <unistd.h>
#include "./include/game.h"
#include "./include/scoreboard.h"
// TODO:
//  - wypisywanie planszy w terminalu, nowa plansza co ruch (kolory pol dodatkowo)
// - wczytywanie planszy i ruchow z pliku (getopt)

int main(int argc, char** argv)
{
    int options;
    int f_flag =0;
    int r_flag; // rows
    int c_flag; // columns
    char* file_path = NULL;

    while((options = getopt(argc, argv, "f")) == -1 ){
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

            return 1;
        }
    }

    if(file_path){
        test(file_path);
    }else{
    game_start();
    display_scoreboard();
    }
    return 0;
}
