#include "entry.h"
#include "misc.h"

int start_thread(void *(*func)(void *), void *param)
{
	pthread_t thread_id;
	pthread_attr_t attr;
	int retval;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if ((retval = pthread_create(&thread_id, &attr, func, param)) != 0)
		DBG("%s: %s", __func__, strerror(retval));

	return (retval);
}
