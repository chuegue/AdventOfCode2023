#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int rank, max_card, bid;
    char hand[5];
} evaluation;

int evaluate_card(char c){
    if(c <= '9' && c >= '2'){
        return c - '2' + 1;
    }else if(c == 'T'){
        return 9;
    }else if(c == 'J'){
        return 0;
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

evaluation evaluate_hand_joker(char hand[5], int bid, int index){
    if (index == 5) {
        return evaluate_hand(hand, bid);
    }
    evaluation best_eval = evaluate_hand(hand, bid);
    char cards[13] = "23456789TQKA";
    if (hand[index] == 'J') {
        char cp_hand[5];
        memcpy(cp_hand, hand, 5*sizeof(char));
        for (int i = 0; i < strlen(cards); i++) {
            cp_hand[index] = cards[i];
            evaluation new_eval = evaluate_hand_joker(cp_hand, bid, index);
            if(compare_hands((void*)&best_eval, (void*)&new_eval) < 0){
                best_eval = new_eval;
            }
        }
        // Reset the character to 'J' for the next iteration
        cp_hand[index] = 'J';
    } else {
        best_eval = evaluate_hand_joker(hand, bid, index + 1);
    }

    return best_eval;
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
        printf("HAND : %s\t BID : %d\n", hand, bid);
        hands[ind++] = evaluate_hand_joker(hand, bid, 0);
        memcpy(hands[ind-1].hand, hand, 5*sizeof(char));
    }
    qsort(hands, ind, sizeof(evaluation), compare_hands);
    unsigned long int total = 0;
    for(int i = 0; i < ind; i++){
        printf("Hand: %.5s\tRank: %d\tMax Card: %d\n", hands[i].hand, hands[i].rank, hands[i].max_card);
        total += (i+1) * hands[i].bid;
    }

    printf("TOTAL ----> %lu\n\n", total);
    fclose(fp);
}
