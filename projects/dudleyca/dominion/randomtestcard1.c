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
	srand(time(NULL));
	
    	int a;
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0;
	int seed = 500;
    	int player=0;
	struct gameState state, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    	printf("\n-------------- Testing village_Card() ------------------\n");


	for(a = 0; a < 5000; a++){
		int numPlayers = (rand() % MAX_PLAYERS);
		initializeGame(numPlayers, k, seed, &state);


   	     	printf("\n---- Iteration number: %d/5000 ----\n", a+1);

		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(village, c1, c2, c3, &state, pos, &bonus);

		player = whoseTurn(&test);

	        if(state.hand[player][test.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
	        }
	        else{
	            printf("Failed! Card was not added to hand.\n");
	        }

	        if(test.playedCardCount+1 == state.playedCardCount){
			printf("Passed! Card was played.\n");
	        }
	        else{
			printf("Failed! Card was not played.\n");
	        }

	        if(test.numActions+2 == state.numActions){
	            printf("Passed! Two extra actions were added.\n");
	        }
	        else{
	            printf("Failed! No extra actions were added.\n");
	        }

        	if(test.discardCount[player] == state.discardCount[player]){
			printf("Passed! Card was discarded.\n");
        	}
		else{
			printf("Failed! Card was not discarded.\n");
		}
		
    	}
	printf("--------- End of testing village_Card() ------------\n");
    
	return 0;
}


