/*
 * cardtest3.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "great_hall"
#define NOISY 1

int silent = 0;

int safeAssert(int condition, char* indent, char* description) {
	if (silent) { return !condition; }
    if (condition) {
		if (NOISY) {
			printf("%s passed: %s\n", indent, description);
		} else {
			printf("%s passed\n", indent);
		}
        return 0;
    } else {
		if (NOISY) {
			printf("%s !-> FAILED: %s\n", indent, description);
		} else {
			printf("%s !-> FAILED\n", indent);
		}
        return 1;
    }
}

void testTail(char* name, char* indent, int failures) {
	printf("%s\n", indent);
    if(failures == 0) {
        printf("%s>>> SUCCESS (%s): All asserts were successful <<<\n", indent, name);
    } else {
        printf("%s>>> FAILED (%s): %d asserts failed <<<\n", indent, name, failures);
    }
    printf("|\n");
}

void testCard_greatHall() {
    int failures = 0, t_failures = 0;
    char buffer[100], indent[20], name[100];

	int i, j, m;
	int result;

    int seed = 1000;
    int numPlayers = 3;
	int currentPlayer = 0;
    struct gameState G, testG, testG_p;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, council_room};

	int non_card, card;

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("| Testing card: %s\n", TESTCARD);

    /* START TESTS */

    /* -------------------- TEST 1 --------------------*/
	strcpy(name,"Test 1");
	failures = 0;
    printf("|--> %s: %s\n", name, "Test functionality of the card effect");
    sprintf(indent, "| |-->");

	G.hand[0][1] = great_hall;

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(great_hall, 0, 0, 0, &testG, 1, NULL);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0]);
	failures += safeAssert(testG.handCount[0] == G.handCount[0], indent, buffer);

	sprintf(buffer, "deck count = %d, expected = %d", testG.deckCount[0], G.deckCount[0] - 1);
	failures += safeAssert(testG.deckCount[0] == G.deckCount[0] - 1, indent, buffer);
    
	sprintf(buffer, "actions = %d, expected = %d", testG.numActions, G.numActions + 1);
	failures += safeAssert(testG.numActions == G.numActions + 1, indent, buffer);

	sprintf(buffer, "played count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
	failures += safeAssert(testG.playedCardCount == G.playedCardCount + 1, indent, buffer);

	sprintf(buffer, "played card = %d, expected = %d", testG.playedCards[0], great_hall);
	failures += safeAssert(testG.playedCards[0] == great_hall, indent, buffer);
	
	testTail(name, "| |", failures);
    if (failures) t_failures++;
    
	/* -------------- FINISHED ALL TESTS --------------*/

    if(!t_failures) {
        printf("|>>> SUCCESS (%s): All tests passed <<<\n", TESTCARD);
    } else {
        printf("|>>> FAILED (%s): %d tests failed <<<\n", TESTCARD, t_failures);
    }

}

int main() {
    testCard_greatHall();
    return 0;
}
