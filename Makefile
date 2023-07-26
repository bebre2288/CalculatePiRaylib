CFLAGS=-Wall -Wextra -Werror -pedantic
CLIBS=-L. -L/usr/local/include -I. -I/usr/local/include -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS=
CC=clang
all: compile

compile:
	$(CC) $(CFLAGS) main.c -o run $(CLIBS)

run: compile
	./run
