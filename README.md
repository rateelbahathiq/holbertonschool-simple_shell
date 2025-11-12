# Simple Shell

A simple UNIX command line interpreter written in C.

## Description
This project is a basic recreation of a UNIX shell.  
It mimics a subset of the features of the standard shell (`sh`), including:
- Displaying a prompt and waiting for the user to type a command.
- Executing simple commands with arguments.
- Handling commands found in the `PATH`.
- Implementing the built-in commands: `exit` and `env`.

## Compilation
Compile all `.c` files using:

## Features
- Displays a prompt and waits for user input.
- Executes commands found in the PATH.
- Handles command arguments.
- Built-in commands:
  - exit – exits the shell.
  - env – prints the current environment.


## Files
- `main.c` — Entry point of the shell  
- `parse_input.c` — Tokenizes user input  
- `execute_command.c` — Forks and executes commands  
- `path.c` — Finds full path for commands  
- `free_args.c` — Frees dynamically allocated memory  
- `_strcmp.c` — Custom string comparison function  
- `_getenv.c` — Gets environment variable values  
- `main.h` — Header file with function prototypes and includes
- `run.c` — Executes commands and built-ins
- `helpers.h`— Utility functions


## Examples
### 0.1— Basic Shel
Task: Display a prompt, read input, execute simple one-word commands (no arguments).

```bash
$ ./hsh
($) /bin/ls
README.md shell.c main.c
($)
```

### 0.2 — Handle PATH
Task: Allow commands without full path (search in PATH).
The shell should not call fork() if the command doesn’t exist.

```bash
$ ./hsh
($) ls
README.md main.h main.c
($) fakecommand
./hsh: 1: fakecommand: not found
($)
```

###0.3 — Exit Built-in
Task: Implement the built-in command exit that terminates the shell.

```bash
$ ./hsh
($) ls
main.c run.c
($) exit
$
```

###0.4 — Env Built-in
Task: Implement the env built-in command that prints the current environment variables.

```bash
$ ./hsh
($) env
USER=julien
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/julien
($) exit
$
```


## Author
- Rateel Bahathiq `<rateelbahathiq@gmail.com>`
- Rateel Bahathiq `<your.email@holbertonstudents.com>`

