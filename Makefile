MPICC=mpicc
CXX=g++
CXXFLAGS  = -g -Wall -std=c99 -Wextra -DEBUG

all: pingpong sn_pingpong

pingpong: pingpong.c
	${MPICC} $(CXXFLAGS)   $^ -o $@  
	@printf 'Linked\n'

sn_pingpong: sn_pingpong.c
	${MPICC} $(CXXFLAGS)   $^ -o $@  
	@printf 'Linked\n'

clean: 	
	rm -f *.o pingpong sn_pingpong

new: clean all

.PHONY: all new clean
