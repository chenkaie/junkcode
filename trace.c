/* Copyright: Pádraig Brady 2005
 * Summary: debug trace support
 * License: LGPL
 * History:
 *     10 Oct 2001 : Initial version
 *     15 Nov 2005 : Add trace()
 */

#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include "trace.h"

int trace_level = LOG_DEBUG; //log everything by default
int trace_interactive = 1; //log to stderr by default (else syslog)

static void back_trace(int sig)
{
    void *array[10]; //only care about last 7 functions (3 taken with tracing support)
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size); //Need -rdynamic gcc (linker) flag for this to work

    for (i = 2; i < size; i++) //skip trace functions themselves
        trace(LOG_CRIT, "going(%02zu) [%s]", i-2, strings[i]);

    trace(LOG_CRIT, "gone");

    free(strings);
    abort(); //hopefully will give core
}

void install_back_trace(void)
{
    signal(SIGILL, back_trace);
    signal(SIGBUS, back_trace);
    signal(SIGSEGV, back_trace);
}

/* priority is same as syslog and is as follows:
    0 LOG_EMERG   system is unusable
    1 LOG_ALERT   action must be taken immediately
    2 LOG_CRIT    critical conditions
    3 LOG_ERR     error conditions
    4 LOG_WARNING warning conditions
    5 LOG_NOTICE  normal, but significant, condition
    6 LOG_INFO    informational message
    7 LOG_DEBUG   debug messages

    A trailing \n in fmt is optional and the appropriate
    thing is done whether it's present or not.
    Ideally one should NOT include a trailing newline
    as that better decouples trace from the terminal.

    Note %m in fmt is equivalent to strerror(errno) as of libc5.
*/
void trace(int priority, const char *fmt, ...)
{
    if (priority > trace_level)
        return;

    va_list ap;
    va_start(ap, fmt);

    if (trace_interactive) {
        vfprintf(stderr, fmt, ap);
        if (fmt[strlen(fmt)-1] != '\n') {
            fputc('\n', stderr);
        }
    } else {
        vsyslog(LOG_DAEMON | priority, fmt, ap);
        //syslog converts \n to (trailing) spaces
    }

    va_end(ap);
}
