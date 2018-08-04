#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

int total;
int dc, ce, sh, tc, dhc;
int fail_counts[6];
char* fx[6] = {"drawCard()", "cardEffect()", "shuffle()", "treasure_count", "deck_hand count" };

//function declarations
void randomAdventurer(int player, struct gameState *G);

int main(){
    srand(time(NULL));
    
//    int i, j, m, a;
//    int pos = 0, c1 = 0, c2 = 0, c3 = 0;
    //int seed = 1000;
    //int numPlayers = 2;
//    int player=0;
//    struct gameState state, test;
//    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
//        sea_hag, tribute, smithy, council_room};
    
//    int count1 = 0;
//    int count2 = 0;

        
    int iters = 5000;
    int treasures[] = {copper,silver,gold};
    int t_count;
    int i, n, player;
    struct gameState G;
    int min = 2; //minimum number of cards, otherwise dominion doesn't work properly
    //initialize the failure_count array to 0's
    for(n = 0; n < 6; n++){
        fail_counts[n] = 0;
    }

    int c;
    for (c = 0; c < iters; c++){
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
        t_count = floor(Random() * ((G.deckCount[player] - min) + 1) + min);

        for (i = 0; i < t_count; i++) {
            G.deck[player][i] = treasures[rand() % 3];
        }
        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
        G.whoseTurn = player;
        //call the random function
        randomAdventurer(player, &G);
    }
// calculate the total number of failures from array
    int j;
    for(j = 0; j < 6; j++){
        total += fail_counts[j];
    }
    //if there are zero failures
    if(total == 0){
        printf("*----- Passed Random Test ------*\n");
    }
    //loop to print out what test failed & how many times
    else {
        int n;
        printf("\n * ------ Failures --------*\n");
        for(n = 0; n < 6; n++){
            printf("%s failed: %d\n", fx[n], fail_counts[n]);
        }
    }

    int check;
    check = iters - total;
    if(check > 0){
        printf("* ----- Results ------- *\n");
        printf("Number of Passed tests: %d\n", check);
        printf("Number of Failed tests: %d\n", total);
    }
    //if there is no difference b/t # of iterations and total failures
    else{
        printf("Passed tests: %d\n", 0);
        printf("Failed test: %d\n", iters);
    }

    return 0;

}

void randomAdventurer(int p, struct gameState *G){
    //create gameState to store state of pre
    struct gameState pre;
    //get the gameState copied into pre
    memcpy(&pre, G, sizeof(struct gameState));
    
    //stores temp
    int temp[MAX_HAND];
    //ints initialized to 0
    int post_tc = 0;
    int pre_tc = 0;
    int t_drawn = 0;
    int bonus = 0;
    int z = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int pos = 0;
// unitialized int variables
    int c_drawn;
    int card;
    int s,t,i, r;
    //get return value from running cardEffect
    r = cardEffect(adventurer, c1, c2, c3, G, pos, &bonus);
    // -1 means that cardEffect failed
    if(r == -1){
        ce++;
        fail_counts[1] = ce;
      //  printf("cardEffect fails: %d \n", fail_counts[1]);
    }
    //adventurer card actions
    //while treasure cards drawn < 2
    while(t_drawn < 2) {
            //if the deck is empty we need to shuffle discard and add to deck
            if (pre.deckCount[p] < 1) {
                    s = shuffle(p, &pre);
                    // check if shuffle failed
                    if (s == -1 && pre.deckCount[p] >= 1) {
                      sh++;
                      fail_counts[2] = sh;
                   //   printf("shuffle fails: %d\n", fail_counts[2]);
                    }
            }
            //store return value of drawCard
            t = drawCard(p, &pre);
            // check if drawcard failed
            if (t == -1 && pre.deckCount[p] != 0) {
                dc++;
                fail_counts[0] = dc;
                //printf("drawCard failed: %d\n", fail_counts[0]);
            }
            //top card of hand is most recently drawn card.
            c_drawn = pre.hand[p][pre.handCount[p] - 1];
            if (c_drawn == copper || c_drawn == silver || c_drawn == gold)
                    t_drawn++;
            else{
                    temp[z] = c_drawn;
                    //this should just remove the top card (the most recently drawn one).
                    pre.handCount[p]--; 
                    z++;
            }
    }
    while(z - 1 >= 0) {
            // discard all cards in play that have been drawn
            pre.discard[p][pre.discardCount[p]++] = temp[z - 1];
            z = z - 1;
    }
    // get the post_tc
    for (i = 0; i < G->handCount[p]; i++) {
        card = G->hand[p][i];
        if (card == copper || card == silver || card == gold) {
            post_tc++;
        }
    }
    // get the pre_tc
    for (i = 0; i < pre.handCount[p]; i++) {
        card = pre.hand[p][i];
        if (card == copper || card == silver || card == gold) {
            pre_tc++;
        }
    }
    //if post treasure count doesn't match the pre-tc
    if (post_tc != pre_tc) {
        //increment the number of treasure count fails
        tc++;
        fail_counts[3] = tc;
       // printf("treasure fail count: %d\n", fail_counts[3]);
    }

    // get values of hand and deck counts
    //pre/post hand counts
    int prhc = pre.handCount[p];
    int pohc = G->handCount[p];
    //pre/post deck counts
    int prdc = pre.deckCount[p];
    int podc = G->deckCount[p];
    //pre/post discard deck counts
    int pre_discard = pre.discardCount[p];
    int post_discard = G->discardCount[p];

    // check if the hand and deck counts dont match up
    if (!(pohc == prhc && podc == prdc && post_discard == pre_discard)) {
        dhc++;
        fail_counts[4] = dhc;
      //  printf("dhc fails: %d\n", fail_counts[4]);
    }
}

