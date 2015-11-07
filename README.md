name1 = Tirth Modi

name2 = Michael Pena


-----------------------------
Command Shell - An Overview
-----------------------------
This program takes in user input to run bash commands such as ls and echo.
Standard syntax for these commands are allowed, including spaces, operators, 
and arguments. 

To Run, type:
make
make rshell

and compile and execute the program.
To end the program, type exit.

-----------------------------
Format
-----------------------------
A normal bash terminal will continually take in user input until they enter
exit. This means we had to create our program to do the same, continually take
user input until the user entered exit. 

One of the challenges of this was to use c strings as the function we used
for executing, execvp, required c strings as arguments. This also didn't work
with certain spaces and other formatting, meaning we had to prepare and format
what the user inputted through functions we created, our check and separate
functions. 

We created the check and separate functions with optimization in mind. One 
thing we could have improved on was breaking down the separate function into
possibly two functions, as the separate function was longer than it should
have been. We considered having another function as a helper for separate to 
remove the spaces in the beginning and the end, however we decided against it 
due to time constraints. Ultimately this could have led to a neater separate 
function, but was not completely necessary. 

Another problem with the separate function is it could have been shorter if 
we combined the || and && sections with smaller less repetitive if statements.
This would have made it much cleaner, but does not affect performance much.

-----------------------------
Known Bugs and Issues
-----------------------------
There are some known issues with the code. One is we did not participate in
the extra credit opportunity to include the logged in user name and hostname 
of the machine or server. Ultimately more time spent could have allowed this
feature to be added, but is at least something to address if we continue 
production and further testing.

Another problem is exit can sometimes not work if exit is entered following an
invalid prompt option, it will fail to exit and nothing will occur. Further 
testing and experimenting would be needed to locate the issue and how to 
resolve it.
