# Shrapnel

Shrapnel is a custom Unix-like shell that replicates core functionality of standard shells such as Bash, Dash and Sh.

## Features

Shrapnel supports the essential features you would expect from a shell. It handles both built-in and external commands with support for arguments, pipes, i/o redirection and enviroment variable expansion.
As a little easter egg, if you run the "shnake" command inside shrapnel a built-in command-line snake game will show up, [more on that later :p](#shnake)

## Built-in functions

- **cd:** Changes the working directory of the program.  
- **echo:** Prints text and variables to the standard output.  
- **env:** Displays the current enviroment variables.  
- **exit:** Exits the Shrapnel with optional status codes.  
- **export:** Sets or updates enviroment variables.  
- **unset:** Removes enviroment variables.  
- **pwd:** Displays the current working directory.  
- **shnake:** Runs the builtin command-line shnake game.  

## Development overview

This was a pair group project, we decided to modilarize the project in a way that let us work in our part without slowing the other down.
We wanted to learn the most out of this project, so we decided to try different data structures for different parts of the project. For example the enviroment management benefited from the flexibility of a linked list, while commands are stored in an array list.
I also wanted to understand more about dinamic memory, so i took the time to make a custom memory management library which was really usefull due to the memory independence of each module of the shell.

### Modules

Here is a breakdown of the major components:

- **Read-line input:** Shows a prompt to the user and waits for input.  
- **Pretokenization:** To avoid enviroment variable contents to be interpreted as redirections or pipes, the input is sliced and assigned one of two flags (TEXT or SYMBOL). Then all enviroment variables are expanded.  
- **Tokenization:** Input is again sliced, now with more descriptive identifyers (COMMAND, HEREDOC, FILENAME...)
- **Redirection:** All the logic of pipes, redirections, heredocs, file descriptors and command arguments is managed here. I like to think about this step as generating a list of well structured instructions to make execution as easy and not a -mess(ish) as possible.
- **Execution:** Finds the command in the PATH if it isn't a relative, or absolute path, or a built-in command. Duplicates the received file descriptors in the STDIN and STDOUT if necessary and executes the command, making sure to free all unneeded memory and file descriptors.

## Shnake

The shnake command was really fun to implement, since this project was made complying with the 42 Minishell subject constraints, I couldn't use any allowed functions you would expect to use when making a game, so here are some of the turnarrounds i made:

### Random number generation
  
To place apples at random grid positions, I needed pseudo-random numbers, but rand() and similar functions weren’t allowed.  
I wrote a function that uses a static integer and mixes it with arbitrary operations involving game variables. To avoid deterministic behaviour one of those variables is a pointer returned by malloc(), which introduces some unpredictability due to memory address randomness.

### Wait function
There were no sleep/wait functions like usleep() available nor time management like gettimeofday() to adjust speeds. So I implemented a busy-wait loop using a volatile variable to prevent compiler optimization.  
Sadly the speed of the snake depends entirely on CPU speed. It runs way too fast on some machines and painfully slow on others and if you are too lucly with cache hits, out reptile friend will hit a wall instantly :(.

### Input
So, no library to directly check keyboard input BUT i had read(), ioctrl() and tcsetattr() which alowed me to put the terminal in raw mode (get input byte by byte instead of full lines like canonical mode) and check if there is any input to read before calling read() so the program doesn't get stuck waiting for any input to read.
I also used a somewhat big buffer in the read() calls, this is to clear the buffer so that if you push a key for a long time the program doesn't have to read every single byte.

This part of the project was really fun to make! I always enjoy having to work without some of the things i usually take for granted. :D
