#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct bd_frame_info {
	int max;
	int top;
	void *stack[1];
};

#define DUMP(func, call) \
	printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)

#define BDFI_MAX_DEPTH 128
#define BDFI_SIZE (sizeof(void *) * (BDFI_MAX_DEPTH - 1) + \
		sizeof(struct bd_frame_info))
#define SHOW_CORRUPTED_INFO 1
#define SHOW_THREAD_INFO 1

__thread struct bd_frame_info *__before_die_frame_info = NULL;

static void
__before_die_corrupted() {
#ifdef SHOW_CORRUPTED_INFO
	int i;
	struct bd_frame_info *bdfi;

	fprintf(stderr, "Stack is corrupted:\n");
	bdfi = __before_die_frame_info;
	fprintf(stderr, "top: %d\n", bdfi->top);
	for(i = bdfi->top - 1; i >= 0; i--) {
		fprintf(stderr, "\t%p\n", bdfi->stack[i]);
	}
#endif /* SHOW_CORRUPTED_INFO */
}

static void
__before_die_new_thread(struct bd_frame_info *bdfi) {
#ifdef SHOW_THREAD_INFO
	fprintf(stderr, "Thread ID = 0x%x, bdfi @ %p\n", (int)pthread_self(), bdfi);
#endif /* SHOW_THREAD_INFO */
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void *this_fn, void *call_site) {
	DUMP(this_fn, call_site);
	struct bd_frame_info *bdfi;
	void *pparent;

	bdfi = __before_die_frame_info;
	if(bdfi == NULL) {
		/* First frame of this thread */
		bdfi = (struct bd_frame_info *)malloc(BDFI_SIZE);
		bdfi->max = BDFI_MAX_DEPTH;
		bdfi->top = 0;
		__before_die_frame_info = bdfi;
		__before_die_new_thread(bdfi);
	}

	if(bdfi->top >= bdfi->max)
		return;

	pparent = __builtin_return_address(2);
	if(bdfi->top > 0 && pparent != bdfi->stack[bdfi->top - 1]) {
		/* Corrupted stack? */
		__before_die_corrupted();
		return;
	}

	bdfi->stack[bdfi->top++] = call_site;
}

void __attribute__((__no_instrument_function__)) 
__cyg_profile_func_exit(void *this_fn, void *call_site) {
	DUMP(this_fn, call_site);
	struct bd_frame_info *bdfi;
	void *parent;

	bdfi = __before_die_frame_info;
	if(bdfi == NULL)
		return;

	parent = __builtin_return_address(1);
	if(parent != bdfi->stack[bdfi->top - 1]) {
		/* Corrupted stack? */
		__before_die_corrupted();
		return;
	}

	if(bdfi->top == 1) {
		/* Last frame of this thread */
		free(bdfi);
		__before_die_frame_info = NULL;
		return;
	}

	bdfi->top--;
}

