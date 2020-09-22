#include"cykshell.h"
#include<sys/wait.h>

/*
	Pipe(pipefd) syscall sets the fd value
	for pipefd[0] for read and pipefd[1] for write.
	Here for commands in middle , we ll
	be needing 2 pipes,one to read from
	one to write into.
 */
//return 0 if no pipe, else 1;
int piping(char* cmd){
	char **pipecoms = calloc(arglen, sizeof(char*));
	int rpipefd[2], lpipefd[2]; //right pipe and left pipe,(l and r wrt even no. coms)
	int stdincp = dup(0);
	int stdoutcp = dup(1); //creating backup for stdin and stdout
	int no_of_pipecoms;    //no of commands
	pipecoms = stringseperator(cmd, "|", &no_of_pipecoms);
	//printf("pinpcoms %d\n",no_of_pipecoms);
	if(no_of_pipecoms==1)
		return 0;
	
	//for first command
	pipe(rpipefd);    
	dup2(rpipefd[1],1);
	int pid=fork();
	if(pid==-1){
		dup2(stdoutcp,1);
		dup2(stdincp,0);
		perror("fork error");
		return 1;
	}
	else if(pid==0){
		cmd_exec(cmd_in(pipecoms[0]));
		exit(0); //incaseof builtin or error;
	}
	else{
		wait(NULL);
		close(rpipefd[1]);
	}
	int i;
	for (i=1;i<no_of_pipecoms-1;i++){
 		//l and r wrt even no. commands
 		if(i%2){		
 			pipe(lpipefd);
 			dup2(lpipefd[1],1);
 			dup2(rpipefd[0],0); 
 		}
 		else{ 
 			pipe(rpipefd);
 			dup2(rpipefd[1],1);
 			dup2(lpipefd[0],0);
 		}
        pid = fork();
        if(pid==-1){
			dup2(stdoutcp,1);
			dup2(stdincp,0);
			perror("fork error");
			return 1;
		}
        else if(pid==0){
            cmd_exec(cmd_in(pipecoms[i]));
            exit(0);
        }
        else{
            wait(NULL);
            if(i%2){
            	close(rpipefd[0]);
            	close(lpipefd[1]);
         	}
			else{
				close(lpipefd[0]);
				close(rpipefd[1]);
			}
        }
    }
    
    //last command
	dup2(stdoutcp,1);
	if(i%2) dup2(rpipefd[0],0);
 	else dup2(lpipefd[0],0);
 
	pid=fork();
	if(pid==-1){
		dup2(stdoutcp,1);
		dup2(stdincp,0);
		perror("fork error");
		return 1;
	}
	else if(pid==0){
		cmd_exec(cmd_in(pipecoms[i]));
		exit(0); //incaseof builtin or error;
	}
	else{
		wait(NULL);
		if(i%2) close(rpipefd[0]);
		else close(lpipefd[0]);
		dup2(stdincp,0);
	}
	//printf("pipe ended....\n");
	return 1;
}