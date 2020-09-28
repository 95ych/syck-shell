#include"cykshell.h"
#include <signal.h>

void sighandlerc(int signum) {
   	if(!proc_run)	
   	{	
   		printf("\n");
	   	prompt();
	   	rst();
	   	fflush(stdout);
	}
}
void sighandlerz(int signum) {
   if(!proc_run)	
   	{	
   		printf("\n");
	   	prompt();
	   	rst();
	   	fflush(stdout);
	}
}