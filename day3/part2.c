#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int a[9];
    int ind;
} aux;

void isadjacenttogear(char **matrix, aux **aux_matrix, int i, int j1, int j2, int n_lines, int number){
    for(int x = i - 1; x <= i + 1; x++){
        for(int y = j1 - 1; y <= j2 + 1; y++){
            if(x < 0 || x >= n_lines || y < 0 || y >= strlen(matrix[i])) continue;
            if(matrix[x][y] == '*') aux_matrix[x][y].a[aux_matrix[x][y].ind++] = number; 
        }
    }
}

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    char buffer[512] = {0};
    int n_lines = 0, max_length = 0;
    while(fgets(buffer, 512, fp)){
        n_lines++;
        if(strlen(buffer) > max_length) max_length = strlen(buffer);
    }
    char **matrix = (char **)malloc(n_lines * sizeof(char *));
    aux **aux_matrix = (aux **)malloc(n_lines * sizeof(aux *));
    for(int i = 0; i < n_lines; i++){
        matrix[i] = (char *)calloc(max_length, sizeof(char));
        aux_matrix[i] = (aux *)calloc(max_length, sizeof(aux));
    }
    rewind(fp);
    int ind = 0;
    while(fgets(buffer, 512, fp)){
        char *c = strchr(buffer, '\n');
        *c = '\0';
        strcpy(matrix[ind], buffer);
        ind++;
    }
    int total = 0;
    for(int i = 0; i < n_lines; i++){
        //for(char *c = matrix[i], j = (int)0; *c != '\0'; j++, c++){
        for(int j = 0; matrix[i][j] != '\0'; j++){
            if(!(matrix[i][j] <= '9' && matrix[i][j] >= '0')) continue;
            int i1 = i, j1 = j;
            while(matrix[i][j] <= '9' && matrix[i][j] >= '0'){
                j++;
            }
            j--; int j2 = j;
            char number[7] = {0}; int nind = 0;
            for(int a = j1; a <= j2; a++){
                number[nind++] = matrix[i][a]; 
            }
            isadjacenttogear(matrix, aux_matrix, i, j1, j2, n_lines, atoi(number));
        }
    }
    for(int i = 0; i < n_lines; i++){
        for(int j = 0; j < max_length; j++){
            if(aux_matrix[i][j].ind > 0){
                printf("One cog with %d numbers adjacent. These are:\t", aux_matrix[i][j].ind);
                for(int a = 0; a < aux_matrix[i][j].ind; a++){
                    printf("%d ", aux_matrix[i][j].a[a]);
                }
                printf("\n");
            }
            if(aux_matrix[i][j].ind == 2) total += aux_matrix[i][j].a[0] * aux_matrix[i][j].a[1];
        }
    }
    printf("Total = %d\n", total);
    fclose(fp);
    return 0;
    }
