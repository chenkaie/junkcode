/* Circular buffer example, keeps one slot open */
 
#include <stdio.h>
#include <malloc.h>
 
/* Opaque buffer element type.  This would be defined by the application. */
typedef struct { int value; } ElemType;

#define _USE_A_FILL_COUNT
//#define _ALWAYS_KEEP_ONES_LOT_OPEN

#if defined(_USE_A_FILL_COUNT)
/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         count;  /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;

/* This approach replaces the CircularBuffer 'end' field with the
   'count' field and changes these functions: */
 
void cbInit(CircularBuffer *cb, int size) {
    cb->size  = size;
    cb->start = 0;
    cb->count = 0;
    cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}
 
int cbIsFull(CircularBuffer *cb) {
    return cb->count == cb->size; }
 
int cbIsEmpty(CircularBuffer *cb) {
    return cb->count == 0; }
 
void cbWrite(CircularBuffer *cb, ElemType *elem) {
    int end = (cb->start + cb->count) % cb->size;
    cb->elems[end] = *elem;
    if (cb->count == cb->size)
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
    else
        ++ cb->count;
}
 
void cbRead(CircularBuffer *cb, ElemType *elem) {
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    -- cb->count;
}

#elif defined(_ALWAYS_KEEP_ONES_LOT_OPEN)

/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         end;    /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;

void cbInit(CircularBuffer *cb, int size) {
    cb->size  = size + 1; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}
 
int cbIsFull(CircularBuffer *cb) {
    return (cb->end + 1) % cb->size == cb->start; }
 
int cbIsEmpty(CircularBuffer *cb) {
    return cb->end == cb->start; }
 
/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cbWrite(CircularBuffer *cb, ElemType *elem) {
    cb->elems[cb->end] = *elem;
    cb->end = (cb->end + 1) % cb->size;
    if (cb->end == cb->start)
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
}
 
/* Read oldest element. App must ensure !cbIsEmpty() first. */
void cbRead(CircularBuffer *cb, ElemType *elem) {
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
}
#endif

void cbFree(CircularBuffer *cb) {
    free(cb->elems); /* OK if null */ }
 
int main(int argc, char **argv) {
    CircularBuffer cb;
    ElemType elem = {0};
 
    int testBufferSize = 10; /* arbitrary size */
    cbInit(&cb, testBufferSize);
 
    /* Fill buffer with test elements 3 times */
    for (elem.value = 0; elem.value < 1 * testBufferSize; ++ elem.value)
        cbWrite(&cb, &elem);
 
    /* Remove and print all elements */
    while (!cbIsEmpty(&cb)) {
        cbRead(&cb, &elem);
        printf("%d\n", elem.value);
    }
 
    cbFree(&cb);
    return 0;
}
