#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#define	__cdecl __attribute__((__cdecl))
#endif

struct __cmdline{
	int		(__cdecl * exist)	(char * argument);
	char *	(__cdecl * getvalue)(char * argument);
	void	(__cdecl * init)	(int argc, char * argv[]);
	void	(__cdecl * cleanup)	(void);
	int		argc;
	char ** argv;
};

extern struct __cmdline cmdline;
