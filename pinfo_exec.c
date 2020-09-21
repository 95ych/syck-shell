#include"cykshell.h"
#include <string.h>

int pinfo_exec(char ** args){
	char path[buflen];
	char status[buflen];
	char mem[buflen];
	char exec[buflen];
	pid_t pid = (!args[1])? getpid(): atoi(args[1]);    //no arg provided , take self						
	sprintf(path, "/proc/%d/status", pid);                //proc directory has all information regarding processes
	printf("pid -- %d\n",pid);
	FILE *info =fopen(path, "r");
	if(!info){
		perror("proc_status file error");
		return 0;
	}
	int i=0;
	while(getline(&BUFFER,&blen,info)!=-1){
		if(strncmp("State",BUFFER,5)==0){
			strcpy(status,BUFFER+7);
			i++;
		}
		else if(strncmp("VmSize",BUFFER,6)==0){
			strcpy(mem,BUFFER+11);
			i++;
		}
		else if(i==2)
			break;

	}
	printf("Process Status -- %s",status);
	printf("memory -- %s",mem);
	fclose(info);
	sprintf(path, "/proc/%d/exe", pid);   //link to executable
	int exlen=readlink(path,exec,buflen); ////return value is no.of bytes read,-1 on error,and readlink doesent place null
	if(exlen<0)
		perror("sym link error");
	else{
		exec[exlen]='\0'; //NULL
		printf("executable -- %s\n",exec);  
	}
	
	return 1;
}