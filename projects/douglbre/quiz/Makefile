CFLAGS = -Wall -fpic -coverage -lm -g

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

all: testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno testme
