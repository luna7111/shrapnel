# Shrapnel

Shrapnel is a custom Unix-like shell that replicates core functionality of standard shells such as Bash, Dash and Sh.

## Features

Shrapnel supports the essential features you would expect from a shell. It handles both built-in and external commands with support for arguments, pipes, i/o redirection and enviroment variable expansion.
As a little easter egg, if you run the "shnake" command inside shrapnel a built-in command-line snake game will show up, more on that later :p

## Built-in functions

cd: Changes the working directory of the program.  
echo: Prints text and variables to the standard output.  
env: Displays the current enviroment variables.  
exit: Exits the Shrapnel with optional status codes.  
export: Sets or updates enviroment variables.  
unset: Removes enviroment variables.  
pwd: Displays the current working directory.  
shnake: Runs the builtin command-line shnake game.  

## Shnake

The shnake command was really fun to implement, as this project was made complying with the 42 Minishell subject, there weren't any allowed functions you would expect to use when making a game, so here are some of the turnarrounds i made:

### Random number generation
The apple position goes to a random place in the grid whenever the snake eats it, to generate pseudo-random numbers without using an already existing funcion like rand() i made a function that takes a static int and makes a bunch of arbitrary operations with some of the game variables.
To avoid deterministic behaviour one of those variables is a pointer allocated using malloc, which should be totally unpredictable to the user.

### Wait function
I hated this one. There wasn't any time/wait/sleep functions like usleep() allowed, so the only way i had to make the program "wait" was using busy wait.
So the function just takes a really big number and iterates it to keep the processor bussy. Compilers REALLY want to optimize stuff so i used a volatile variable to avoid the compiler omiting the seemingly unnecesary loop.
The problem with this one is the wait time depends too much on the speed of the processor, so the snake will go too fast on some computers and painfully slow on others.
The biggest issue with this implementation is that if you are too lucky with cache hits, the snake will instantly hit a wall at the start of the game.

### Input
So, no library to directly check keyboard input BUT i had read(), ioctrl() and tcsetattr() which alowed me to put the terminal in raw mode (get input byte by byte instead of full lines like canonical mode) and check if there is any input to read before calling read() so the program doesn't get stuck waiting for any input to read.
I also used a somewhat big buffer in the read() calls, this is to clear the buffer so that if you push a key for a long time the program doesn't have to read every single byte.

This part of the project was really fun to make! I always enjoy having to work without some of the things i usually take for granted. :D
