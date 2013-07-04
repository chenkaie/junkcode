#ifndef THREAD_TOOL_H_INCLUDED
#define THREAD_TOOL_H_INCLUDED

#include <stdio.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define ENTER_FUNCTION()                              \
    fprintf(stderr, "thread#%d: %s(): entering...\n", \
            pthread_self(), __FUNCTION__);            \
    /**/

/** Sleep @p s seconds for current thread. */
void thread_sleep(size_t s);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif /* THREAD_TOOL_H_INCLUDED */
