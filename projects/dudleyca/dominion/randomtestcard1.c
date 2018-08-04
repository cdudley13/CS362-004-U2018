#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

int main() 
{
	srand(time(NULL)); //start random
	
    	int a;
	int pass_hc = 0, pass_pcc =0, fail_acts = 0, pass_dc=0; //counts
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0;
	int seed = 500;
    	int player=0;
	struct gameState state;
	struct gameState old;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    	printf("\n-------------- Testing village_Card() ------------------\n");
	//start the testing
	for(a = 0; a < 5000; a++){
		//randomize players& initialize the game
		int numPlayers = (rand() % MAX_PLAYERS);
		initializeGame(numPlayers, k, seed, &state);
		//print pass number
   	     	printf("\n---- Iteration number: %d/5000 ----\n", a+1);
		//copy memory into old state
		memcpy(&old, &state, sizeof(struct gameState));
		//start testing
		cardEffect(village, c1, c2, c3, &state, pos, &bonus);
		player = whoseTurn(&old);
		//test for expected handcount
	        if(state.hand[player][old.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
		    pass_hc += 1;
	        }
		//test for expected played card
	        if(old.playedCardCount+1 == state.playedCardCount){
			printf("Passed! Card was played.\n");
			pass_pcc +=1;
	        }
		//test for expected failure (bug in refactored code adds 4 acts, this should ALWAYS fail
	        if(old.numActions+2 != state.numActions){
	            printf("Failed! Two extra actions were not added.\n");
		    fail_acts += 1;
	        }
		//test for discard count
        	if(old.discardCount[player] == state.discardCount[player]){
			printf("Passed! Card was discarded.\n");
			pass_dc += 1;
        	}
    	}
	//print out the results
	printf("****** Results ******\n");
	printf("Hand count tests passed: %d\n", pass_hc);
	printf("Played card tests passed: %d\n", pass_pcc);
	printf("Discard tests passed: %d\n", pass_dc);
	printf("Actions added tests FAILED: %d\n", fail_acts);
	printf("--------- End of testing village_Card() ------------\n");
    
	return 0;
}


