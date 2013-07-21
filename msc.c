/* @(#) msc.c 1.2 91/07/14 16:08:54 */

#include <stdio.h>		/* to get fileno() */
#include <stdlib.h>
#include <signal.h>

#ifdef OS2
#define INCL_BASE
#include <os2.h>
#else
#include <dos.h>
#endif

void dosname PARMS((char *, char *));

/****************
function zootrunc() truncates a file at the current seek position.
*/

int zootrunc (f)
FILE *f;
{
	int handle = fileno(f);
	extern long tell();
	extern int chsize();
	return chsize(handle, tell(handle));
}

/****************
Function fixfname() converts the supplied filename to a syntax
legal for the host system.  It is used during extraction.
*/

char *fixfname(fname)
char *fname;
{
	char tmpname[PATHSIZE];
#ifdef OS2
        if ( IsFileNameValid(fname) )
	  return(fname);
#endif
	dosname (nameptr(fname), tmpname);
	strcpy(fname,tmpname);
	return(fname);
}

static int set_break (int flag)
{
#ifdef OS2
	KBDINFO info;
	int ret;

	info.cb = sizeof(info);
	KbdGetStatus(&info, 0);
	ret = info.fsMask & 0x0f;
	info.fsMask = flag ? KEYBOARD_ECHO_OFF | KEYBOARD_BINARY_MODE
                           : KEYBOARD_ECHO_ON  | KEYBOARD_ASCII_MODE;
	KbdSetStatus(&info, 0); /* keyboard in new mode */
	return ret;
#else
	int retval;
	union REGS regs;

	regs.x.ax = 0x3300;				/* get ctrl-break flag */
	intdos (&regs, &regs);
	retval = regs.h.dl;				/* retval is old value of setting */
	regs.x.ax = 0x3301;				/* set ctrl-break flag */
	regs.h.dl = flag;				/* status to set to */
	intdos (&regs, &regs);
	return (retval);
#endif
}

static int break_flag;

void zooexit (int status)
{
	set_break (break_flag);			/* restore control_break setting */
	exit (status);
}

void spec_init(void)
{
	break_flag = set_break (0);
	signal (SIGINT, zooexit);		/* install our own Control-C handler */
	signal (SIGBREAK, zooexit);		/* install our own Control-Break handler */
}
