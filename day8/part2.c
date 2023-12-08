#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int find_next(tokens *tokens, char *next_str){
    for(int i = 2; i < tokens->n_lines; i++){
            if(strcmp(next_str, tokens->tokens[i][0]) == 0){
               return i; 
        }
    }
    return 0;
}

int all_zs(tokens *tokens, int *curr, int n_strs){
    for(int i = 0; i < n_strs; i++){
        if(tokens->tokens[curr[i]][0][2] != 'Z') return 0;
    }
    return 1;
}

unsigned long long int gcd(unsigned long long int a, unsigned long long int b)  
{  
    if (a == 0) 
        return b;  
    return gcd(b % a, a);  
}  
  
// Function to return LCM of two numbers  
unsigned long long int lcm(unsigned long long int a, unsigned long long int b)  
{  
    return (a / gcd(a, b)) * b; 
} 

int main(int argc, char **argv){
    if(argc == 1){
        printf("Ficheiro burro\n\n");
        return 1;
    }
    tokens *tokens = parse_file(argv[1]);
    int n_strs = 0;
    //print_tokens(tokens);
    for(int i = 2; i < tokens->n_lines; i++){
        memcpy(tokens->tokens[i][2], tokens->tokens[i][2] + 1, 3*sizeof(char));
        tokens->tokens[i][2][3] = '\0';
        tokens->tokens[i][3][3] = '\0';
        if(tokens->tokens[i][0][2] == 'A') n_strs++;
    }
    char *directions = tokens->tokens[0][0];
    int *next = malloc(n_strs * sizeof(int));
    int *current = malloc(n_strs * sizeof(int));
    int *steps = malloc(n_strs * sizeof(int));
    int **ptrs = malloc(2*sizeof(int*));
    for(int i = 0; i < 2; i++) ptrs[i] = malloc(tokens->n_lines * sizeof(int));
    int ind = 0;
    for(int i = 2; i < tokens->n_lines; i++){
        ptrs[0][i] = find_next(tokens, tokens->tokens[i][2]);
        ptrs[1][i] = find_next(tokens, tokens->tokens[i][3]);
        if(tokens->tokens[i][0][2] == 'A') {
            current[ind] = next[ind] = i;
            ind++;
        }
    }
    for(int n = 0; n < n_strs; n++){
        unsigned long int total = 0;
        int dir_ind = 0;
        size_t str_len_dir = strlen(directions); 
        while(tokens->tokens[current[n]][0][2] != 'Z'){
            total++;
            current[n] = next[n];
            next[n] = directions[dir_ind] == 'L' ? ptrs[0][current[n]] : ptrs[1][current[n]];  
            dir_ind = (dir_ind + 1) % str_len_dir;
        }
        steps[n] = total - 1;
        printf("TOTAL STEPS = %lu\n", total - 1);
    }
    unsigned long long int cm = 1;
    for(int i = 0; i < n_strs; i++)
    {
        cm = lcm(cm, steps[i]);
    }
    printf("TOTAL FINAL ---> %llu\n\n", cm);
    free(next); free(current);
    free(ptrs[0]); free(ptrs[1]); free(ptrs);
    free_tokens(tokens);
}
