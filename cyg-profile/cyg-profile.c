/* 
 * cyg-profile.c - CygProfiler runtime functions.
 *
 * Michal Ludvig <michal@logix.cz>
 * http://www.logix.cz/michal/devel
 *
 * cyg-profile.c
 * - Compile your program with -finstrument-functions and link 
 *   together with this code.
 * - Logging is enabled as soon as your program calls
 *   cygprofile_enable() and disabled with cygprofile_disable().
 * - Before logging was enabled you can change the name 
 *   of a logfile by calling cygprofile_setfilename().
 */

/* Hint: -finstrument-functions, no_instrument_function */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "cyg-profile.h"

#define FN_SIZE 100
#define FN_DEFAULT "cyglog.%d"

/* Private variables.  */
static int level=0;
static FILE *logfile=NULL;
static int cyg_profile_enabled=0;
static char cyg_profile_filename[FN_SIZE+1];

#ifdef __cplusplus
extern "C" {
#endif

/* Static functions. */
static FILE *openlogfile (const char *filename)
	__attribute__ ((no_instrument_function));
static void closelogfile (void)
	__attribute__ ((no_instrument_function));

/* Note that these are linked internally by the compiler. 
 * Don't call them directly! */
void __cyg_profile_func_enter (void *this_fn, void *call_site)
	__attribute__ ((no_instrument_function));
void __cyg_profile_func_exit (void *this_fn, void *call_site)
	__attribute__ ((no_instrument_function));

#ifdef __cplusplus
};
#endif

void
__cyg_profile_func_enter (void *this_fn, void *call_site)
{
	if(cyg_profile_enabled)
		if (logfile || openlogfile(cyg_profile_filename))
			fprintf(logfile, "+ %d %p %p\n", level++, 
				this_fn, call_site);
}

void
__cyg_profile_func_exit (void *this_fn, void *call_site)
{
	if(cyg_profile_enabled)
		if (logfile || openlogfile(cyg_profile_filename))
			fprintf(logfile, "- %d %p %p\n", level--, 
				this_fn, call_site);
}

void
cygprofile_enable (void)
{
	if (!cyg_profile_filename[0])
		cygprofile_setfilename (FN_DEFAULT);
	if (!openlogfile (cyg_profile_filename))
		return;
	cyg_profile_enabled = 1;
}

void
cygprofile_disable (void)
{
	cyg_profile_enabled = 0;
}

int
cygprofile_isenabled (void)
{ return cyg_profile_enabled; }

int 
cygprofile_setfilename (const char *filename)
{
	char *ptr;

	if (cygprofile_isenabled ())
		return -1;

	if (strlen (filename) > FN_SIZE)
		return -2;

	ptr = strstr (filename, "%d");
	if (ptr)
	{
		size_t len;
		len = ptr - filename;
		snprintf (cyg_profile_filename, len+1, "%s", filename);
		snprintf (&cyg_profile_filename[len], FN_SIZE - len, 
			"%d", getpid ());
		len = strlen (cyg_profile_filename);
		snprintf (&cyg_profile_filename[len], FN_SIZE - len,
			"%s", ptr + 2);
	}
	else
		snprintf (cyg_profile_filename, FN_SIZE, "%s", filename);

	if (logfile)
		closelogfile ();

	return 0;
}

char *
cygprofile_getfilename (void)
{
	if (!cyg_profile_filename[0])
		cygprofile_setfilename (FN_DEFAULT);
	return cyg_profile_filename;
}

static FILE *
openlogfile (const char *filename)
{
	static int complained = 0;
	FILE *file;
	
	if (complained)
		return NULL;
	
	if (logfile)
		return logfile;

	file = fopen(filename, "w");
	if (!file)
	{
		fprintf (stderr, "WARNING: Can't open logfile '%s': %s\n", 
			filename, strerror (errno));
		complained = 1;
		return NULL;
	}
	
	setlinebuf (file);
	logfile = file;

	return file;
}

static void
closelogfile (void)
{
	if (logfile)
		fclose (logfile);
}
