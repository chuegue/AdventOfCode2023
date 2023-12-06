#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    unsigned long int *begin;
    unsigned long int *end;
    int *transitioned;
    int size;
    int full;
} da;

da *da_init(){
    da *new = malloc(sizeof(da));
    new->begin = malloc(sizeof(unsigned long int));
    new->end = malloc(sizeof(unsigned long int));
    new->transitioned = malloc(sizeof(int));
    new->begin[0] = new->end[0] = 0;
    new->transitioned[0] = 0;
    new->size = 1;
    new->full = 0;
    return new;
}

void da_rm(da *arr, int ind){
    if(ind < 0 || ind >= arr->full){
        printf("Deu merda familia. Ind = %d. arr->ful = %d\n", ind, arr->full);
        exit(1);
    }
    for(int i = ind; i < arr->full - 1; i++){
        arr->begin[i] = arr->begin[i+1];
        arr->end[i] = arr->end[i+1];
        arr->transitioned[i] = arr->transitioned[i+1];
    }
    arr->full -= 1;
}

void da_add_end(da *arr, unsigned long int begin, unsigned long int end, int transitioned){
    if(arr->full == arr->size){
        arr->begin = realloc(arr->begin, 2*arr->size*sizeof(unsigned long int)); 
        arr->end = realloc(arr->end, 2*arr->size*sizeof(unsigned long int)); 
        arr->transitioned = realloc(arr->transitioned, 2*arr->size*sizeof(int)); 
        arr->size *= 2;
        printf("Array extended. New size = %d\n", arr->size);
    }
    arr->begin[arr->full] = begin; 
    arr->end[arr->full] = end; 
    arr->transitioned[arr->full] = transitioned;
    arr->full += 1;
}

void da_reset_transitioned(da *arr){
    memset(arr->transitioned, 0, arr->size * sizeof(int));
}

int intersection( unsigned long int a1,  unsigned long int b1,  unsigned long int a2,  unsigned long int b2,  unsigned long int *c1,  unsigned long int *c2){
    *c1 = a1 > a2 ? a1 : a2;
    *c2 = b1 < b2 ? b1 : b2;
    if(*c1 > *c2) return 0;
    return 1;
}

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    char buffer[1024] = {0}, *aux;
    fgets(buffer, 1024, fp);
    aux = &buffer[0];
    da *seeds = da_init();
    unsigned long int begin, end;
    while(!(*aux<='9' && *aux >= '0')) aux++;
    while(sscanf(aux, "%lu %lu", &begin, &end) == 2){
        da_add_end(seeds, begin, begin + end - 1, 0);
        aux = strchr(aux, ' ') + 1;
        aux = strchr(aux, ' ') + 1;
        if(aux - 1 == NULL) break;
        while(!(*aux<='9' && *aux >= '0')) aux++;
    }
    for(int i = 0; i < seeds->full; i++){
        printf("%ld:%ld\n", seeds->begin[i], seeds->end[i]);
    }
    int finish = 0;
    for(int _ = 0; _ < 7; _++){
        if(finish) break;
        while(strstr(buffer, "map:") == NULL) fgets(buffer, 1024, fp);
        fgets(buffer, 1024, fp);
        da_reset_transitioned(seeds);
        while(buffer[0] <= '9' && buffer[0] >= '0'){
            if(finish) break;
            unsigned long int dest, src, len, begin, end;
            sscanf(buffer, "%lu %lu %lu", &dest, &src, &len);
            for(int i = 0; i < seeds->full; i++){
                if(intersection(seeds->begin[i], seeds->end[i], src, src + len - 1, &begin, &end) == 1 && seeds->transitioned[i] == 0){
                    if(src < seeds->begin[i]){
                        if(end >= seeds->begin[i] && end < seeds->end[i]){
                            da_add_end(seeds, dest + begin - src, dest + begin - src + end - begin, 1);
                            seeds->begin[i] = end + 1;
                        }else {
                            seeds->begin[i] = dest + begin - src;
                            seeds->end[i] = dest + end - src;
                            seeds->transitioned[i] = 1;
                        }
                    }else if(begin == seeds->begin[i]){
                        if(end < seeds->end[i]){
                            da_add_end(seeds, dest, dest + end - src, 1);
                            seeds->begin[i] = end + 1;
                        }else {
                            seeds->begin[i] = dest + begin - src;
                            seeds->end[i] = dest + end - src;
                            seeds->transitioned[i] = 1;
                        }
                    }else if(begin > seeds->begin[i] && begin < seeds->end[i]){
                        if(end < seeds->end[i]){
                            da_add_end(seeds, dest, dest + end - src, 1);
                            seeds->end[i] = begin - 1;
                        }else{
                            seeds->begin[i] = dest + begin - src;
                            seeds->end[i] = dest + end - src;
                            seeds->transitioned[i] = 1;
                        }
                    }else if(begin == seeds->end[i]){
                        da_add_end(seeds, dest, dest, 1);
                        seeds->end[i] = begin - 1;
                    }
                }
            }
            if(!fgets(buffer, 1024, fp)) finish = 1;
        }
    }
    unsigned long int min = ~0;
    for(int i = 0; i < seeds->full; i++){
        if(seeds->begin[i] < min) min = seeds->begin[i];
    }
    printf("ESTA MERDA ---> %lu\n", min);
    fclose(fp);
}
