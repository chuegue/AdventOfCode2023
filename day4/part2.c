#include <stdio.h>
#include <string.h>

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    char buffer[1024] = {0};
    char *winning_ptr, *have_ptr;
    int total = 0;
    char cards[256][1024] = {0}; int ind = 0;
    int how_many[256] = {0};
    while(fgets(buffer, 1024, fp)){
        strcpy(cards[ind], buffer);
        char *sn = strchr(cards[ind], '\n');
        if(sn != NULL) {
            sn = '\0';
        }
        how_many[ind] = 1;
        ind++;
    }
    for(int i = 0; i < ind; i++){
        int game_score = 0;
        winning_ptr = strchr(cards[i], ':') + 1;
        while(!(*winning_ptr >= '0' && *winning_ptr <= '9')){
            winning_ptr++;
        }
        int winning;
        while(winning_ptr && sscanf(winning_ptr, "%d", &winning) == 1){
            //printf("%d ", winning);
            have_ptr = strchr(cards[i], '|') + 1;
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
        for(int a = 0; a < game_score; a++){
            how_many[i + a + 1] += how_many[i];
        }
    }
    for(int i = 0; i < ind; i++) total += how_many[i];
    printf("Total = %d\n", total);
    fclose(fp);
    return 0;
}
