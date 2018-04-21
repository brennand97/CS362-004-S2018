/*
 * cardtest1.c
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

void testCard_adventurer() {
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
    printf("|--> %s: %s\n", name, "Check that card works when deck is full of copper.");
    sprintf(indent, "| |-->");

	// set the deck to a known state
	for (i = 0; i < G.deckCount[0]; i++) {
		if (i > 1) {
			G.deck[0][i] = copper;
		} else {
			G.deck[0][i] = estate;
		}
	}

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

	sprintf(buffer, "deck count = %d, expected = %d", testG.deckCount[0], G.deckCount[0] - 2);
	failures += safeAssert(testG.deckCount[0] == G.deckCount[0] - 2, indent, buffer);

	sprintf(buffer, "discard count = %d, expected = %d", testG.discardCount[0], G.discardCount[0]);
	failures += safeAssert(testG.discardCount[0] == G.discardCount[0], indent, buffer);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 2);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 2, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
	failures = 0;
    printf("|--> %s: %s\n", name, "Check that card works when deck is full of silver.");
    sprintf(indent, "| |-->");

	// set the deck to a known state
	for (i = 0; i < G.deckCount[0]; i++) {
		G.deck[0][i] = silver;
	}

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

	sprintf(buffer, "deck count = %d, expected = %d", testG.deckCount[0], G.deckCount[0] - 2);
	failures += safeAssert(testG.deckCount[0] == G.deckCount[0] - 2, indent, buffer);

	sprintf(buffer, "discard count = %d, expected = %d", testG.discardCount[0], G.discardCount[0]);
	failures += safeAssert(testG.discardCount[0] == G.discardCount[0], indent, buffer);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 2);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 2, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 3 --------------------*/
	strcpy(name,"Test 3");
	failures = 0;
    printf("|--> %s: %s\n", name, "Check that card works when deck is full of gold.");
    sprintf(indent, "| |-->");

	// set the deck to a known state
	for (i = 0; i < G.deckCount[0]; i++) {
		G.deck[0][i] = gold;
	}

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

	sprintf(buffer, "deck count = %d, expected = %d", testG.deckCount[0], G.deckCount[0] - 2);
	failures += safeAssert(testG.deckCount[0] == G.deckCount[0] - 2, indent, buffer);

	sprintf(buffer, "discard count = %d, expected = %d", testG.discardCount[0], G.discardCount[0]);
	failures += safeAssert(testG.discardCount[0] == G.discardCount[0], indent, buffer);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 2);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 2, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 4 --------------------*/
	strcpy(name,"Test 4");
    failures = 0;
    printf("|--> %s: %s\n", name, "Check if it can find treasure in the discard pile");
    sprintf(indent, "| |-->");

	G.discardCount[0] = 2;
	G.discard[0][0] = silver;
	G.discard[0][1] = gold;

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

	sprintf(buffer, "deck count = %d, expected = %d", testG.deckCount[0], G.deckCount[0] + G.discardCount[0] - testG.discardCount[0] - 2);
	failures += safeAssert(testG.deckCount[0] == G.deckCount[0] + G.discardCount[0] - testG.discardCount[0] - 2, indent, buffer);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0] + 2);
	failures += safeAssert(testG.handCount[0] == G.handCount[0] + 2, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 5 --------------------*/
	strcpy(name,"Test 5");
    failures = 0;
    printf("|--> %s: %s\n", name, "Check if it fails if there is no treasure.");
    sprintf(indent, "| |-->");

	// set the deck to a known state
	for (i = 0; i < G.deckCount[0]; i++) {
		G.deck[0][i] = estate;
	}
	G.discardCount[0] = 0;

	// set test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	result = cardEffect(adventurer, 0, 0, 0, &testG, 0, NULL);

	sprintf(buffer, "result = %d, expected = %d", result, -1);
	failures += safeAssert(result == -1, indent, buffer);

	sprintf(buffer, "hand count = %d, expected = %d", testG.handCount[0], G.handCount[0]);
	failures += safeAssert(testG.handCount[0] == G.handCount[0], indent, buffer);
	
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
    testCard_adventurer();
    return 0;
}
