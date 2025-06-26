# 🚀 Minishell: A Custom Unix Shell





## ✨ Overview

Minishell is a challenging core project from 42 Paris, where the goal is to replicate key functionalities of the Bash shell in C. This project provided an in-depth exploration of Unix system programming, command parsing, and process management, pushing the boundaries of what a custom shell can achieve.
It was designed to deepen understanding of how operating systems interact with user commands, from interpreting input to executing external programs and managing environmental variables.

## 🌟 Key Features & Learnings

### Core Functionalities (Mandatory Part)

- Robust Input Parsing: Implemented a sophisticated command-line parser capable of handling single and double quotes, multiple commands, and various arguments.
- Command Execution: Ability to launch external executables from absolute, relative, or environment PATH (e.g., /bin/ls or ls).
- I/O Redirections: Support for standard input/output redirection (<, <<, >, >>).
- Pipes (|): Implemented inter-process communication using pipes, allowing the output of one command to serve as the input for another.
- Environment Variables: Management of environment variables (setting, unsetting, expansion like $HOME, and handling $? for return codes).
- Built-in Commands: Developed custom versions of essential shell built-ins:
	- echo [-n]
	- cd [path] (relative/absolute)
	- pwd
	- export
	- unset
	- env
	- exit

### Advanced Features (Bonus Part)

- Logical Operators: Implementation of && (AND) and || (OR) operators with parenthesis support for command grouping and priority.
- Wildcard Expansion: Support for * wildcard expansion in the current working directory, similar to Bash's globbing.
- Signal Handling: Proper handling of Unix signals (Ctrl-C for SIGINT, Ctrl-\ for SIGQUIT, Ctrl-D for EOF).

## 🛠️ Technologies Used

- Language: C
- Build System: Makefile
- Libraries: Standard C Library, system calls (e.g., fork, execve, waitpid, pipe, dup2).

## 🚀 How to Use

1. Clone the repository:

	`git clone https://github.com/yourusername/minishell.git`
	`cd minishell`



2. Build the executable:

	`make`



3. Run Minishell:

	`./minishell`


You will see a prompt, and can start typing commands!

##🎓 Learning Outcomes

This project was pivotal in deepening my understanding of:

- Unix System Programming: Mastery of fork(), execve(), waitpid(), pipe(), dup2(), and other crucial system calls.
- Process Management: How processes are created, managed, and interact within a Unix-like environment.
- Lexing & Parsing: Design and implementation of a robust parsing engine for complex command lines.
- Memory Management: Careful allocation and deallocation of memory in C.
- Error Handling: Robust error management for system calls and invalid user inputs.
