### 42 Minishell

The existence of shells is linked to the very existence of IT. At the time, all coders agreed that communicating with
a computer using aligned 1/0 switches was seriously irritating. It was only logical that they came up with the idea 
to communicate with a computer using interactive lines of commands in a language somewhat close to english. The 
objective of this project is to create a simple shell in C.

This project is a 42 school's duo project. The core achievement of the project was that it helped us  get to the core
of the Unix system and explore an important part of this system’s API: process creation, input parsing and 
synchronisation.

## Introduction to the project

The behavior of the minishell is heavily based on the bash behavior. For every point, take [bash](https://www.gnu.org/software/bash/manual/bash.pdf) as a reference. It is implemented with the rules described below.

__implement the following builtins:__

- `echo` and the `-n` option
- `cd` only with an absolute or relative path
- `pwd` without any options
- `export` without any options
- `unset` without any options
- `env` without any options or arguments
- `exit` without any options

__The function to be implemented in the project__

- Display a prompt while waiting for a new order.
-  Find and launch the correct executable (based on a PATH environment variable
or using an absolute path).
- `<<` in the command line must open a heredoc and take input like bash.
- `’`and `"` must work as in bash, except multiline.
- The `<`,`>` and `>>` redirectionss must work as in bash, except for
aggregations of fd.
-  Pipes redirections `|`.
- The environment variables ($ followed by characters) must work.
- `$?` variable.
- `ctrl-C`, `ctrl-D` and `ctrl- \` signals should have the same behavior.

## Implementation and organization of the project

> ⚠️ **Warning**: Don't copy/paste code you don't understand: it's bad for you, and for the school.

The current project is built for Linux. If you want to run it on Mac, please change the Makefile accordingly 
by specifying the place of the needed libraries (for example readline).

The project consists of several folders that are presented below.

__includes:__
	The following folder contains the minishell.h file, which consists of the includes of external libraries, function
	headers created in this project and the declaration of the structs used in the project.

__libft:__
	This folder represents the library created during the Libft 42 project. It contains many useful functions that
	helped during the project.

__srcs:__
	This folder contains the main functions of the project.

	`main.c:` The main function of the project.
	`signal.c:` The functions used for signal handling.
	`execute.c:` The file that contains the ft_exec function. 
	`parse_and_execute.c:` The file that is responsible for parsing the line and executing the commands.
	
	`parse:` The folder containing all the files related to parsing.
	`env:` The folder containig util functions workig with environment variables. 
	`builtins:` The folder containing the implementations of the builtin commands.

__utils:__
	This folder contains the util functions used by this project.

## Installation

To use this project you need to clone this repository, by running the following command

```
git clone https://github.com/42YerevanProjects/42_minishell.git
```
Then you should go to the cloned repo and run the make command

```
cd 42_minishell
make
```
After that you will see the executable minishell. Lastly you should run the executable

```
./minishell
```
You will be provided with a prompt and can use it as a shell.

## Credits

WE got help from a 42 school student [aisraely](https://github.com/Mampacuk). He explained us the logic of the code and helped to test it.

## Additional info

In order to understand the project requirements well you can read the subject file of the project. Moreover, if you
copy the code from this repository then you have to specify the author of the code and referrence this repository. If
you find any bugs in the code please write to the issues.
