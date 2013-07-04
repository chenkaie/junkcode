#ifndef DPRINTF_H_INCLUDED
#define DPRINTF_H_INCLUDED

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

void dprintf_c99(const char* src_file, size_t src_line,
                 int enable, const char* fmt, ...);

typedef void (*dprintf_fn)(int enable, const char* fmt, ...);

void dprintf_tls(int enable, const char* fmt, ...);
dprintf_fn dprintf_front(const char* src_file, size_t src_line);

#if defined(__cplusplus)
} // extern "C"
#endif

#if defined(__cplusplus)
class dprintf_cpp
{
public:
    dprintf_cpp(const char* src_file, size_t src_line);
    void operator()(bool enable, const char* fmt, ...) const;
private:
    const char* src_file_;
    size_t      src_line_;
};
#endif

#ifndef NDEBUG
#   if (__STDC_VERSION__ >= 199901L) // support C99
#       define DPRINTF(enable, ...) \
               dprintf_c99(__FILE__, __LINE__, enable, __VA_ARGS__)
#   else
#       if defined(__cplusplus) // is C++
#           define DPRINTF \
                   dprintf_cpp(__FILE__, __LINE__)
#       else
#           define DPRINTF \
                   (*dprintf_front(__FILE__, __LINE__))
        #endif
#   endif
#else
#   define DPRINTF(enable, ...) // define to nothing in release mode
#endif

#endif // DPRINTF_H_INCLUDED
