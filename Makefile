CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

all: polynomial

polynomial: src/main.c src/polynomial.c include/polynomial.h
	$(CC) $(CFLAGS) src/main.c src/polynomial.c -o polynomial

test_polynomial: tests/test_polynomial.c src/polynomial.c include/polynomial.h
	$(CC) $(CFLAGS) tests/test_polynomial.c src/polynomial.c -o test_polynomial

run: polynomial
	./polynomial

demo: polynomial
	./polynomial --demo

test: test_polynomial
	./test_polynomial

clean:
	rm -f polynomial test_polynomial polynomial.exe test_polynomial.exe