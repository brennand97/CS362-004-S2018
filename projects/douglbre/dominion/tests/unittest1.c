/*
 * unittest1.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"

#define TESTFUNCTION "endTurn"
#define NOISY 1

int safeAssert(int condition, char* indent, char* description) {
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
        printf("%s >>> SUCCESS (%s): All asserts were successful <<<\n", indent, name);
    } else {
        printf("%s >>> FAILED (%s): %d asserts failed <<<\n", indent, name, failures);
    }
    printf("|\n");
}

void testEndTurn() {
    int failures = 0, t_failures = 0;
    char buffer[100], indent[20], name[100];

	int i;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 3;
	int currentPlayer = 0;
    struct gameState G, testG, testG_p;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("| Testing Function: %s\n", TESTFUNCTION);

    /* START TESTS */

    /* -------------------- TEST 1 --------------------*/
	strcpy(name,"Test 1");
	failures = 0;
    printf("|--> %s: %s\n", name, "Check to make sure all attributes are properly set");
    sprintf(indent, "| |-->");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// offset values (to confirm update later)
	testG.outpostPlayed = (int) (Random() * 1020) + 4;
	testG.phase = (int) (Random() * 1020) + 4;
	testG.numActions = (int) (Random() * 1020) + 4;
	testG.numBuys = (int) (Random() * 1020) + 4;
	testG.playedCardCount = (int) (Random() * 1020) + 4;

	endTurn(&testG);

	// Check to make sure the current player was updated
	sprintf(buffer, "whose turn = %d, expected = %d", testG.whoseTurn, currentPlayer + 1);
	failures += safeAssert(testG.whoseTurn == currentPlayer + 1, indent, buffer);

	// Check to make sure handCount is zero
	sprintf(buffer, "hand count pervious player = %d, expected = %d", testG.handCount[currentPlayer], 0);
	failures += safeAssert(testG.handCount[currentPlayer] == 0, indent, buffer);

	// Check to make sure discard pile increased by handCount
	sprintf(buffer, "discard pile count = %d, expected = %d", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + G.handCount[currentPlayer]);
	failures += safeAssert(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + G.handCount[currentPlayer], indent, buffer);

	// Check to make sure new player has 5 cards
	sprintf(buffer, "new player hand count = %d, expected = %d", testG.handCount[testG.whoseTurn], 5);
	failures += safeAssert(testG.handCount[testG.whoseTurn] == 5, indent, buffer);
	
	// Check to make sure all values were updated
	sprintf(buffer, "outpost played = %d, expected = %d", testG.outpostPlayed, 0);
	failures += safeAssert(testG.outpostPlayed == 0, indent, buffer);

	sprintf(buffer, "phase = %d, expected = %d", testG.phase, 0);
	failures += safeAssert(testG.phase == 0, indent, buffer);

	sprintf(buffer, "num actions = %d, expected = %d", testG.numActions, 1);
	failures += safeAssert(testG.numActions == 1, indent, buffer);

	sprintf(buffer, "num buys = %d, expected = %d", testG.numBuys, 1);
	failures += safeAssert(testG.numBuys == 1, indent, buffer);

	sprintf(buffer, "played card count = %d, expected = %d", testG.playedCardCount, 0);
	failures += safeAssert(testG.playedCardCount == 0, indent, buffer);


    testTail(name, "| |", failures);
    if (!failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
    failures = 0;
    printf("|--> %s: %s\n", "Test 2", "Check to make sure whose turn wraps around");
    sprintf(indent, "| |-->");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    for (i = 0; i < numPlayers; i++) {
		// Run endTurn
		endTurn(&testG);

		// Check to make sure whose turn increments in a circular pattern
		sprintf(buffer, "whose turn = %d, expected = %d", testG.whoseTurn, (i + 1) % numPlayers);
		failures += safeAssert(testG.whoseTurn == (i + 1) % numPlayers, indent, buffer);
	}

    testTail("Test 2", "| |", failures);
    if (!failures) t_failures++;


    /* -------------- FINISHED ALL TESTS --------------*/

    if(t_failures) {
        printf("| >>> SUCCESS (%s): All tests passed 1<<<\n", TESTFUNCTION);
    } else {
        printf("| >>> FAILED (%s): %d tests failed <<<\n", TESTFUNCTION, t_failures);
    }

}

int main() {
    testEndTurn();
    return 0;
}
