/* os2.c */

/* Highly system-dependent routines go here */

#include "options.h"
#include "zoo.h"
#include "zooio.h"		/* to satisfy declarations in zoofns.h */
#include "zoofns.h"
#include "errors.i"
#include <stdio.h>		/* to get fileno() */
#include <stdlib.h>

#define INCL_NOPM
#define INCL_DOS
#define INCL_DOSERRORS
#include <os2.h>

#include "assert.h"     /* macro definition:  assert() macro            */

/* settime() */

/* Accepts a date/time in DOS format and sets the file time. Returns 1
if OK, 0 if error */

int settime (file,date,time)
ZOOFILE file;
unsigned date, time;
{
	FILESTATUS info;
	HFILE handle = fileno(file);

	fflush(file);
	DosQFileInfo(handle, 1, &info, sizeof(info));
	*((unsigned *)&info.fdateLastWrite) = date;
	*((unsigned *)&info.ftimeLastWrite) = time;
	return DosSetFileInfo(handle, 1, (PBYTE) &info, sizeof(info)) == 0;
} /* settime */

/* gets date and time of file */

gettime (file,date,time)
ZOOFILE file;
unsigned *date, *time;
{
	FILESTATUS info;
	HFILE handle = fileno(file);
	int ret;

	ret = DosQFileInfo(handle, 1, &info, sizeof(info));
	*date = *((unsigned *) &info.fdateLastWrite);
	*time = *((unsigned *) &info.ftimeLastWrite);
	return ret == 0;
} /* settime */


/* space() */

/* Returns free space in bytes on disk n (0 = default, 1 = A, etc.).  Returns
	0 if drive number is invalid.  Before getting disk space, the function
	requests DOS to flush its internal buffers */

unsigned long space (drive, alloc_size)
int drive;
int *alloc_size;
{
	unsigned long free_space;
	FSALLOCATE info;
	int ret;

	DosBufReset(-1);
	ret = DosQFSInfo(drive, 1, (BYTE FAR *)&info, sizeof(info));
	*alloc_size = info.cbSector * (int) info.cSectorUnit;
	return ret ? 0L : (unsigned long) (info.cUnitAvail * *alloc_size);
}

int IsFileNameValid(char *name)
{
  HFILE hf;
  USHORT usAction;

  switch( DosOpen(name, &hf, &usAction, 0L, 0, FILE_OPEN,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, 0L) )
  {
  case ERROR_INVALID_NAME:
  case ERROR_FILENAME_EXCED_RANGE:
    return FALSE;
  case NO_ERROR:
    DosClose(hf);
  default:
    return TRUE;
  }
}


int IsFileSystemDumb(char *dir)
{                         
  char drive[5], path[256], name[256];
  
  _splitpath(dir, drive, path, NULL, NULL);
  _makepath(name, drive, path, ".DUMB.TEST.NAME", NULL);
  
  return !IsFileNameValid(name);
}


#define  FMAX  3        /* Number of different filename patterns */

void fcbpath (FILEFINDBUF *, char *, char *);

char *nextfile (what, filespec, fileset)
int what;                        /* whether to initialize or match      */
register char *filespec;         /* filespec to match if initializing   */
register int fileset;            /* which set of files                  */
{
   static FILEFINDBUF file_info [FMAX+1];     /* our own private dta        */
   static HDIR handles [FMAX+1];
   static int first_time [FMAX+1];
   static char pathholder [FMAX+1][PATHSIZE]; /* holds a pathname to return */
   static char saved_fspec [FMAX+1][PATHSIZE];/* our own copy of filespec   */
   static int lower;
   USHORT count;
   int ret;

   assert(fileset >= 0 && fileset <= FMAX);
   if (what == 0) {
      assert(filespec != NULL);
      strcpy (saved_fspec[fileset], filespec);  /* save the filespec */
      first_time[fileset] = 1;
      return (NULL);
   }

   assert(what == 1);
   assert(filespec == NULL);
   assert(first_time[fileset] == 0 || first_time[fileset] == 1);

   if (first_time[fileset]) {             /* first time -- initialize etc. */
      /* find first matching file */
      count = 1;
      lower = IsFileSystemDumb(saved_fspec[fileset]);
      handles[fileset] = 0xffff;	  /* Get new handle */
      ret = DosFindFirst(saved_fspec[fileset], &handles[fileset], 0,
      		   &file_info[fileset], sizeof(FILEFINDBUF), &count, 0L);
   } else {
      /* find next matching file */
      count = 1;
      ret = DosFindNext(handles[fileset], &file_info[fileset], sizeof(FILEFINDBUF),
      		  &count);
   }

   if (ret != 0 || count != 1) {            /* if error status                  */
      if (first_time[fileset]) {       /*   if file never matched then     */
         first_time[fileset] = 0;
         return (saved_fspec[fileset]);/*      return original filespec    */
      } else {                         /*   else                           */
         first_time[fileset] = 0;      /*                                  */
         return (NULL);                /*      return (NULL) for no more   */
      }
   } else {                                        /* a file matched */
      first_time[fileset] = 0;
      /* add path info  */
      if ( lower )
        strlwr(file_info[fileset].achName);
      fcbpath (&file_info[fileset], saved_fspec[fileset], pathholder[fileset]);
      return (pathholder[fileset]);                /* matching path  */
   }
} /* nextfile */

/*
fcbpath() accepts a pointer to the FILEFINDBUF, a
character pointer to a pathname that may contain wildcards, and a character
pointer to a buffer.  Copies into buffer the path prefix from the pathname
and the filename prefix from the DTA so that it forms a complete path
*/

void fcbpath (info, old_path, new_path)
FILEFINDBUF *info;
char *old_path;
register char *new_path;
{
   register int i;
   int length, start_pos;

   strcpy(new_path, old_path);               /* copy the whole thing first */
   length = strlen(new_path);
   i = length - 1;                           /* i points to end of path */
   while (i >= 0 && new_path[i] != '/' && new_path[i] != '\\' && new_path[i] != ':')
      i--;
   /* either we found a "/", "\", or ":", or we reached the beginning of
      the name.  In any case, i points to the last character of the
      path part. */
   start_pos = i + 1;
   for (i = 0; info->achName[i]; i++)
      new_path[start_pos+i] = info->achName[i];
   new_path[start_pos+i] = '\0';
}


int outchar(int c)
{
  putchar(c);
}
