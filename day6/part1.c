#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    printf("%d\n\n", argc);
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
    while(!(*t_ptr <= '9' && *t_ptr >= '0')) t_ptr++;
    while(!(*d_ptr <= '9' && *d_ptr >= '0')) d_ptr++;
    int time, distance, total = 1;
    while(sscanf(t_ptr, "%d", &time) == 1 && sscanf(d_ptr, "%d", &distance) == 1){
        printf("%d:%d\n", time, distance); 
        int wins = 0;
        for(int button = 0; button <= time; button++){
            int my_dist = (time - button) * button;
            if(my_dist > distance) wins++;
        }
        printf("Wins = %d\n", wins);
        total *= wins;
        t_ptr = strchr(t_ptr, ' ');
        d_ptr = strchr(d_ptr, ' ');
        if(!t_ptr || !d_ptr) break;
        while(!(*t_ptr <= '9' && *t_ptr >= '0')) t_ptr++;
        while(!(*d_ptr <= '9' && *d_ptr >= '0')) d_ptr++;
    }
    printf("THIS ---> %d\n", total);
    fclose(fp);
    return 0;
}
