#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    char buffer[512] = {0}, *aux;
    int total = 0;
    while(fgets(buffer, 512, fp)){
        int game_id;
        sscanf(buffer, "Game %d", &game_id);
        aux = strchr(buffer, ':') + 2;
        int n, valid = 1;
        char word[6] = {0};
        while(sscanf(aux, "%d %s;", &n, word) == 2){
            //printf("%d %s\n", n, word);
            if(word[0] == 'r'){
                if(n > MAX_RED){
                    valid = 0;
                    break;
                }
            }
            if(word[0] == 'g'){
                if(n > MAX_GREEN){
                    valid = 0;
                    break;
                }
            }
            if(word[0] == 'b'){
                if(n > MAX_BLUE){
                    valid = 0;
                    break;
                }
            }
            aux = strchr(aux, word[strlen(word) - 1]) + 2;
        }    
        if(valid != 0) total += game_id;
    }
    printf("Total = %d\n", total);
    fclose(fp);
    return 0;
}
