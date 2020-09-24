#include "cykshell.h"
#include <sys/types.h>
#include <signal.h>
int kjob_b(char** args){
	if(no_of_args>3){
		printf("Too many arguments\n");
		return 1;
	}
	if(no_of_args<3){
		printf("Too few arguments\n");
		return 1;
	}
	
	else{
		int jobid = atoi(args[1]);
		int sig = atoi(args[2]);
		//printf("bg_proc_size%d",bg_proc_size);		
		if(jobid < 1){
			printf("Invalid job no.\n");
			return 1;
		}
		if(sig > 31 || sig < 1){
			printf("Invalid signal\n");
			return 1;
		}
		int pid=-2;
		struct process *i =calloc(1,sizeof(struct process));
		i=bg_proc;
		for(int j=1;j<jobid;j++){
			i=i->next;
			
			if(!i){
				printf("No job found\n");
				return 1;
			}
		}
		pid=i->pid;
		if(kill(pid, sig)==-1)
			perror("kill error:");
		char* proc=calloc(buflen,sizeof(char));
		delbg(pid,proc,1);
		return 1;
	}


}

