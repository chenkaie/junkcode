/*
 CIH<Software Magician> IamCIH@gmail.com
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void __attribute__((__no_instrument_function__))
	__cyg_profile_func_enter(void *this_func, void *call_site)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	fprintf(stderr, "+ func:%x parent_func:%x time:%i.%06i\n",
			(unsigned int)this_func,
			(unsigned int)call_site,
			(unsigned int)tv.tv_sec,
			(unsigned int)tv.tv_usec);

}
void __attribute__((__no_instrument_function__))
	__cyg_profile_func_exit(void *this_func, void *call_site)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	fprintf(stderr, "- func:%x parent_func:%x time:%i.%06i\n",
			(unsigned int)this_func,
			(unsigned int)call_site,
			(unsigned int)tv.tv_sec,
			(unsigned int)tv.tv_usec);
}

void ggg()
{
	sleep(1);
}

int main()
{
	ggg();
	return 0;
}

