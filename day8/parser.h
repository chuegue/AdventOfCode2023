#ifndef __FILE_PARSER_TOKENIZER__
#define __FILE_PARSER_TOKENIZER__
typedef struct {
    char *** tokens;
    int n_lines;
    int *n_tokens;
} tokens;

/*
 * Returns a char***tokens. This is an array of array of strings. 
 * tokens[0] is the first line, tokens[1] is the secons, etc
 * tokens[0][0] is the first token of the first line, tokens[0][1] is the second token of the first line, etc
 * n_lines should be passed by referenced and will be stored the number of lines in the file
 * n_tokens must be a pointer to an integer array. the array will be malloc'ed inside this function.
 * if any element in n_tokens is 0 then that file is empty
 * n_tokens[i] is the number of tokens in the i'th line
 * */
tokens *parse_file(char *filename);

void print_tokens(tokens *tokens);

void free_tokens(tokens *tokens);
#endif
