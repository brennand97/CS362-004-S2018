/*
 * cardtest2.c
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

void testCard_smithy() {
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
    printf("|--> %s: %s\n", name, "Check the functionality of the smithy card");
    sprintf(indent, "| |-->");

	G.hand[0][1] = smithy;

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, 0, 0, 0, &testG, 1, NULL);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 2);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 2, indent, buffer);

	sprintf(buffer, "played cards count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
	failures += safeAssert(testG.playedCardCount == G.playedCardCount + 1, indent, buffer);

	sprintf(buffer, "played card = %d, expected = %d", testG.playedCards[testG.playedCardCount - 1], smithy);
	failures += safeAssert(testG.playedCards[testG.playedCardCount - 1] == smithy, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
    failures = 0;
    printf("|--> %s: %s\n", name, "Check to make sure smithy only draws up to the amount of cards in the deck");
    sprintf(indent, "| |-->");

	G.deckCount[0] = 2;

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, 0, 0, 0, &testG, 1, NULL);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 1);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 1, indent, buffer);

	sprintf(buffer, "played cards count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
	failures += safeAssert(testG.playedCardCount == G.playedCardCount + 1, indent, buffer);

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
    testCard_smithy();
    return 0;
}
