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
	//initialize random
	srand(time(NULL));
	
    	int a;
    	int pos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0; //inputs into cardEffect function
	int seed = 500;
    	int player=0;
	struct gameState state, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    	printf("\n-------------- Testing village_Card() ------------------\n");

	//start the loop for the test
	for(a = 0; a < 5000; a++){
		//randomize the number of players
		int numPlayers = (rand() % MAX_PLAYERS);
		// initialize the game state
		initializeGame(numPlayers, k, seed, &state);

		//prints the number of iterations
   	     	printf("\n---- Iteration number: %d/5000 ----\n", a+1);
		//copy the gameState to the test
		memcpy(&test, &state, sizeof(struct gameState));
		//calls the game
		cardEffect(village, c1, c2, c3, &state, pos, &bonus);

		player = whoseTurn(&test);
		//Check players hand for village_Card
	        if(state.hand[player][test.handCount[player]-1] != -1){
	            printf("Passed! Card was added to hand.\n");
	        } else{
	            printf("Failed! Card was not added to hand.\n");
	        }
		//check if player actually played the card
	        if(test.playedCardCount+1 == state.playedCardCount){
			printf("Passed! Card was played.\n");
	        } else{
			printf("Failed! Card was not played.\n");
	        }
        	//Check if the correct number (+2) of actions were added
        	//this should always fail--> bug in code changed numActions added to be +4
	        if(test.numActions+2 == state.numActions){
	            printf("Passed! Two extra actions were added.\n");
	        } else{
	            printf("Failed! No extra actions were added.\n");
	        }
		//Check if card was discarded
        	if(test.discardCount[player] == state.discardCount[player]){
			printf("Passed! Card was discarded.\n");
        	} else{
			printf("Failed! Card was not discarded.\n");
		}
		
    	}
	//print that the testing ended
	printf("--------- End of testing village_Card() ------------\n");
    
	return 0;
}


