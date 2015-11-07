MOVE = cd src;
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	$(MOVE) $(COMPILE) $(FLAGS) main.cc -o rshell
	
rshell:
	$(MOVE) ./rshell
