#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv){
    if(argc == 1){
        printf("Dá-me um ficheiro de entrada seu burro\n");
        exit(1);
    }
    char filename[256] = {0};
    strcpy(filename, argv[1]);
    FILE *fp = fopen(filename, "r"); 
    char time_str[1024], dst_str[1024];
    fgets(time_str, 1024, fp);
    fgets(dst_str, 1024, fp);
    char *t_ptr, *d_ptr;
    t_ptr = strchr(time_str, ':');
    d_ptr = strchr(dst_str, ':');
    char t_aux[32] = {0}, d_aux[32] = {0};
    int t_i = 0, d_i = 0;
    while(*t_ptr != '\n'){
        if(*t_ptr <= '9' && *t_ptr >= '0'){
            t_aux[t_i++] = *t_ptr;
        }
        t_ptr++;
    }
    while(*d_ptr != '\n'){
        if(*d_ptr <= '9' && *d_ptr >= '0'){
            d_aux[d_i++] = *d_ptr;
        }
        d_ptr++;
    }
    printf("%s\n%s\n", t_aux, d_aux);
    unsigned long long t = strtoull(t_aux, NULL, 10);
    unsigned long long d = strtoull(d_aux, NULL, 10);
    printf("%llu\n%llu\n", t, d);
    unsigned long long x1 = (t + (unsigned long long)floorl(sqrtl((t*t) - (4*d))))/2;
    unsigned long long x2 = (t - (unsigned long long)floorl(sqrtl((t*t) - (4*d))))/2;
    printf("x1 = %llu\nx2 = %llu\nNUMBER OF WAYS = %llu\n\n", x1, x2, (x1 - x2) < 0 ? (x2 - x1) : (x1 - x2));
    fclose(fp);
}
