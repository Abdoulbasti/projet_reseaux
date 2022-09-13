CC=gcc
INCLUDE=./include/
BIN=./bin/
SRC=./src/
SEFLAGS=-I$(INCLUDE) -pthread -Wall -Wextra -O1 -o

init: clean bin compileserver

bin:
	mkdir $(BIN)

clean:
	rm -rf $(BIN)/*
	rm -rf $(BIN)

compileserver:
	$(CC) $(SEFLAGS) $(BIN)server $(SRC)server/server.c