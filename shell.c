#include"cykshell.h"
#include <string.h>
int main(){
  char **a;
  char **c;
  char cp[1234];
  char b[10]="ls";
  init();
  while(1){ 
    prompt();
    fflush(stdout);
    rst();
    a=inputt();
    for(int i=0;i<no_of_cmds;i++){
      c=cmd_in(a[i]);
      cmd_exec(c);
    }
    bg_end();
  } 
}
