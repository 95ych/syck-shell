## SHELL in C
A shell with basic functionalities with io redirections and piping support. \
It can run system commands ,both in foreground and in background. \
For compiling the shell run
```bash
foo@bar>./make
```
for running it
```bash
foo@bar>./shell
```
#### Has some builtin commands:
* `echo`
* `cd`
* `pwd`
* `pinfo`
* `ls` , with -a , -l flags supported
* `exit`, `quit`
* `setenv`
* `unsetenv`
* `jobs`
* `fg`
* `bg`
* `kjob`
* `overkill`

#### Limitations:
* Doesen't support quoting arguments or whitespace escape.

#### What i,ve learnt from this assignment:
Basic functionalities of shell and how processes execute \
Expisure to new system calls and library functions \
Modular coding\
Understanding how io, redirections and piping works

##### Debugging pain gains:
* End the input with NULL if using malloc to avoid random chars in buffer, or simply use calloc.
* Not to run certain builtin commands as child processes, example: cd when run as child , it changes directory and exits, but parent ends up remaining in the same directory.
* Not to allocate strings pointers directly for a variable, we can end up messing up the orginal string, so make a duplicate of it by strdup() or strcpy()  
* While implementing ctrl-z when the process stopped, i tried send the child process to new group by setpgid(pid,0), but it gave permission error;\
Fix: Irrespective of whether bg of fg process, i sent the child to new group, if it is an fg ,in the parent interface it with terminal's io by tcsetpgrp(0, pid);

#### Structure:
* `cykshell.h` : the header file having main libraries, global constants , variables and functions.
* `shell.c` : main() function;
* `interface.c` : functions related to interface
  >`init()`: initialises the terminal,</br>
 `prompt()`: displays prompt in the terminal
,</br> `cwd_func()`: stores current working directory shortened and previous directory</br> `inputt()`: takes in input splits it into commands</br> `cmd_in()`: takes in command splits into arguments</br>
`stringseperator()`: takes a string and return array of strings splitted with delimter


* `cmd_exec.c` : Command execution takes place</br>
  > `cmd_exec()`: takes in arguments of a command and executes it. </br> `buitlin_exec()`: executes builtin commands.</br> `bg_check()`: check if it is a bg process.</br> `bg_end()`: display if background process ends.</br>`delbg()` to get process name of pid and delete if neccesary.

* `colours.c` : just storing few colour functions
* `builtin.c` : few small builtin functions pwd_b() cd_b() echo_b() exit_b()
* `ls_exec.c` : ls command by ls_exec() function
* `pinfo_exec` : pinfo command by pinfo_exec() function
* `ioredir.c` : ioredir() function for redirections.
* `pipe.c` : for piping the commands
* `killakill.c` : kjob and overkill implementation.
* `jobsrelated.c` : jobs , fg and bg implementation
* `signalhandler.c` : signal handling for ctrl-c and ctrl-z

Assignment 3 bonus: `cd -`

(P.S: The code was compiled in arch distro, it wasnt compiling unless -fcommon was used, if it doesent compile, pls use appropriate flags in makefile and try again. \
Thank you)
