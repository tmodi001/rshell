MOVE = cd src;
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	$(MOVE) $(COMPILE) $(FLAGS) rshell.cpp -o rshell
	
rshell:
	$(MOVE) ./rshell
