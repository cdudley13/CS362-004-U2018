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
	
    	int a;
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0;
    	int seed = 1000;
    	int player=0;
	struct gameState state;
    	struct gameState old;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
  	//print card being tested  
   	 printf("\n---------- Testing great_hall card --------------");
   	 for(a = 0; a < 5000; a++){
		//initialize game & player count
		int player_num = (rand() % MAX_PLAYERS);
		initializeGame(player_num, k, seed, &state);
		//copy the memory
        	memcpy(&old, &state, sizeof(struct gameState));
		//print pass number
	        printf("\n---- Iteration number: %d/5000 ----\n", a+1);
		//start the testing
		cardEffect(great_hall, c1, c2, c3, &state, pos, &bonus);
		player = whoseTurn(&old);
		//test handcount
	        if(state.hand[player][old.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
	        } else{
	            printf("Failed! Card was not added to hand.\n");
	        }
		//test played card count
	        if(old.playedCardCount+1 == state.playedCardCount){
	            printf("Passed! Card was played.\n");
	        } else{
	            printf("Failed! Card was not played.\n");
	        }
		//test number of actions
	        if(old.numActions+1 == state.numActions){
	            printf("Passed! One extra action was added.\n");
	        }
	        else{
	            printf("Failed! No extra action was added.\n");
	        }
		//test discarding card
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




