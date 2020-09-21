#include"cykshell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int ioredir(char** args){
	int iodir = 0;
	for(int i=0;args[i]!=NULL;i++){
		if(!strcmp(args[i],"<")){
			int fd = open(args[i+1], O_RDONLY);
			if (fd < 0)  
		    { 
		        perror("ioredir error");  
		    }
		    dup2(fd,0);
		    close(fd);
		    iodir=1;
		    args[i]=NULL; //to execute arg[0] without irrevelant args
		}
		else if(!strcmp(args[i],">")){
			int fd = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)  
		    { 
		        perror("ioredir error");  
		    }
		    dup2(fd,1);
		    close(fd);
		    iodir=1;
		    args[i]=NULL; //to execute arg[0] without irrevelant args
		}
		else if (!strcmp(args[i],">>")){
			int fd = open(args[i], O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd < 0){
				perror("ioredir error");
			}
			dup2(fd,1);
			close(fd);
			iodir=1;
			args[i]=NULL; //to execute arg[0] without irrevelant args
		}
	}
	return iodir;
}

