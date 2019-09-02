VPATH = src
CC = g++

OBJS = util.o \
	algo.o \
	gen.o \

all: main test

main: main.o bench.o $(OBJS)
test: test.o $(OBJS)


.PHONY: clean

clean:
	rm *.o -rf
