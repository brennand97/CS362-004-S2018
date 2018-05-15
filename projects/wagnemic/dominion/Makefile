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

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	echo "Result from running randomtestadventurer:" > randomtestadventurer.out
	rm -f dominion.gcda
	randomtestadventurer >> randomtestadventurer.out

	echo "" >> randomtestadventurer.out
	echo "File coverage:" >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	rm -f dominion.c.gcov

	echo "" >> randomtestadventurer.out
	echo "Function coverage:" >> randomtestadventurer.out
	gcov dominion.c
	tail -n+673 dominion.c.gcov | head -n41 >> randomtestadventurer.out	

randomtest1: randomtest1.c dominion.o rngs.o
	gcc -o randomtest1 randomtest1.c dominion.o rngs.o $(CFLAGS)

randomtest1.out: randomtest1
	echo "Result from running randomtest1:" > randomtest1.out
	rm -f dominion.gcda
	randomtest1 >> randomtest1.out

	echo "" >> randomtest1.out
	echo "File coverage:" >> randomtest1.out
	gcov dominion.c -b >> randomtest1.out
	rm -f dominion.c.gcov

	echo "" >> randomtest1.out
	echo "Function coverage:" >> randomtest1.out
	gcov dominion.c
	tail -n+814 dominion.c.gcov | head -n15 >> randomtest1.out	

randomtest2: randomtest2.c dominion.o rngs.o
	gcc -o randomtest2 randomtest2.c dominion.o rngs.o $(CFLAGS)

randomtest2.out: randomtest2
	echo "Result from running randomtest2:" > randomtest2.out
	rm -f dominion.gcda
	randomtest2 >> randomtest2.out

	echo "" >> randomtest2.out
	echo "File coverage:" >> randomtest2.out
	gcov dominion.c -b >> randomtest2.out
	rm -f dominion.c.gcov

	echo "" >> randomtest2.out
	echo "Function coverage:" >> randomtest2.out
	gcov dominion.c
	tail -n+713 dominion.c.gcov | head -n62 >> randomtest2.out	

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 unittest5.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 unittest5 cardtest1 cardtest2 cardtest3 cardtest4 dominion.o rngs.o
	echo "Result for running Unit Tests:" > unittestresults.out	
	
	echo "" >> unittestresults.out
	unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out	
	rm -f dominion.gcda
	unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out	
	rm -f dominion.gcda
	unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out	
	rm -f dominion.gcda
	unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "" >> unittestresults.out
	rm -f dominion.gcda
	unittest5 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	echo "Total unit test coverage:" >> unittestresults.out
	rm -f dominion.gcda
	unittest1 >> /dev/null
	unittest2 >> /dev/null
	unittest3 >> /dev/null
	unittest4 >> /dev/null
	unittest5 >> /dev/null
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	echo "" >> unittestresults.out
	echo "Results for running Card Tests:" >> unittestresults.out

	echo "" >> unittestresults.out
	rm -f dominion.gcda
	cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	rm -f dominion.gcda
	cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	rm -f dominion.gcda
	cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	rm -f dominion.gcda
	cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	echo "Total card test coverage:" >> unittestresults.out
	rm -f dominion.gcda
	cardtest1 >> /dev/null
	cardtest2 >> /dev/null
	cardtest3 >> /dev/null
	cardtest4 >> /dev/null
	gcov dominion.c -b >> unittestresults.out

	echo "" >> unittestresults.out
	echo "Total unit and card test coverage:" >> unittestresults.out
	rm -f dominion.gcda
	unittest1 >> /dev/null
	unittest2 >> /dev/null
	unittest3 >> /dev/null
	unittest4 >> /dev/null
	unittest5 >> /dev/null
	cardtest1 >> /dev/null
	cardtest2 >> /dev/null
	cardtest3 >> /dev/null
	cardtest4 >> /dev/null
	gcov dominion.c -b >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtest1 randomtest2
