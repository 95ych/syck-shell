main: 
	gcc  interface.c colours.c cmd_exec.c builtin.c  ls_exec.c pinfo_exec.c shell.c ioredir.c pipe.c -o shell -g -fcommon