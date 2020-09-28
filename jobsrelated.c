#include"cykshell.h"
#include <string.h>
#include <signal.h>
int jobs_b(char** args){
	struct process *i =calloc(1,sizeof(struct process));
	i=bg_proc;
	int no=1;
	if(!i){
		printf("No jobs running\n");
		fflush(stdout);
		return 1;
	}
	while(i){
		//printf("running jobs:\n");
		printf("[%d] ",no);
		fflush(stdout);
		char path[buflen];
		char status[buflen];						
		sprintf(path, "/proc/%d/status", i->pid);                //proc directory has all information regarding processes
		FILE *info =fopen(path, "r");
		
		if(!info){
			perror("proc_status file error");
			return 1;
		}

		while(getline(&BUFFER,&blen,info)!=-1){
			if(strncmp("State:   ",BUFFER,5)==0){
				strcpy(status,BUFFER+7);
				//printf("status%s",status);
				break;
			}
		}
	
	switch(status[0]){
		case 'T':printf("Stopped "); break;
		case 'R':printf("Running "); break;
		case 'S':printf("Sleeping (interruptible) "); break;
		case 'D':printf("Sleeping (uninterruptible) "); break;
		case 'Z':printf("Zombie "); break;
		default: printf("Unknown ");
	}
	printf("%s [%d]\n",i->name, i->pid);
	i=i->next;
	no++;
	}
	
	return 1;
}
/*
   R  running or runnable (on run queue)
   D  uninterruptible sleep (usually IO)
   S  interruptible sleep (waiting for an event to complete)
   Z  defunct/zombie, terminated but not reaped by its parent
   T  stopped, either by a job control signal or because
      it is being traced
 */

int bg_b(char** args){

    if(no_of_args < 2){
        printf("bg: Too few arguments\n");
        return 1;
    }
    if(no_of_args > 2){
        printf("bg: Too many arguments\n");
        return 1;
    }

    int jobid = atoi(args[1]);
    int pid=-2;
	struct process *i;
	char* proc=calloc(buflen,sizeof(char));
	i=bg_proc;
    
    if (jobid==1){
		if(kill(bg_proc->pid,SIGCONT)==-1)
			perror("bg error:");
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
	if(kill(pid, SIGCONT)==-1)
		perror("bg error:");

}
