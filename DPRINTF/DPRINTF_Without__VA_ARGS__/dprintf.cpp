#include "dprintf.h"
#include "thread_tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

static
void dprintf_impl(const char* src_file, size_t src_line,
                  int enable, const char* fmt, va_list ap)
{
    ENTER_FUNCTION();
    if (enable) {
        fprintf(stderr, "%s (%d): ", src_file, src_line);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
}

void dprintf_c99(const char* src_file, size_t src_line,
                 int enable, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    dprintf_impl(src_file, src_line, enable, fmt, ap);
    va_end(ap);
}

dprintf_cpp::dprintf_cpp(const char* src_file, size_t src_line)
    : src_file_(src_file)
    , src_line_(src_line)
{
}

void dprintf_cpp::operator()(bool enable, const char* fmt, ...) const
{
    ENTER_FUNCTION();
    va_list ap;
    va_start(ap, fmt);
    dprintf_impl(src_file_, src_line_, enable, fmt, ap);
    va_end(ap);
}

struct file_line_t
{
    const char* file;
    size_t      line;
};

void free_file_line(void* value)
{
    ENTER_FUNCTION();
    file_line_t* fl = reinterpret_cast<file_line_t*>(value);
    if (fl) {
        free(fl);
    }
}

typedef void (*cleanup_fn)(void* value);

template <class T>
class TlsCell
{
public:

    TlsCell(cleanup_fn cleanup = 0)
    {
        pthread_key_create(&key_, cleanup);
    }

    ~TlsCell()
    {
        pthread_key_delete(key_);
    }

    void set(T* value)
    {
        pthread_setspecific(key_, reinterpret_cast<void*>(value));
    }

    T* get()
    {
        return reinterpret_cast<T*>(pthread_getspecific(key_));
    }

private:

    pthread_key_t key_;

};

TlsCell<file_line_t> g_file_line_tls(free_file_line);

void dprintf_tls(int enable, const char* fmt, ...)
{
    ENTER_FUNCTION();
    va_list ap;
    file_line_t* fl = g_file_line_tls.get();
    va_start(ap, fmt);
    dprintf_impl(fl->file, fl->line, enable, fmt, ap);
    va_end(ap);
}

dprintf_fn dprintf_front(const char* src_file, size_t src_line)
{
    ENTER_FUNCTION();
    file_line_t* fl = g_file_line_tls.get();
    if (fl == NULL) {
        fl = reinterpret_cast<file_line_t*>(malloc(sizeof(file_line_t)));
        g_file_line_tls.set(fl);
    }
    fl->file = src_file;
    fl->line = src_line;
    thread_sleep(2);
    return &dprintf_tls;
}
