#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int find_next(tokens *tokens, char *next){
    for(int i = 2; i < tokens->n_lines; i++){
        if(strcmp(next, tokens->tokens[i][0]) == 0){
            return i;
        }
    }
    return 0;

}

int main(int argc, char **argv){
    if(argc == 1){
        printf("Ficheiro burro\n\n");
        return 1;
    }
    tokens *tokens = parse_file(argv[1]);
    //print_tokens(tokens);
    for(int i = 2; i < tokens->n_lines; i++){
        memcpy(tokens->tokens[i][2], tokens->tokens[i][2] + 1, 3*sizeof(char));
        tokens->tokens[i][2][3] = '\0';
        tokens->tokens[i][3][3] = '\0';
    }
    print_tokens(tokens);
    char *directions = tokens->tokens[0][0];
    int dir_ind = 0, current = find_next(tokens, "AAA"), next = find_next(tokens, "AAA");
    char target[4] = "ZZZ";
    char *next_str = "AAA";
    char *current_str = "AAA";
    int total = 0;
    while(strcmp(current_str, target) != 0){
        total++;
        printf("This step: %s\n", current_str);
        current = next;
        current_str = next_str;
        next_str = directions[dir_ind] == 'L' ? tokens->tokens[current][2] : tokens->tokens[current][3];
        dir_ind = (dir_ind + 1) % strlen(directions);
        next = find_next(tokens, next_str);
        if(next == 0){
            printf("DEU MERDA FAMILIA\n");
            return 1;
        }
    }
    printf("This step: %s\n", current_str);
    printf("TOTAL STEPS = %d\n", total - 1);
    free_tokens(tokens);
}
