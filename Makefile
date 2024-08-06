NAME = snuif
CC = tcc

CFLAGS = -g -Wall -Wextra -Iinc
LDFLAGS = -L/usr/lib

SRC = $(wildcard src/*.c)

.PHONY: clean test all

all: build

build:
	mkdir -p bin
	$(CC) -o bin/$(NAME) $(CFLAGS) $(LDFLAGS) $(SRC)

install: all
	cp bin/$(NAME) /usr/local/bin/
	chmod a+rx /usr/local/bin/$(NAME)

uninstall:
	rm -f /usr/local/bin/$(NAME)

clean:
	rm -f bin/$(NAME)
