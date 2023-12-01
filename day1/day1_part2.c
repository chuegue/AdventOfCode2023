#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char numbers[10][6] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main(){
    FILE *fp = fopen("input_day1_part2.txt", "r");
    char buffer[256] = {0};
    int total = 0;
    while(fgets(buffer, 256, fp)){
        int first = -1, second = -1;
        for(int i = 0; i < strlen(buffer); i++){
            if(buffer[i] <= '9' && buffer[i] >= '0'){
                if(first == -1){
                    first = buffer[i] - '0';
                    second = buffer[i] - '0';
                }else{
                    second = buffer[i] - '0';
                }
            }else{ //letter
                for(int j = 0; j < 10; j++){
                    if(strstr(((char *)&buffer[0])+i, numbers[j]) == ((char *)&buffer[0]) + i){
                        if(first == -1){
                            first = second = j;
                        }
                        else{
                            second = j;
                        }
                    }
                }
            }
        }
        total += (first*10) + second;
    }
    printf("Total: %d\n", total);
    fclose(fp);
}
