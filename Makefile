CC = gcc
CFLAGS = -Wall -std=c11
RM = rm

OBJS = manager.o
OUT = manager

all: clean $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

clean:
	$(RM) -f $(OUT) $(OBJS)