# minishell
As beautiful as a shell

* [Introduction](#Introduction)
* [Installation & Usage](#Installation_&_Usage)
* [Mandatory](#Mandatory)
* [Builtins implemented](#builtins_implemented)
* [Step by step](#step_by_step)

* [Study resources](#study_resources)
* [libft functions](#libft_functions)

## Introduction         🤔

The objective of this project is to create a simple shell and learn a lot about processes and file descriptors

Minishell is 42's second largest project. It's a minimum viable version of a real shell. The main objective is to have a good understanding of creating and synchronizing processes using the C programming language.


## Installation & Usage ❕

1. Download/Clone this repo

        git clone https://github.com/kazuumaVII/minishell.git
2. `cd` into the root directory and run `make`

        cd minishell
        make

3. After building the source `./minishel` from the project root.


## Mandatory 🌐

- Can only use C
- Must respect the school imposed coding style ([The Norme][norme-pdf])
- No memory leaks
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit

## builtins_implemented

command | description  |
---|------|
**echo** | echo the STRING(s) to standart output. **-n** flag: do not output the trailing newline |
**cd** | change the shell working directory	(with a relative or absolute path)|
**pwd** | print name of current/working directory	|
**export** | set export attribute for shell variables | 
**unset** | unset values of shell variables |
**env** | print the environment	| 
**exit** | cause the shell to exit with the exit status specified	| 
