#include "cmdline.h"
#ifndef WIN32
#define	__cdecl __attribute__((__cdecl))
#endif

static int 		__cdecl exist(char * argument);
static char * 	__cdecl getvalue(char * argument);
static void 	__cdecl init(int argc, char * argv[]);
static void 	__cdecl cleanup(void);

struct __cmdline cmdline = {
	exist,
	getvalue,
	init,
	cleanup,
	0,
	(char **)NULL,
};

void cleanup(void)
{
	cmdline.argc = 0;
	cmdline.argv = (char **) NULL;
}

static int __cdecl exist(char * argument)
{
	int i = 0;
	int length = strlen(argument);
	for(i = 1; i < cmdline.argc; i++){
		if(0 == memcmp(argument, cmdline.argv[i], length)){
			return 1;
		}
	}
	return 0;
}

static char * __cdecl getvalue(char * argument)
{
	int i = 0;
	int length =strlen(argument);
	for(i = 1; i < cmdline.argc; i++){
		if(0 == memcmp(argument, cmdline.argv[i], length)){
			if(cmdline.argv[i][length] == '='){
				return &cmdline.argv[i][length+1];
			} else if(cmdline.argv[i][length] == '\0'){
				if(cmdline.argv[i+1][0] != '-'){
					return cmdline.argv[i+1];
				} else {
					return (char *) NULL;
				}
			}
		}
	}
	return (char *)NULL;
}



void init(int argc, char * argv[])
{
	cmdline.argc = argc;
	cmdline.argv = argv;
}

