#include <stdio.h>
#include <string.h>

int main(){
    FILE *fp = fopen("input_part1.txt", "r");
    if(!fp){printf("erro com o ficheiro\n"); return 1;}
    char buffer[1024] = {0}, *aux;
    fgets(buffer, 1024, fp);
    aux = buffer;
    while(!(*aux<='9'&&*aux>='0'))aux++;
    unsigned long int seeds[128] = {0}, ind = 0, location[128], changed[128];
    while(sscanf(aux, "%ld", &seeds[ind]) == 1){
        location[ind] = seeds[ind];
        changed[ind] = 0;
        printf("seeds[%ld] = %ld\n", ind, seeds[ind]);
        ind++;
        aux = strchr(aux, ' ');
        if(!aux) break;
        while(!(*aux<='9'&&*aux>='0'))aux++;
    }
    while(strstr(buffer, "seed-to-soil map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(seeds[i] >= src && seeds[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (seeds[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> soil %ld\n", seeds[i], location[i]);
    printf("\n");
    while(strstr(buffer, "soil-to-fertilizer map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> fertilizer %ld\n", seeds[i], location[i]);
    printf("\n");
    while(strstr(buffer, "fertilizer-to-water map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> water %ld\n", seeds[i], location[i]);
    printf("\n");
    while(strstr(buffer, "water-to-light map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> light %ld\n", seeds[i], location[i]);
    printf("\n");
    while(strstr(buffer, "light-to-temperature map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> temperature %ld\n", seeds[i], location[i]);
    printf("\n");
    while(strstr(buffer, "temperature-to-humidity map:") == NULL) fgets(buffer, 1024, fp);
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        fgets(buffer, 1024, fp);
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> humidity %ld\n", seeds[i], location[i]);
    while(strstr(buffer, "humidity-to-location map:") == NULL) fgets(buffer, 1024, fp);
    printf("\n");
    fgets(buffer, 1024, fp);
    memset(changed, 0, 128*sizeof(unsigned long int));
    while(buffer[0]<='9' && buffer[0] >= '0'){
        unsigned long int dest, src, len;
        sscanf(buffer, "%ld %ld %ld", &dest, &src, &len);
        for(unsigned long int i = 0; i < ind; i++){
            if(location[i] >= src && location[i] <= src + len - 1 && changed[i] == 0){
                location[i] = dest + (location[i] - src); 
                changed[i] = 1;
            }
        }
        if(!fgets(buffer, 1024, fp)) break;
    }
    for(unsigned long int i = 0; i < ind; i++) printf("seed %ld -> location %ld\n", seeds[i], location[i]);
    printf("\n");
    unsigned long int closest = ~0;
    int c_i = 0;
    for(int i = 0; i < ind; i++){
        if(location[i] < closest){
            closest = location[i]; 
            c_i = i;
        }
    }
    printf("ISTO ---> %zu\n", closest);
    fclose(fp);
    return 0;
}
