CC = gcc
CFLAGS = -Wall -g
OBJ = string_manipulation_new.o strcmp.o strcpy.o strcat.o strlen.o
ASS = strcmp.s strcpy.s strcat.s strlen.s

all: string_manipulation.out 

string_manipulation_new.o: string_manipulation_new.c
	$(CC) -c -o $@ $^ $(CFLAGS)

%.o: $(ASS).s
	$(CC) -c -o $@ $< $(CFLAGS)

string_manipulation.out: $(OBJ)
	$(CC) -o $@ $^
