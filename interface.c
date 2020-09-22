#include "cykshell.h"
#include <errno.h>
#include <sys/utsname.h>
#include <string.h>

char** cmd_in(char* cmd){                         //splits command into arguments
char **args = calloc(arglen , sizeof(char*));     //an array of pointers to store cmdument's pointers
  char *arg=NULL;                    //pointer to store pointer returned by strtok   
  if(cmd == NULL)
    return args;
  arg=strtok(cmd,DELIM);
  int i=0;
  while(arg!=NULL){
    args[i]=arg;
    arg=strtok(NULL,DELIM);           //to return the next pointer of prev buffer's cmdument
    i++;                          //hopefully i <100
  }
  no_of_args=i;
  //printf("args%d",no_of_args);
  //fflush(stdout);
  args[no_of_args]=NULL;
  return args;
}

char* inputt(){
    if (getline(&BUFFER, &blen, stdin) == -1){
    if (feof(stdin))                  //if eof is recieved like ctrl-D, exit shell
          exit(EXIT_SUCCESS); 
      else {
          perror("input");
          exit(EXIT_FAILURE);
      }
    }
    return BUFFER;
}


char** stringseperator(char* BUF, char* delim, int* cnt){                                    //splits input to commands
	char **cmds = calloc(arglen, sizeof(char*));			//an array of pointers to store cmdument's pointers
	char *cmd;											//pointer to store pointer returned by strtok 	

	cmd=strtok(BUFFER, delim);
	int i=0;
	int j=1;
	while(cmd!=NULL){
		cmds[i]=cmd;
		cmd=strtok(NULL, delim); 							//to return the next pointer of prev buffer's cmdument
		i++;
		if(i>j*100){
			j++;
      //TODO: realloc for safety;
		}
  		    	          				
  }
	*cnt=i;
  return cmds;
}


void cwd_func(){
	getcwd(cwd, sizeof(cwd));
	if(strlen(cwd) >= strlen(home) && strncmp(cwd, home, strlen(home)) == 0)
        sprintf(cwd_s, "~%s", cwd + strlen(home));
    else
    	sprintf(cwd_s, "%s", cwd);
}


void init(){
	mgn();
	getlogin_r(user, buflen);
   	gethostname(host, buflen);
   	getcwd(home, buflen);
   	cwd_func();
	printf("                           Welcome to \n");
	printf("****************************cykshell******************************\n");
	printf("                      Have a nice day %s :) \n\n",user);	
}


void prompt(){ 
	grn();
	printf("<");
  cyn();
  printf("%s",user);
  grn();
  printf("@");
  cyn();
  printf("%s ",host);
  blu();
  printf("%s", cwd_s);
  grn();
  printf(">");
  fflush(stdout);
  return;
}