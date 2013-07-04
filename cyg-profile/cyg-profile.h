/* 
 * cyg-profile.h - Header file for CygProfiler
 * 
 * Michal Ludvig <michal@logix.cz>
 * http://www.logix.cz/michal/devel
 *
 * This source code is a public domain.
 *
 * See cyg-profile.c for details on usage.
 */

#ifndef CYG_PROFILE_H
#define CYG_PROFILE_H

/* Public functions.  */

#ifdef __cplusplus
extern "C" {
#endif

/* Enable/disable CygProfiler.  */
void cygprofile_enable (void)
	__attribute__ ((no_instrument_function));
void cygprofile_disable (void)
	__attribute__ ((no_instrument_function));

/* Tell whether CygProfiler is enabled/disabled.  */
int cygprofile_isenabled (void)
	__attribute__ ((no_instrument_function));

/* Set filename of a logfile.  */
int cygprofile_setfilename (const char *filename)
	__attribute__ ((no_instrument_function));

/* Query for a filename of a logfile.  */
char *cygprofile_getfilename (void)
	__attribute__ ((no_instrument_function));

#ifdef __cplusplus
};
#endif

#endif
