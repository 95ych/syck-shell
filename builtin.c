#include"cykshell.h"
#include<string.h>

struct func_map builtins[bltin_no] ={{"echo",echo_b}, {"pwd",pwd_b}, {"cd",cd_b}, {"ls",ls_exec}, {"pinfo",pinfo_exec}, {"exit",exit_b}};

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