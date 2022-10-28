CC ?= gcc
CFLAGS += -Wall --pedantic -g

all:
	$(CC) $(LDFLAGS) -o dames $(CFLAGS) dames.c main.c

test:
	$(CC) $(LDFLAGS)  -o dames_tests $(CFLAGS) tests/test_main.c dames.c -lcunit

clean:
	rm -f *.o dames_tests dames
