CC = gcc
CFLAGS = -Wall -g

# $(shell mkdir -p out)

all: ungetc_1

ungetc_1: ungetc_1.c
	$(CC) $^ -o out/$@ $(CFLAGS)

clean:
	rm out/*