#include <stdio.h>
#include <string.h>

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    char buffer[1024] = {0};
    char *winning_ptr, *have_ptr;
    int total = 0;
    while(fgets(buffer, 1024, fp)){
        //printf("%s\n", buffer);
        int game_score = 0;
        winning_ptr = strchr(buffer, ':') + 1;
        while(!(*winning_ptr >= '0' && *winning_ptr <= '9')){
            winning_ptr++;
        }
        int winning;
        while(winning_ptr && sscanf(winning_ptr, "%d", &winning) == 1){
            //printf("%d ", winning);
            have_ptr = strchr(buffer, '|') + 1;
            while(!(*have_ptr >= '0' && *have_ptr <= '9')){
                have_ptr++;
            }
            int have;
            while(have_ptr && sscanf(have_ptr, "%d", &have) == 1){
                //printf("Checking pair %d and %d.\t", winning, have);
                if(winning == have) {
                    printf("Checking pair %d and %d.\t", winning, have);
                    game_score++;
                    printf("Score!\n");
                }
                //printf("\n");
                while(!(*have_ptr >= '0' && *have_ptr <= '9')){
                    have_ptr++;
                }
                have_ptr = strchr(have_ptr, ' ');
                if(!have_ptr) break;
                have_ptr++;
            }
            while(!(*winning_ptr >= '0' && *winning_ptr <= '9')){
                winning_ptr++;
            }
            winning_ptr = strchr(winning_ptr, ' ') + 1;
        }
        printf("Game score: %d\n", game_score == 0 ? 0 : 1 << (game_score - 1));
        total += game_score == 0 ? 0 : 1 << (game_score - 1);
    }
    printf("TOTAL = %d\n", total);
    fclose(fp);
    return 0;
}
