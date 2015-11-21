name1 = Tirth Modi

name2 = Michael Pena

-----------------------------
Command Shell - An Overview
-----------------------------
This program takes in user input to run bash commands such as ls and echo.
Standard syntax for these commands are allowed, including spaces, operators, 
and arguments. 

This has been expanded on to include test, including the [] operators, and to 
allow for precedence operators (). Comments have also been revised and are 
working fully.

-----------------------------
Design
-----------------------------
We designed our program to take input through the main, with a loop to 
continually take user input until the user enters "exit". As the user enters 
their commands, the commands are pushed to our dummy function, a function 
designed to determine if a comment was made in the command. This function 
also checks against the user putting the comment symbol, #, inside a quote or 
not.

After this, commands are pushed in through our par_function. This function
checks if the commands passed in contain any parentheses. If there isn't, 
it simply moves to our separate function. If there is however, we break up the
commands into three parts, a beginning part before the first parentheses, the 
stuff inside any parentheses, and the part after the final parentheses. 
Conditions are checked and maintained when deciding whether or not to run the
commands after operators such as || or &&. These commands are recursively put 
through our par_function, and ultimately end up passed into separate when they 
finally have no more parentheses.

Our separate function is the main function we use to break up our commands 
through their operators when parentheses are no longer involved. The function 
breaks up the commands based off which operator gets detected first. It will 
then branch off depending on which, if any, get detected. If a || or && get 
detected, it will go to the branches designed for those, run the first 
command, then check if it should continue with the ones that follow. If it 
should, it pushes the rest of the commands back into a recursive call on 
separate, and goes until our base case. Our base case is if there is just a 
single command with no operators, which simply get run. These branches also 
help prepare the commands for the execute function, removing unnecessary spaces
through our check function, and moving commands into their temporary strings. 
In each of these branches, we also check if the user has a test or [] command 
to run, in which case we would break off into our test_command function, a 
function designed to check and run any test commands. This will check for flags
and ensure that that the commands are valid commands, using its helper function
fileExists and directoryExists. 

Our execute function is the function actually capable of running the commands. 
This function forks into two separate processes, a parent and a child, where 
the child runs the command and the parent waits for it. We set it up for if the
user enters an invalid command, an error message is printed. many of our 
functions return a bool based off this function and is the prime way we 
determine if a command successfully executed or not.

We have expanded on our functions from last time by adding new ones, such as 
the test_command and par_function functions to make it slightly cleaner, as 
our separate function was already larger than we wished for it to be from the 
first assignment. By creating these functions and some helper functions, we 
were able to break our code up into neater blocks.
-----------------------------
Known Bugs and Issues
-----------------------------
There are a few bugs we have found during testing. One is echos with quotes 
that involve a semicolon are not outputted correctly. This is due to our 
quote checking in our dummy function not expanding enough to catch these to fix
them. Another known issue involving quotes is if any | or & symbols are in 
quotes for the echo as well. This could be solved through a revamp in our 
separate function to check against such errors. Finally, if the word "test" is 
used in quotes, the function will falsely assume that the user is attempting 
to run a test command. Again, a revamp to our separate function could solve 
this issue.

Other than quotes, we also have problems with long strimgs of commands and 
operators failing to execute the proper commands when the || operator is used. 
An example of this is echo A || echo B || echo C || echo D, which should only 
print an A, however prints out other letters as well. The problem is once 
again somewhere in our separate function, and could also be resolved through 
a revamp of the function. 
