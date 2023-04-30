EXEC = proj2
CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
OUT = proj2
SEMFLAGS = -pthread -lrt

.PHONY: clean all

all: $(EXEC)

$(EXEC): proj2.o
	$(CC) $(CFLAGS) -o $(EXEC) proj2.o $(SEMFLAGS)

proj2.o: proj2.c
	$(CC) $(CFLAGS) -c proj2.c $(SEMFLAGS)

clean:
	rm -f $(EXEC) proj2.o proj2.out