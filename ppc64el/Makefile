CC=gcc
CFLAGS=-I. -mhtm -Wall -g
OBJS = htm.o

%.o : %.c
	$(CC) $(CFLAGS) $@ $<

htm: $(OBJ)
