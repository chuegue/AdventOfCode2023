#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int rank, max_card, bid;
    char hand[5];
} evaluation;

int evaluate_card(char c){
    if(c <= '9' && c >= '2'){
        return c - '2';
    }else if(c == 'T'){
        return 8;
    }else if(c == 'J'){
        return 9;
    }else if(c == 'Q'){
        return 10;
    }else if(c == 'K'){
        return 11;
    }else{
        return 12;
    }
}

int compare_cards(const void *a, const void *b){
    char ac = *(char *)a, bc = *(char *)b;
    return evaluate_card(ac) - evaluate_card(bc);
}

int compare_hands(const void *a, const void *b){
    evaluation ha = *(evaluation *)a, hb = *(evaluation *)b;
    if(ha.rank != hb.rank){
        return ha.rank - hb.rank;
    }else{
        for(int i = 0; i < 5; i++){
            if(evaluate_card(ha.hand[i]) != evaluate_card(hb.hand[i])) return evaluate_card(ha.hand[i]) - evaluate_card(hb.hand[i]);
        }
    }
    return 0;
}


evaluation evaluate_hand(char hand[5], int bid){
    char aux[5];
    memcpy(aux, hand, 5*sizeof(char));
    qsort(aux, 5, sizeof(char), compare_cards);
    evaluation r;
    memcpy(r.hand, hand, 5*sizeof(char));
    r.bid = bid;
    if(aux[0] == aux[1] && aux[1] == aux[2] && aux[2] == aux[3] && aux[3] == aux[4]){
        r.rank = 6;
        r.max_card = evaluate_card(hand[0]);
    }else if((aux[0] == aux[1] && aux[1] == aux[2] && aux[2] == aux[3]) || (aux[1] == aux[2] && aux[2] == aux[3] && aux[3] == aux[4])){
        r.rank = 5;
        r.max_card = evaluate_card(hand[0]);
    }else if((aux[0] == aux[1] && aux[1] == aux[2] && aux[3] == aux[4]) || (aux[0] == aux[1] && aux[2] == aux[3] && aux[3] == aux[4])){
        r.rank = 4;
        r.max_card = evaluate_card(hand[0]);
    }else if((aux[0] == aux[1] && aux[1] == aux[2]) || (aux[1] == aux[2] && aux[2] == aux[3]) || (aux[2] == aux[3] && aux[3] == aux[4])){
        r.rank = 3;
        r.max_card = evaluate_card(hand[0]);
    }else if((aux[0] == aux[1] && aux[2] == aux[3]) || (aux[1] == aux[2] && aux[3] == aux[4]) || (aux[0] == aux[1] && aux[3] == aux[4])){
        r.rank = 2;
        r.max_card = evaluate_card(hand[0]);
    }else if(aux[0] == aux[1] || aux[1] == aux[2] || aux[2] == aux[3] || aux[3] == aux[4]){
        r.rank = 1;
        r.max_card = evaluate_card(hand[0]);
    }else{
        r.rank = 0;
        r.max_card = evaluate_card(hand[0]);
    }
    return r;
}

int main(int argc, char **argv){
    if(argc == 1){
        printf("Dá mu um ficheiro de entrada seu burro\n\n");
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if(!fp){
        printf("Ficheiro não existe seu burro\n\n");
        exit(1);
    }
    char buffer[1024] = {0};
    evaluation hands[1024] = {0};
    int ind = 0, bids[1024] = {0};
    while(fgets(buffer, 1024, fp)){
        char hand[5]; int bid;
        sscanf(buffer, "%s %d", hand, &bid);
        //printf("HAND : %s\t BID : %d\n", hand, bid);
        hands[ind++] = evaluate_hand(hand, bid);
    }
    for(int i = 0; i < ind; i++){
        printf("Hand: %.5s\tRank: %d\tMax Card: %d\n", hands[i].hand, hands[i].rank, hands[i].max_card);
    }
    printf("\n\n");
    qsort(hands, ind, sizeof(evaluation), compare_hands);
    int total = 0;
    for(int i = 0; i < ind; i++){
        printf("Hand: %.5s\tRank: %d\tMax Card: %d\n", hands[i].hand, hands[i].rank, hands[i].max_card);
        total += (i+1) * hands[i].bid;
    }

    printf("TOTAL ----> %d\n\n", total);
    fclose(fp);
}
