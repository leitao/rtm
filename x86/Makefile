CC=gcc
CFLAGS=-I. -mrtm -Wall -g
OBJS = hello.o

%.o : %.c
	$(CC) $(CFLAGS) $@ $<

hello: $(OBJ)
