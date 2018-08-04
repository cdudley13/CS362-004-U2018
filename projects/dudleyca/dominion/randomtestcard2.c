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
	//initialize random
	srand(time(NULL));
	
    	int a;
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0; //used for cardEffect fxn
    	int seed = 1000; //seeding
    	int player=0;
	struct gameState state; //name structs
    	struct gameState old;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    	//print notification of test
   	 printf("\n---------- Testing great_hall card --------------");
	//loop to start testing
   	 for(a = 0; a < 5000; a++){
		 //randomize number of players
		int player_num = (rand() % MAX_PLAYERS);
		//initialize the game state
		initializeGame(player_num, k, seed, &state);
		//copy state into "old"
        	memcpy(&old, &state, sizeof(struct gameState));
		//print header for number of iterations
	        printf("\n---- Iteration number: %d/5000 ----\n", a+1);
		//start the test
		cardEffect(great_hall, c1, c2, c3, &state, pos, &bonus);
		//get player
		player = whoseTurn(&old);
		//check players hand compared to the old state
	        if(state.hand[player][old.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
	        } else{
	            printf("Failed! Card was not added to hand.\n");
	        }
		//check if player played the great hall card
	        if(old.playedCardCount+1 == state.playedCardCount){
	            printf("Passed! Card was played.\n");
	        } else{
	            printf("Failed! Card was not played.\n");
	        }
		//check if the correct number of actions were added as result of playing card
		// there are no bugs, so this should ALWAYS pass
	        if(old.numActions+1 == state.numActions){
	            printf("Passed! One extra action was added.\n");
	        } else{
	            printf("Failed! No extra action was added.\n");
	        }
		//check if the card was properly discarded
	        if(old.discardCount[player] == state.discardCount[player]){
	            printf("Passed! Card was discarded.\n");
	        } else{
        	    printf("Failed! Card was not discarded.\n");
       		 }
	}
	//print that tests have ended
	printf("--------- End of testing for great_hall card --------\n");

	return 0;
}




