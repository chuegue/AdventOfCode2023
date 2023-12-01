#include <stdio.h>
#include <string.h>
int main(){
    FILE *fp = fopen("input_day1_part1.txt", "r");
    char buffer[256] = {0};
    int total = 0;
    while(fgets(buffer, 256, fp)){
        int first = 0, second = 0;
        for(int i = 0; i < strlen(buffer); i++){
            if(buffer[i] <= '9' && buffer[i] >= '0'){
                first = buffer[i] - '0'; break;
            }
        }
        for(int i = strlen(buffer) - 1; i >= 0; i--){
            if(buffer[i] <= '9' && buffer[i] >= '0'){
                second = buffer[i] - '0'; break;
            }
        }
        total += (first*10) + second;
    }
    printf("Total: %d\n", total);
    fclose(fp);
}
