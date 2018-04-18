CFLAGS = -Wall -fpic -coverage -lm -g

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: tests/unittest1.c dominion.o rngs.o
	gcc -o tests/unittest1 tests/unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: tests/unittest2.c dominion.o rngs.o
	gcc -o tests/unittest2 tests/unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: tests/unittest3.c dominion.o rngs.o
	gcc -o tests/unittest3 tests/unittest3.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: tests/unittest1.c tests/unittest2.c tests/unittest3.c dominion.o rngs.o
	echo "Result for running Unit Tests:" > unittestresults.out	
	echo "" >> unittestresults.out
	gcc -o tests/unittest1 tests/unittest1.c dominion.o rngs.o $(CFLAGS)
	tests/unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	gcc -o tests/unittest2 tests/unittest2.c dominion.o rngs.o $(CFLAGS)	
	tests/unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	gcc -o tests/unittest3 tests/unittest3.c dominion.o rngs.o $(CFLAGS)	
	tests/unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	echo "Total Coverage of all Tests:" >> unittestresults.out
	tests/unittest1 > /dev/null
	tests/unittest2 > /dev/null
	tests/unittest3 > /dev/null
	gcov dominion.c -b >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe tests/unittest1 tests/unittest2 unittestresults.out
