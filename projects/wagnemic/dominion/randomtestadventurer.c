/*
 * randomtestadventurer.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "adventurer"
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

int check_adventurer(struct gameState *G) {
	struct gameState testG;
	int failures = 0;
	
	int i, j;
	int card;

	int diff = 0, diff2 = 0;
	int p = G->whoseTurn;

	// set test game state
	memcpy(&testG, G, sizeof(struct gameState));

	// run the state through the function
	adventurerEffect(&testG);

	// find the difference in hand counts
	diff = testG.handCount[p] - G->handCount[p];
	// check to make sure its not greater than 2
	failures += safeAssert(diff <= 2);

	// check to make sure each card moved to hand
	// is a treasure card
	for (i = 0; i < diff; i++) {
		card = testG.hand[p][G->handCount[p] + i];
		failures += safeAssert(card == copper || card == silver || card == gold);
	}

	// check to make sure the total difference between
	// the deck and discard pile is the same as what
	// was added to the hand
	diff2 = (G->deckCount[p]    + G->discardCount[p]) - 
	        (testG.deckCount[p] + testG.discardCount[p]);
	failures += safeAssert(diff2 == diff);

	return failures;
}

int main() {
    int failures = 0;
	int i, j, m, p;
	int result;

	int N;
    int seed = 1111;
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

		// Set the deck counts to one thrid the max_deck
		// as at any one time all the cards could potentially
		// be in one deck and therfore the total number of
		// cards needs to be less than the MAX_DECK constraint.
		G.deckCount[p] = floor(Random() * (MAX_DECK / 3));
		G.discardCount[p] = floor(Random() * (MAX_DECK / 3));
		G.handCount[p] = floor(Random() * (MAX_DECK / 3));

		// Set the card arrays to the correct card integers.
		// The random test would still work without this,
		// however it would take a much longer time to find
		// any treausres (and thus a much longer time to
		// check for proper sucesses and failures).

		for (i = 0; i < G.deckCount[p]; i++) {
			// There are 27 different cards
			// set them to random cards
			G.deck[p][i] = floor(Random() * 26);
		}

		for (i = 0; i < G.discardCount[p]; i++) {
			// There are 27 different cards
			// set them to random cards
			G.discard[p][i] = floor(Random() * 26);
		}

		for (i = 0; i < G.handCount[p]; i++) {
			// There are 27 different cards
			// set them to random cards
			G.hand[p][i] = floor(Random() * 26);
		}

		// Check to see if the random gameState passes
		// the check.
		failures += check_adventurer(&G);


		// Print out the result.
		if (failures == 0) {
			printf("iteration %d\n", m);
		} else {
			printf("iteration %d: FAILED\n", m);
		}
		fflush(stdout);
	}

	printf("All tests completed\n");
    
    return 0;
}
