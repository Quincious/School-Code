#Jonathan Hart
#Assignment 1 readme file

myshell.c description:
This version does not include history functionality. 
-The code runs entirely in an infinite while loop. It should never break out of it without exiting the code completely.
-All command handling are done in the executecmd() function.
-Takes input and transforms it to be used in the execvp() function
-Once input is parsed, the program will quit or fork and execute the command
-Shell will wait if pid > 0
-If an unknown command or command outside the specs is entered, it will respond accordingly and then exit that process. This is considered a successful exit as it is intend to do this.

myhistory.c description:
-includes all code from myshell.c
-a history global array was added to hold all previous commands, possibly switch to linked list in future
-a historycount global variable was added to hold number of history 
-before a cmd is added to the history array, if the count is the max for the array, the program will eliminate the oldest command. Another solution could be extending array but to me, there is no need to remember over a hundred commands
-the program then adds the command to the history array and increases the count
-if history command was entered, the program will output the history then return for next command
-if no history command, the program will operate as normal

