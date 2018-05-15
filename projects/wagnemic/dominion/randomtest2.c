/*
 * randomtest2.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "feast"
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

int check_feast(struct gameState *G, int choice) {
	struct gameState testG;
	int failures = 0;
	
	int i, j;
	int card;

	int diff, diff2;
	int p = G->whoseTurn;

	// set test game state
	memcpy(&testG, G, sizeof(struct gameState));

	// run the state through the function
	cardEffect(0, choice, 0, 0, &testG, 0, 0);

	// determine if a card should have been picked up
	j = G->supplyCount[choice] < 1 || getCost(choice) > 5 ? 0 : 1;

	// the supply count should be one lower
	failures += safeAssert(G->supplyCount[choice] == testG.supplyCount[choice] + j);

	// the discard should have an extra card
	failures += safeAssert(G->discardCount[p] == testG.discardCount[p] - j);

	//printf("G.sc: %d, tG.sc: %d, G.dc: %d, tG.dc: %d, cost: %d, j: %d\n", G->supplyCount[choice], testG.supplyCount[choice], G->deckCount[choice], testG.deckCount[choice], getCost(choice), j);

	return failures;
}

int main() {
    int failures = 0, t_failures = 0;
	int i, j, m, p;
	int result;
	int choice;

	int N;
    int seed = 1110;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, council_room};

	
	SelectStream(2);
	PutSeed(seed);

	N = 5000;

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

		// Set the deck counts to one quarter the max_deck
		// as at any one time all the cards could potentially
		// be in one deck and therfore the total number of
		// cards needs to be less than the MAX_DECK constraint.
		G.deckCount[p] = floor(Random() * (MAX_DECK / 4));
		G.discardCount[p] = floor(Random() * (MAX_DECK / 4));
		G.playedCardCount = floor(Random() * (MAX_DECK / 4));
		G.handCount[p] = floor(Random() * (MAX_DECK / 4));

		// Set a random supply postion that is valid as the choice
		choice = floor(Random() * (treasure_map + 1));

		

		// Check to see if the random gameState passes
		// the check.
		failures += check_feast(&G, choice);


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
