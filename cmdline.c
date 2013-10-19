#include "cmdline.h"

static int  exist(char * argument);
static char *  getvalue(char * argument);
static void  init(int argc, char * argv[]);
static void  cleanup(void);

struct __cmdline{
	int		( * exist)			(char * argument);
	char *	( * getvalue)	(char * argument);
	void		( * init)			(int argc, char * argv[]);
	void		( * cleanup)	(void);
	int		argc;
	char ** argv;
} cmdline = {
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

static int  exist(char * argument)
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

static char *  getvalue(char * argument)
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

int main(int argc, char * argv[])
{
	cmdline.init(argc, argv);
	if(cmdline.exist("-d")){
		printf("exist -d argument!\n");
	} else {
		printf("not exist -d argument!\n");
	}
	char * test = (char *)NULL;
	test = cmdline.getvalue("-f");
	if(test){
		printf("%s\n", test);
	}
	cmdline.cleanup();
	return 0;
}
