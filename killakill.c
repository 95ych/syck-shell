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
		
		if(bg_proc==NULL){
			printf("No job found\n");
			return 1;
		}
		int pid=-2;
		struct process *i;
		char* proc=calloc(buflen,sizeof(char));
		i=bg_proc;
		if (jobid==1){
			if(kill(bg_proc->pid,sig)==-1)
				perror("kill error:");
			//delbg(bg_proc->pid,proc,1);
			return 1;
		}

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
		//delbg(pid,proc,1);
		return 1;
	}
}

int overkill_b(char** args){
	//printf("no_of_args%d",no_of_args);
	if(no_of_args>1){
		printf("Too many arguments");
		return 1;
	}
	struct process *i, *j;
	i=bg_proc;
	while(i){
		int pid=i->pid;
		if(kill(pid, 9)==-1)  //dont do kill(-1,9), lol it kills everything xD
				perror("kill error:");
		j=i->next;
		i=j;
		//printf("killing");
	}
	//bg_proc=NULL;
return 1;	
}
