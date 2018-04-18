/*
 * unittest3.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"

#define TESTFUNCTION "updateCoins"
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

void testUpdateCoins() {
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
    printf("|--> %s: %s\n", name, "N/A");
    sprintf(indent, "| |-->");


    testTail(name, "| |", failures);
    if (!failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
    failures = 0;
    printf("|--> %s: %s\n", name, "N/A");
    sprintf(indent, "| |-->");


    testTail(name, "| |", failures);
    if (!failures) t_failures++;

    /* -------------------- TEST 3 --------------------*/
	strcpy(name,"Test 3");
    failures = 0;
    printf("|--> %s: %s\n", name, "N/A");
    sprintf(indent, "| |-->");

	
	testTail(name, "| |", failures);
    if (!failures) t_failures++;

    /* -------------- FINISHED ALL TESTS --------------*/

    if(t_failures) {
        printf("|>>> SUCCESS (%s): All tests passed <<<\n", TESTFUNCTION);
    } else {
        printf("|>>> FAILED (%s): %d tests failed <<<\n", TESTFUNCTION, t_failures);
    }

}

int main() {
    testUpdateCoins();
    return 0;
}
