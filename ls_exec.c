#include"cykshell.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int ls_exec(char **args){
	int l=0,a=0;                     //for flags
	int dir_i=0;	          	     //for storing arg no. for dir
	char *dir = NULL;                //for storing directory name
	struct dirent **namelist; 
	for(int i=1; i<no_of_args ;i++){
		if(strcmp(args[i],"-l")==0)
			l=1;
		
		else if(!strcmp(args[i],"-a"))
			a=1;
		
		else if(!strcmp(args[i],"-al") || !strcmp(args[i],"-la")){
			l=1;a=1;
		}
		else if (strcmp(args[i],"")!=0){           //non-empty arg other than flag is dir
		  dir_i = i;
		}
	}
	if(dir_i ){
		if(args[dir_i][0]=='~'){
			dir=home;
			strcat(dir,args[dir_i]+1);
		}
		else{
			dir=args[dir_i];
		}
	}
	else dir = ".";                  //no dir mentioned, hence current one
	int no_of_files = scandir(dir,&namelist,NULL,alphasort);
	//printf("%d %d",l,a);
	//printf(" %d %s ",no_of_files,dir);
	if(no_of_files < 0)
		perror("ls error ");
	else{
		
		for(int i=0;i<no_of_files;i++){
			if(namelist[i]->d_name[0]!='.' || a){
				if(l){
					struct stat statbuf;
					char *path = namelist[i]->d_name;
					if (stat(path, &statbuf) != 0){
						printf("%s ",namelist[i]->d_name);
					    perror("error:");
					}
					
					else{
						struct passwd *user_s = getpwuid(statbuf.st_uid); //user struct
						struct group *group_s = getgrgid(statbuf.st_gid); //group struct
						printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
						printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
					    printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
					    printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
					    printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
					    printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
					    printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
					    printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
					    printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
					    printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
					    printf(" %2ld ", statbuf.st_nlink);
					    if (user_s == 0){
						    perror("user error");
						}
						else printf(" %s ",user_s->pw_name);
						if (group_s == 0)
						{
						    perror("group error");
						}
						else printf(" %s ",group_s->gr_name);
					    char date_time[16];
    					strftime(date_time, 16, "%b %2d %2I:%2M", gmtime(&(statbuf.st_mtime)));
    					printf("%s ",date_time);

				    }
				}
				printf("%s\n",namelist[i]->d_name);
			}
		}
	}
	return 1;
}