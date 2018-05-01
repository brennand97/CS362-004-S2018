CFLAGS = -Wall -fpic -coverage -lm -g

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

all: testme

run: testme
	./testme

runfilter: testme
	./testme | grep error

clean:
	rm -f *.o *.gcov *.gcda *.gcno testme
