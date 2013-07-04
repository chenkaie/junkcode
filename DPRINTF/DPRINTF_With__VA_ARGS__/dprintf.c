#include <stdio.h>
#include <stdarg.h>

void dprintf_impl(const char* file, size_t line, int enable, const char* fmt, ...)
{
    va_list ap;
    if (enable) {
        fprintf(stderr, "%s (%d): ", file, line);
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
}

#ifndef NDEBUG
#   if (__STDC_VERSION__ < 199901L)
#       error "Please use a newer compiler that support __VA_ARGS__."
#   else
#       define DPRINTF(enable, ...) \
               dprintf_impl(__FILE__, __LINE__, enable, __VA_ARGS__)
#   endif
#else
#   define DPRINTF(enable, ...) // define to nothing in release mode
#endif

int main()
{
    int enable = 1;
    int i = 3;
    DPRINTF(enable, "i == %d, %d, %d", i, 33, 44);
    return 0;
}

// OUTPUT:
// dprintf.c (32): i == 3
