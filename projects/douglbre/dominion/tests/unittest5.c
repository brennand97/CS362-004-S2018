/*
 * unittest3.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"

#define TESTFUNCTION "buyCard"
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

void testBuyCard() {
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

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("| Testing Function: %s\n", TESTFUNCTION);

    /* START TESTS */

    /* -------------------- TEST 1 --------------------*/
	strcpy(name,"Test 1");
	failures = 0;
    printf("|--> %s: %s\n", name, "Confirm that no card can be bought when no buys are left");
    sprintf(indent, "| |-->");

	// copy game state to test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.numBuys = 0;
	
	result = buyCard(0, &testG);
	
	sprintf(buffer, "result = %d, expected = %d", result, -1);
	failures += safeAssert(result == -1, indent, buffer);

	sprintf(buffer, "discardCount = %d, expected = %d", testG.discardCount[testG.whoseTurn], G.discardCount[testG.whoseTurn]);
	failures += safeAssert(testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn], indent, buffer);

	sprintf(buffer, "coins = %d, expected = %d", testG.coins, G.coins);
	failures += safeAssert(testG.coins == G.coins, indent, buffer);

	sprintf(buffer, "numbuys = %d, expected = %d", testG.numBuys, 0);
	failures += safeAssert(testG.numBuys == 0, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
    failures = 0;
    printf("|--> %s: %s\n", name, "Confirm that if no cards are avaiable to be bought it can't be");
    sprintf(indent, "| |-->");

	// copy game state to test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.supplyCount[0] = 0;

	result = buyCard(0, &testG);

	sprintf(buffer, "result = %d, expected = %d", result, -1);
	failures += safeAssert(result == -1, indent, buffer);

	sprintf(buffer, "discardCount = %d, expected = %d", testG.discardCount[testG.whoseTurn], G.discardCount[testG.whoseTurn]);
	failures += safeAssert(testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn], indent, buffer);

	sprintf(buffer, "coins = %d, expected = %d", testG.coins, G.coins);
	failures += safeAssert(testG.coins == G.coins, indent, buffer);

	sprintf(buffer, "numbuys = %d, expected = %d", testG.numBuys, G.numBuys);
	failures += safeAssert(testG.numBuys == G.numBuys, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 3 --------------------*/
	strcpy(name,"Test 3");
    failures = 0;
    printf("|--> %s: %s\n", name, "Confirm that if there are not enough coins you can't buy");
    sprintf(indent, "| |-->");

	// copy game state to test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.coins = 0;

	result = buyCard(1, &testG);

	sprintf(buffer, "result = %d, expected = %d", result, -1);
	failures += safeAssert(result == -1, indent, buffer);

	sprintf(buffer, "discardCount = %d, expected = %d", testG.discardCount[testG.whoseTurn], G.discardCount[testG.whoseTurn]);
	failures += safeAssert(testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn], indent, buffer);

	sprintf(buffer, "coins = %d, expected = %d", testG.coins, 0);
	failures += safeAssert(testG.coins == 0, indent, buffer);

	sprintf(buffer, "numbuys = %d, expected = %d", testG.numBuys, G.numBuys);
	failures += safeAssert(testG.numBuys == G.numBuys, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 4 --------------------*/
	strcpy(name,"Test 4");
    failures = 0;
    printf("|--> %s: %s\n", name, "Confirm that if there are zero coins I can still buy copper");
    sprintf(indent, "| |-->");

	// copy game state to test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.coins = 0;

	result = buyCard(0, &testG);

	sprintf(buffer, "result = %d, expected = %d", result, 0);
	failures += safeAssert(result == 0, indent, buffer);

	sprintf(buffer, "discardCount = %d, expected = %d", testG.discardCount[testG.whoseTurn], G.discardCount[testG.whoseTurn] + 1);
	failures += safeAssert(testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn] + 1, indent, buffer);

	sprintf(buffer, "coins = %d, expected = %d", testG.coins, 0);
	failures += safeAssert(testG.coins == 0, indent, buffer);

	sprintf(buffer, "numbuys = %d, expected = %d", testG.numBuys, G.numBuys - 1);
	failures += safeAssert(testG.numBuys == G.numBuys - 1, indent, buffer);

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 5 --------------------*/
	strcpy(name,"Test 5");
    failures = 0;
    printf("|--> %s: %s\n", name, "Confirm that if a card is bought all attributes are updated");
    sprintf(indent, "| |-->");

	// copy game state to test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	result = buyCard(1, &testG);

	sprintf(buffer, "result = %d, expected = %d", result, 0);
	failures += safeAssert(result == 0, indent, buffer);

	sprintf(buffer, "discardCount = %d, expected = %d", testG.discardCount[testG.whoseTurn], G.discardCount[testG.whoseTurn] + 1);
	failures += safeAssert(testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn] + 1, indent, buffer);

	sprintf(buffer, "coins = %d, expected = %d", testG.coins, G.coins - 2);
	failures += safeAssert(testG.coins == G.coins - 2, indent, buffer);

	sprintf(buffer, "numbuys = %d, expected = %d", testG.numBuys, G.numBuys - 1);
	failures += safeAssert(testG.numBuys == G.numBuys - 1, indent, buffer);

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
    testBuyCard();
    return 0;
}
