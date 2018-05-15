/*
 * unittest3.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

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

	int non_coin = estate;
	int expected[3] = {0,6,5};
	int hand[3][5];

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("| Testing Function: %s\n", TESTFUNCTION);

    /* START TESTS */

    /* -------------------- TEST 1 --------------------*/
	strcpy(name,"Test 1");
	failures = 0;
    printf("|--> %s: %s\n", name, "Test to make sure function distinguishs between players + counts poperly");
    sprintf(indent, "| |-->");

	// Initialize the hands
	for (i = 0; i < 5; i++) {
		hand[0][i] = non_coin;
		hand[1][i] = non_coin;
		hand[2][i] = copper;
	}
	
	// Make second hand intresting
	hand[1][0] = silver;
	hand[1][3] = gold;
	hand[1][4] = copper;

	for (i = 0; i < 3; i++) {		
		// copy the game state to the test case
		memcpy(&testG, &G, sizeof(struct gameState));

		// Set proper players turn
		for (j = 0; j < i; j++) {
			endTurn(&testG);
		}

		// Fill player's hand
		for (j = 0; j < 5; j++) {
			testG.hand[i][j] = hand[i][j];
		}

		// test function
		updateCoins(i, &testG, 0);

		sprintf(buffer, "hand = ");
		for (j = 0; j < testG.handCount[i]; j++) {
			sprintf(buffer, "%s%d,", buffer, testG.hand[i][j]);
		}
		sprintf(buffer, "%s coins = %d, expected = %d", buffer, testG.coins, expected[i]);
		failures = safeAssert(testG.coins == expected[i], indent, buffer);
	}

    testTail(name, "| |", failures);
    if (failures) t_failures++;

    /* -------------------- TEST 2 --------------------*/
	strcpy(name,"Test 2");
    failures = 0;
    printf("|--> %s: %s\n", name, "Check to make sure the bonus works correctly");
    sprintf(indent, "| |-->");

	for (i = 0; i < 3; i++) {
		for (m = 1; m < 4; m++) {
			// copy the game state to the test case
			memcpy(&testG, &G, sizeof(struct gameState));

			// Fill players hand
			for (j = 0; j < 5; j++) {
				testG.hand[0][j] = hand[i][j];
			}

			updateCoins(0, &testG, m);

			memset(buffer, '\0', sizeof(buffer));	
			sprintf(buffer, "hand = ");
			for (j = 0; j < testG.handCount[0]; j++) {
				sprintf(buffer, "%s%d,", buffer, testG.hand[i][j]);
			}
			sprintf(buffer, "%s bonus = %d, coins = %d, expected = %d", buffer, m, testG.coins, expected[i] + m);
			failures = safeAssert(testG.coins == expected[i] + m, indent, buffer);

		}
	}

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
    testUpdateCoins();
    return 0;
}
