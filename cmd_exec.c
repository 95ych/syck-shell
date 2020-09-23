#include"cykshell.h"
#include<string.h>
#include<unistd.h>
#include<sys/wait.h> 

int builtin_notchild_exec(char** args){
	for(int i=0; i<bltin_notchild_count;i++)            //check for builtin functions
		if(!strcmp(builtins_notchild[i].name, args[0]))
			return builtins_notchild[i].func(args);
	return 0;
}

int builtin_exec(char** args){
	for(int i=0; i<bltin_no;i++)            //check for builtin functions
		if(!strcmp(builtins[i].name, args[0]))
			return builtins[i].func(args);
	return 0;
}
int bg_check(char** args){
	if(!strcmp(args[no_of_args-1],"&")){
		no_of_args--;
		args[no_of_args]=NULL;
		return 1;
	}
	else if( args[no_of_args-1][strlen(args[no_of_args-1])-1]=='&'){
		args[no_of_args-1][strlen(args[no_of_args-1])-1]='\0';
		return 1;
	}
	return 0;
}


int cmd_exec(char **args){
		pid_t pid, wpid;
		int status, bg=0;
		//printf("no of args %d ", no_of_args);
		//fflush(stdout);
		if(args[0]==NULL)
			return 1;
		if(builtin_notchild_exec(args)) // should not executed as child process 
			return 1;							 //edit assgn3: in case of ioredir, proceed as child
		bg = bg_check(args);
		pid = fork();
		if (pid == 0) {                     // Child process
		    if(bg) 
		    	if(setpgrp()<0)              //moving the process into a new process grp to cutoff i/o interaction
		    		perror("error allocating for bg process");
		    if(ioredir(args)==-1) 			//look for io redirects
		    	exit(0);					//in case of error
		    if(builtin_exec(args));
		    else if (execvp(args[0], args) == -1){
		    	//perror("No command found");
		    	fprintf(stderr,"Unknown command\n");
		    }
			exit(0);
		}
	  	else if (pid < 0) {
	    	perror("fork failed");
	    	exit(1);
	  	} 
	  	else{                            //Parent process
		  	if(!bg){
		  		wait(NULL);       // if not a background process wait till child completes
	  		}
	  		else{                    //else append to linked list of process
				struct process *new =calloc(1,sizeof(struct process));
				new->pid=pid;
				strcpy(new->name,args[0]);
				new->next=NULL;
				if(!bg_proc)
					bg_proc=new;
				else{
					struct process *i=bg_proc;
					while(i->next)
						i=i->next;
					i->next=new;
				}
				bg_proc_size++;
				//sleep(1);		 //to print errors from child bg process before prompt
	  		}

	  	}
  	return 1; 
}
void delbg(pid_t pid, char* proc,int b){          //delete bg process from list if b=1, and get process name for pid
	bg_proc_size--; 
    struct process *i = bg_proc;

    if(i->pid == pid){			
        strcpy(proc,i->name);
        fflush(stdout);
        i=i->next;
        if(b)
        	free(i);
        return;
    }
    while(i->next){              
        if(i->next->pid == pid){
        	struct process *del=i->next;
            strcpy(proc,del->name);
            if(b){
            	i->next = del->next;
            	free(del);
            }
            return ;
        }
        i=i->next;
    }

}


void bg_end(){			//to display end of bg process
	int status;
	do{	
	    pid_t wpid = waitpid(-1, &status, WUNTRACED | WNOHANG);
		if(wpid<=0){
	        return;
	    }
	    char* proc=calloc(buflen,sizeof(char));
		blen=0; 
	    if (WIFEXITED(status)){  //if bg proc exited
	    	delbg(wpid,proc,1);
	    	fprintf(stderr,"\n%s with pid %d exited normally with status %d\n",proc, wpid, WEXITSTATUS(status));
	    }
	    else if(WIFSIGNALED(status)){ 	//if bg proc killed by signal
	    	delbg(wpid,proc,1);
	    	fprintf(stderr,"\n%s with pid %d exited due to a kill signal %d\n",proc, wpid, WTERMSIG(status));
	    }
	    else if (WIFSTOPPED(status)) { 		//if bg proc stopped by signal
            delbg(wpid,proc,0);
            fprintf(stderr,"%s with pid %d stopped by signal %d\n", proc, wpid, WSTOPSIG(status));
 
         } 
        else if (WIFCONTINUED(status)) {
            delbg(wpid,proc,0);
            fprintf(stderr,"%s with pid %d continued\n", proc, wpid);
         }
 
		
	}while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

