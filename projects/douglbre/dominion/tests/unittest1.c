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

int safeAssert(int condition, char* indent, char* description) {
    if (condition) {
        printf("%s PASSED: %s\n", indent, description);
        return 0;
    } else {
        printf("%s FAILED: %s\n", indent, description);
        return 1;
    }
}

void testHead(char* name, char** indent) {
    printf("|--> %s\n", name);
    sprintf(*indent, "| |-->");
}

void testTail(char* name, char* indent, int failures) {
    if(failures) {
        printf("%s >>> SUCCESS (%s): All asserts were successful <<<\n", indent, name);
    } else {
        printf("%s >>> FAILED (%s): %d of asserts failed <<<\n", indent, name, failures);
    }
    printf("|\n");
}

void testEndTurn() {
    int failures = 0, t_failures = 0;
    char buffer[100], indent[20];

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	             sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("| Testing Function: %s\n", TESTFUNCTION);

    /* START TESTS */

    /* TEST 1 */
    failures = 0;
    testHead("Test 1", &indent);



    testTail("Test 1", indent, failures);
    if (!failures) t_failures++;

    /* TEST 2 */
    failures = 0;
    testHead("Test 2", &indent);

    

    testTail("Test 2", indent, failures);
    if (!failures) t_failures++;


    /* FINISHED ALL TESTS */

    if(t_failures) {
        printf("|--> >>>>>> SUCCESS (%s): All tests passed <<<<<<\n", TESTFUNCTION);
    } else {
        printf("|--> >>>>>> FAILED (%s): %d tests failed <<<<<<\n", TESTFUNCTION, t_failures);
    }

}

int main() {
    testEndTurn();
    return 0;
}