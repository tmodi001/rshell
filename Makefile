MOVE = cd src;
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	$(MOVE) $(COMPILE) $(FLAGS) almost.cpp -o rshell
	
rshell:
	$(MOVIE) ./rshell
