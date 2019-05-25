CC = gcc
INC = -I include
CFLAGS = $(INC) -g

test_obj = ${shell find unit_test -name "*.c" | sed -e 's/\.c/\.o/g'}
obj = ${shell find src -name "*.c" | sed -e 's/\.c/\.o/g'}
test_target = test

.PHONY: test
test: $(test_obj) $(obj)
	$(CC) $^ -o $(test_target) -lcheck -lm -lpthread -lrt -lsubunit

.PHONY: clean
clean:
	rm $(test_target) $(obj) $(test_obj)
