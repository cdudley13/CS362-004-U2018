#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// global count of test failures
int fails= 0;

// function to check if two ints are equal or not
void assertTrue(int a, int b) {
    if (a == b) {
        printf("Test: PASSED\n");
    }
    else {
        printf("Test: FAILED\n");
        fails++;
    }
}

// runs the tests
int main () {
    int i;
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    
    int handpos = 0;
    int c1 = 0, c2 = 0, c3 = 0;
    int bonus = 0;
    
    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    int seed = 2000;
    struct gameState state, origState;
    
    printf("----------------- Testing: village_Card()------------------\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&origState,23,sizeof(struct gameState));
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    
    // copy it to preserve it
    memcpy(&origState, &state, sizeof(struct gameState));
    //copy game state to a test case
    cardEffect(village, c1, c2, c3, &state, handpos, &bonus);
    
    printf("\n TEST 1: Player0 gains 1 card\n");
    assertTrue(state.handCount[player0],origState.handCount[player0]);
    
    printf("\n TEST 2: Player0 gains 1 card from his own pile\n");
    assertTrue(state.deckCount[player0],origState.deckCount[player0]-1);
    
    printf("\n TEST 3: Player0 gains two actions\n");
    assertTrue(state.numActions,origState.numActions+2);
    
    printf("\n TEST 4: No change to victory card piles\n");
    printf("Province Pile\n");
    assertTrue(state.supplyCount[province],origState.supplyCount[province]);
    printf("Duchy Pile\n");
    assertTrue(state.supplyCount[duchy],origState.supplyCount[duchy]);
    printf("Estate Pile\n");
    assertTrue(state.supplyCount[estate],origState.supplyCount[estate]);
    
    printf("\n TEST 5: Player1 was not affected\n");
    printf("Hand Count\n");
    assertTrue(state.handCount[player1],origState.handCount[player1]);
    printf("Deck Count\n");
    assertTrue(state.deckCount[player1],origState.deckCount[player1]);
    
    printf("\nTEST 6: No change to kingdom card piles\n");
    for (i = 0; i < 10; i++) {
        printf("checking card piles...\n");
        assertTrue(state.supplyCount[k[i]],origState.supplyCount[k[i]]);
    }
    
    if (fails) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",fails);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }
    
    return 0;
}
