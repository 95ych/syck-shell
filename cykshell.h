#ifndef HEADER
#define HEADER

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DELIMC ";\n"
#define DELIM " \t\r\n\v" //delim for strtok func.
#define buflen 1024       //giving buffer length of 1024 chars
#define arglen 100        //assuming upto max 100 arguments
#define bltin_no 5
#define bltin_notchild_count 8
#define maxproc 1024      //assuming can hold upto 1024 processes

char user[buflen];
char host[buflen];
char home[buflen];
char cwd[buflen];
char cwd_s[buflen];        //pwd_s for cwd shortened
char cdminus[buflen];
int no_of_args;
int no_of_cmds;
int proc_run;
int z;
char* inputt();
char** stringseperator();
char** cmd_in();
void delbg(pid_t pid, char* proc,int b);
int ls_exec(char **args); 
int pinfo_exec(char **args); 
int jobs_b(char **args);
int bg_b(char **args);
int fg_b(char **args);
int kjob_b(char** args);  
int pwd_b(char **args);    //builtin pwd
int echo_b(char **args);   //builtin echo 
int cd_b(char **args);
int exit_b();
int setenv_b(char** args);
int unsetenv_b(char** args);
int overkill_b(char ** args);
int cmd_exec(char **args);
int ioredir(char** args);
void cwd_func();
void bg_end();
struct func_map { char *name;
 				  int (*func)(char **args);
 				};
int piping(char* cmd);
struct func_map builtins[bltin_no];
//functions that not meant to be run as child processes and hence not with i/o redir too.
struct func_map builtins_notchild[bltin_notchild_count];
char *BUFFER;
size_t blen;
struct process {pid_t pid;
			 	char name[buflen];
			 	struct process *next;
				};

struct process *bg_proc;
int bg_proc_size;
int sepcount;
void sighandlerc(int signum);
void sighandlerz(int signum);
//colours for shell
void red();
void grn();
void blu();
void ylw();
void cyn();
void mgn();
void rst();
void init();
void prompt();
#endif