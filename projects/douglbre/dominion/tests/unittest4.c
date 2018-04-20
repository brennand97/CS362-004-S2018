/*
 * unittest3.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"

#define TESTFUNCTION "fullDeckCount"
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

void testFullDeckCount() {
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

    printf("| Testing Function: %s\n", TESTFUNCTION);

    /* START TESTS */

    /* -------------------- TEST 1 --------------------*/
	strcpy(name,"Test 1");
	failures = 0;
    printf("|--> %s: %s\n", name, "Test to make sure each card can be found in each pile");
    sprintf(indent, "| |-->");

	for (i = 0; i < 24; i++) {
		
		if (i == 0) {
			non_card = 23;
		} else {
			non_card = i - 1;
		}

		// set test game state
		memcpy(&testG, &G, sizeof(struct gameState));

		// set cards
		for (j = 0; j < testG.handCount[0]; j++) {
			testG.hand[0][j] = non_card;
		}
		for (j = 0; j < testG.deckCount[0]; j++) {
			testG.deck[0][j] = non_card;
		}
		testG.hand[0][2] = i;

		// test function
		result = fullDeckCount(0, i, &testG);

		sprintf(buffer, "count = %d, expected = %d", result, 1);
		failures += safeAssert(result == 1, indent, buffer);


		// set test game state
		memcpy(&testG, &G, sizeof(struct gameState));

		// set cards
		for (j = 0; j < testG.handCount[0]; j++) {
			testG.hand[0][j] = non_card;
		}
		for (j = 0; j < testG.deckCount[0]; j++) {
			testG.deck[0][j] = non_card;
		}
		testG.discardCount[0] = 1;
		testG.discard[0][0] = i;

		// test function
		result = fullDeckCount(0, i, &testG);

		sprintf(buffer, "count = %d, expected = %d", result, 1);
		failures += safeAssert(result == 1, indent, buffer);


		// set test game state
		memcpy(&testG, &G, sizeof(struct gameState));

		// set cards
		for (j = 0; j < testG.handCount[0]; j++) {
			testG.hand[0][j] = non_card;
		}
		for (j = 0; j < testG.deckCount[0]; j++) {
			testG.deck[0][j] = non_card;
		}
		testG.deck[0][0] = i;

		// test function
		result = fullDeckCount(0, i, &testG);

		sprintf(buffer, "count = %d, expected = %d", result, 1);
		failures += safeAssert(result == 1, indent, buffer);
	}

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
    failures = 0;
    printf("|--> %s: %s\n", name, "Test when all decks are full with one card");
    sprintf(indent, "| |-->");

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	card = copper;
	non_card = smithy;

	// set cards
	for (j = 0; j < testG.handCount[0]; j++) {
		testG.hand[0][j] = card;
	}
	for (j = 0; j < testG.deckCount[0]; j++) {
		testG.deck[0][j] = card;
	}
	testG.discardCount[0] = 3;
	for (j = 0; j < testG.discardCount[0]; j++) {
		testG.discard[0][j] = card;
	} 

	// test function
	result = fullDeckCount(0, card, &testG);

	sprintf(buffer, "count = %d, expected = %d", result, testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0]);
	failures += safeAssert(result == testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0], indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 3 --------------------*/
	strcpy(name,"Test 3");
    failures = 0;
    printf("|--> %s: %s\n", name, "Test when all decks don't have the card");
    sprintf(indent, "| |-->");

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	card = copper;
	non_card = smithy;

	// set cards
	for (j = 0; j < testG.handCount[0]; j++) {
		testG.hand[0][j] = non_card;
	}
	for (j = 0; j < testG.deckCount[0]; j++) {
		testG.deck[0][j] = non_card;
	}
	testG.discardCount[0] = 3;
	for (j = 0; j < testG.discardCount[0]; j++) {
		testG.discard[0][j] = non_card;
	} 

	// test function
	result = fullDeckCount(0, card, &testG);

	sprintf(buffer, "count = %d, expected = %d", result, 0);
	failures += safeAssert(result == 0, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;
    
	/* -------------- FINISHED ALL TESTS --------------*/

    if(!t_failures) {
        printf("|>>> SUCCESS (%s): All tests passed <<<\n", TESTFUNCTION);
    } else {
        printf("|>>> FAILED (%s): %d tests failed <<<\n", TESTFUNCTION, t_failures);
    }

}

int main() {
    testFullDeckCount();
    return 0;
}
