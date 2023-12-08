#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

#ifndef MAX_LINE_SIZE
#define MAX_LINE_SIZE 1024 << 4
#endif

tokens *parse_file(char *filename){
    FILE *fp = fopen(filename, "r");
    char buffer[MAX_LINE_SIZE] = {0};
    tokens *ret = malloc(sizeof(tokens));
    ret->n_lines = 0;
    while(fgets(buffer, MAX_LINE_SIZE, fp)){
        ret->n_lines++;
        //printf("%s", buffer);
    }
    ret->tokens = malloc(ret->n_lines * sizeof(char **));
    ret->n_tokens = malloc(ret->n_lines * sizeof(int));
    rewind(fp);
    int line = 0;
    while(fgets(buffer, MAX_LINE_SIZE, fp)){
        //printf("LINE: \n");
        int m_tokens = 1, i_tok = 0;
        ret->tokens[line] = malloc(m_tokens * sizeof(char *));
        char *ptr = buffer;
        while(*ptr != '\n'){
            if(isspace(*ptr)){
                ptr++;
                continue;
            }
            char *end = ptr;
            while(!isspace(*end)){
                end++;
            }
            if(i_tok == m_tokens){
                ret->tokens[line] = realloc(ret->tokens[line], (m_tokens+1)*sizeof(char *));
                m_tokens++;
            }
            ret->tokens[line][i_tok++] = strndup(ptr, end - ptr);
            //printf("\tTOKEN: %s\n", tokens[line][i_tok - 1]);
            ptr = end;
        }
        ret->n_tokens[line] = i_tok;
        line++;
    }
    fclose(fp);
    return ret;
}

void print_tokens(tokens *tokens){

    for(int i = 0; i < tokens->n_lines; i++){
        printf("LINE %d:", i);
        if(tokens->n_tokens[i] == 0){
            printf(" IS EMPTY\n");
        }else{
            printf("\n");
            for(int j = 0; j < tokens->n_tokens[i]; j++){
                printf("\tTOKEN %i: %s\n", j, tokens->tokens[i][j]);
            }
        }
    }

}

void free_tokens(tokens *tokens){
    for(int i = 0; i < tokens->n_lines; i++){
        for(int j = 0; j < tokens->n_tokens[i]; j++){
            free(tokens->tokens[i][j]);
        }
        free(tokens->tokens[i]);
    }
    free(tokens->tokens);
    free(tokens->n_tokens);
    free(tokens);
}

//int main(int argc, char **argv){
//    if(argc==1){printf("Ficheiro burro\n\n"); exit(1);}
//    int n_lines, *n_tokens;
//    tokens * tokens = parse_file(argv[1]);
//    print_tokens(tokens);
//    free_tokens(tokens);
//    return 0;
//}
