RM=rm
CC=gcc
CFLAGS=-g -I. -I../ -I../../../typeclass
OBJ1=${shell find ../ -maxdepth 1 -name "*.c" | sed -e 's/\.c/\.o/g'}
OBJ = main.o $(OBJ1)
test: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) -f $(OBJ) test
