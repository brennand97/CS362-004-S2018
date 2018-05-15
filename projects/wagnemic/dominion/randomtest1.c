/*
 * randomtest1.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "smithy"
#define NOISY 1

int silent = 0;

int safeAssert(int condition) {
	if (silent) { return !condition; }
    if (condition) {
		if (NOISY) {
			// nothing for now
		}
        return 0;
    } else {
		if (NOISY) {
			// nothing for now
		}
        return 1;
    }
}

int check_smithy(struct gameState *G, int handPos) {
	struct gameState testG;
	int failures = 0;
	
	int i, j;
	int card;

	int diff, diff2;
	int p = G->whoseTurn;

	// set test game state
	memcpy(&testG, G, sizeof(struct gameState));

	// run the state through the function
	cardEffect_smithy(&testG, handPos);

	// find the difference in hand counts
	diff = testG.handCount[p] - G->handCount[p];
	// check to make sure its not greater than 2
	failures += safeAssert(diff <= 2);

	// find the difference between avaiable cards
	diff2 = (G->deckCount[p]    + G->discardCount[p]) -
	        (testG.deckCount[p] + testG.discardCount[p]);
	// check to make sure this is equal to diff + 1
	failures += safeAssert(diff + 1 == diff2);

	// check to make sure that the playedCardCount is 1 more
	failures += safeAssert(testG.playedCardCount - G->playedCardCount == 1);

	// check to make sure the proper card was copied to playedCards
	failures += safeAssert(G->hand[p][handPos] == testG.playedCards[G->playedCardCount]);


	return failures;
}

int main() {
    int failures = 0, t_failures = 0;
	int i, j, m, p;
	int result;
	int handPos;

	int N;
    int seed = 1110;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, council_room};

	
	SelectStream(2);
	PutSeed(seed);

	N = 10000;

	for (m = 0; m < N; m++) {

		failures = 0;

		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}	
	
		// Set the number of players constraint.	
		G.numPlayers = floor(Random() * (MAX_PLAYERS - 2)) + 2;

		// Choose a valid player to be currently playing.	
		p = floor(Random() * G.numPlayers);
		G.whoseTurn = p;

		// Set the deck counts to one fourth the max_deck
		// as at any one time all the cards could potentially
		// be in one deck and therfore the total number of
		// cards needs to be less than the MAX_DECK constraint.
		G.deckCount[p] = floor(Random() * (MAX_DECK / 4));
		G.discardCount[p] = floor(Random() * (MAX_DECK / 4));
		G.playedCardCount = floor(Random() * (MAX_DECK / 4));
		G.handCount[p] = floor(Random() * (MAX_DECK / 4)) + 1; // expecting minimum of one card

		// Set a random hand postion that is valid
		handPos = floor(Random() * G.handCount[p]);

		// Check to see if the random gameState passes
		// the check.
		failures += check_smithy(&G, handPos);


		// Print out the result.
		if (failures == 0) {
			printf("iteration %d\n", m);
		} else {
			printf("iteration %d: FAILED\n", m);
		}
		fflush(stdout);
		t_failures += failures;
	}

	printf("All tests completed, %d/%d failed.\n", t_failures, N);
    
    return 0;
}
