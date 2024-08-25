NAME = snuif
CC = gcc

CFLAGS = -g -Wall -Wextra -Iinc $(shell pkg-config --cflags libpcap)
LDFLAGS = -L/usr/lib $(shell pkg-config --libs libpcap)

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: clean test all

all: clean proj

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

proj: $(OBJ)
	$(shell mkdir -p bin)
	$(CC) -o bin/$(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)


