#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *fp = fopen("input_part2.txt", "r");
    char buffer[512] = {0}, *aux;
    int total = 0;
    while(fgets(buffer, 512, fp)){
        int game_id;
        sscanf(buffer, "Game %d", &game_id);
        aux = strchr(buffer, ':') + 2;
        int n, max_red = 0, max_green = 0, max_blue = 0;
        char word[6] = {0};
        while(sscanf(aux, "%d %s", &n, word) == 2){
            //printf("%d %s\n", n, word);
            if(word[0] == 'r'){
                if(n > max_red){
                    max_red = n;
                }
            }
            if(word[0] == 'g'){
                if(n > max_green){
                    max_green = n;
                }
            }
            if(word[0] == 'b'){
                if(n > max_blue){
                    max_blue = n;
                }
            }
            aux = strchr(aux, word[strlen(word) - 1]) + 2;
        }    
        total += max_red * max_green * max_blue;
    }
    printf("Total = %d\n", total);
    fclose(fp);
    return 0;
}
