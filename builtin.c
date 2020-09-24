#include"cykshell.h"
#include<string.h>

struct func_map builtins[bltin_no] ={{"echo",echo_b}, {"pwd",pwd_b}, {"ls",ls_exec}, {"pinfo",pinfo_exec}};
struct func_map builtins_notchild[bltin_notchild_count] ={ {"cd",cd_b}, {"exit",exit_b}, {"setenv", setenv_b}, {"unsetenv",unsetenv_b}};

int setenv_b(char** args){
	//printf("nof of args %d\n",no_of_args);
	if (no_of_args==1)
		printf("Insufficient arguments\n");
	
	else if(no_of_args>3)
		printf("Too many arguments\n");
	
	else if(no_of_args==2)
		if(setenv(args[1], "", 1) == -1)
			perror("setenv error ");
	
	else if(setenv(args[1], args[2], 1) == -1)
		perror("setenv error ");

	return 1;
}

int unsetenv_b(char** args){
	//printf("nof of args %d\n",no_of_args);
	if (no_of_args==1)
		printf("Insufficient arguments\n");
	
	else if(no_of_args>2)
		printf("Too many arguments\n");
	
	else
		if(unsetenv(args[1]) == -1)
			perror("cannot unset var");
		return 1;
}

int echo_b(char** args){
	int i=1;
	while(args[i]!=NULL){
		printf("%s ",args[i]);
		i++;
	}
	// if(i>1)
	printf("\n");
	return 1;
}


int pwd_b(char** args){
	printf("%s\n",cwd_s);    
	return 1;
}

int cd_b(char** args){
	char *cdr =calloc(buflen,sizeof(char)); 
	if(args[1]==NULL)
	{
		cdr=strdup(home);    //if nothing mentioned taking home by default
	}

	else if(args[1][0]=='~'){
		sprintf(cdr,"%s%s",home,args[1]+1);
	}
	else
		strcpy(cdr,args[1]); 
	
	if(chdir(cdr)<0)          
		perror("cd error ");
	cwd_func();					//setting up cwd_s
	//printf("home--%s cdr--%s",home,cdr);
	return 1;
}

int exit_b(char** args){
	exit(EXIT_SUCCESS);
}