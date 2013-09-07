CFLAGS=-Wall -Wextra -std=c99 -fno-exceptions
CPPFLAGS=-Wall -Wextra -std=c++0x -fno-rtti -fno-exceptions -Wno-unused-parameter
LDFLAGS=

CFLAGS+=-g
CPPFLAGS+=-g

#CFLAGS+=-O2
#CPPFLAGS+=-O2

CC=gcc
CXX=g++

SOURCES = voronoi.cpp point.cpp

COBJS:= $(patsubst %.c,%.o, $(SOURCES))
OBJS= $(patsubst %.cpp, %.o, $(COBJS))
CLEANUP= test test.o $(OBJS)

# RULES

all: test

test: test.o $(OBJS)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)

clean:
	rm -rf $(CLEANUP)
