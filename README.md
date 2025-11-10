# Simple Shell

A simple UNIX command line interpreter written in C.

## Description
This project is a basic recreation of a UNIX shell.  
It reads commands from the user, parses them, and executes them using system calls.

## Compilation
Compile all `.c` files using:

## Files
- `main.c` — Entry point of the shell  
- `parse_input.c` — Tokenizes user input  
- `execute_command.c` — Forks and executes commands  
- `find_path.c` — Finds full path for commands  
- `free_args.c` — Frees dynamically allocated memory  
- `_strcmp.c` — Custom string comparison function  
- `_getenv.c` — Gets environment variable values  
- `shell.h` — Header file with function prototypes and includes

## Author
- Your Name `<your.email@holbertonstudents.com>`

