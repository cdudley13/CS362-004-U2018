#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() 
{
	srand(time(NULL));
	
    	int i, j, m, a;
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0;
    	int seed = 1000;
    	int player=0;
	struct gameState state;
    	struct gameState old;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
   	 printf("\n---------- Testing great_hall card --------------");
   	 for(a = 0; a < 5000; a++){
		int player_num = (rand() % MAX_PLAYERS);
		initializeGame(player_num, k, seed, &state);

        	memcpy(&old, &state, sizeof(struct gameState));

	        printf("\n---- Iteration number: %d/5000 ----\n", a+1);

		cardEffect(great_hall, c1, c2, c3, &state, pos, &bonus);

		player = whoseTurn(&old);

	        if(state.hand[player][old.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
	        } else{
	            printf("Failed! Card was not added to hand.\n");
	        }

	        if(old.playedCardCount+1 == state.playedCardCount){
	            printf("Passed! Card was played.\n");
	        } else{
	            printf("Failed! Card was not played.\n");
	        }

	        if(old.numActions+1 == state.numActions){
	            printf("Passed! One extra action was added.\n");
	        }
	        else{
	            printf("Failed! No extra action was added.\n");
	        }

	        if(old.discardCount[player] == state.discardCount[player]){
	            printf("Passed! Card was discarded.\n");
	        }
	        else{
        	    printf("Failed! Card was not discarded.\n");
       		 }
	}
	printf("--------- End of testing for great_hall card --------\n");

	return 0;
}




