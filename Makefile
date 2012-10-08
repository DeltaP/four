MPICC=mpicc
CXX=g++
CXXFLAGS  = -g -Wall -std=c99 -Wextra -DEBUG

all: pingpong 

pingpong: pingpong.c
	${MPICC} $(CXXFLAGS)   $^ -o $@  
	@printf 'Linked\n'

clean: 	
	rm -f *.o pingpong

new: clean all

.PHONY: all new clean
