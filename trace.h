/* Copyright: Pádraig Brady 2001
 * Summary: debug trace support
 * License: LGPL
 * History:
 *     10 Oct 2001 : Initial version
 *     15 Nov 2005 : Add trace()
 */

//TODO: have a look at fmtmsg

#ifndef TRACE_H
#define TRACE_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <syslog.h>

/*
  This is an extremely useful facility provided by glibc,
  where the call stack of a program can be printed (on
  program crash in this case). This help narrows down what
  caused the problem (to the function (not the line) (so
  keep your functions nice and small and cohesive!)).

  This takes no runtime overhead and minimal space, and
  so should be considered for inclusion in release versions
  as well as debug, especially for long lived processes
  like servers et al.

  Note to get symbols printed also, you need to use
  the -rdynamic gcc (linker) flag. Alternatively you
  can just print the (function) line info and use addr2line
  with a seperately maintained symbol table (in a debugging
  version of the binary).

  Note this can also be used to debug infinite loops
  by explicitly sending a signal like:
  kill -s SIGSEGV -p your_pid

  Note the output from the following will be something like (for C++):

  Oct  9 18:24:48 pixelbeat monaco: going(01) [/lib/i686/libc.so.6(killpg+0x54) [0x400cc648]]
  Oct  9 18:24:48 pixelbeat monaco: going(02) [./monaco(main__14monitorManager+0x1df) [0x804dcab]]
  Oct  9 18:24:48 pixelbeat monaco: going(03) [./monaco(ThreadStarter__6ThreadPv+0x1d) [0x80536a9]]
  Oct  9 18:24:48 pixelbeat monaco: gone

  To decode this info in detail you need the binutils utilities c++filt and addr2line.
  Both take input from stdin and decode the C++ names and file_name:line_num respectively.
  From the output above you would pass "main__14monitorManager" to c++filt and "0x804dcab"
  to addr2line. Note addr2line must be pointed at the appropriate binary with *full debugging
  info present". For e.g. like: addr2line -e ./monaco.symbols
*/
void install_back_trace(void);

extern int trace_level; //set to LOG_DEBUG by default (logs everything)
extern int trace_interactive; //1 = log to stderr (default) else syslog

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
void trace(int priority, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //TRACE_H
