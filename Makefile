NAME = snuif
CC = tcc

CFLAGS = -g -Wall -Wextra -Iinc
LDFLAGS = -L/usr/lib

SRC = $(wildcard src/*.c)

.PHONY: clean test all

all: build

build:
	$(shell mkdir -p bin)
	$(CC) -o bin/$(NAME) $(CFLAGS) $(LDFLAGS) $(SRC)

clean:
	rm -f bin/$(NAME)
