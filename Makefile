EXEC = proj2
CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
OUT = proj2
SEMFLAGS = -pthread -lrt

.PHONY: clean all

all: $(EXEC)

$(EXEC): *.o
	$(CC) $(CFLAGS) -o $(EXEC) *.o $(SEMFLAGS)

*.o: *.c
	$(CC) $(CFLAGS) -c *.c $(SEMFLAGS)

clean:
	rm -f $(EXEC) proj2.o proj2.out