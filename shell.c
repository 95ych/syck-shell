#include"cykshell.h"
#include <string.h>
int main(){
  char* a=calloc(buflen,sizeof(char));
  char** asp;
  char** c;
  char cp[1234];
  char b[10]="ls";
  init();
  while(1){ 
    
    prompt();
    fflush(stdout);
    rst();
    a=inputt();
    asp=stringseperator(a,DELIMC,&no_of_cmds);
    
    for(int i=0;i<no_of_cmds;i++){
      if(piping(asp[i]))
        continue;
      c=cmd_in(asp[i]);
      cmd_exec(c);
    }
    
    bg_end();
  
  } 
}
