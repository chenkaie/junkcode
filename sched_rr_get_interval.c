/*
 * Example (TI Platform):  
 * ~ # /home/kent/ArmTools/DavinciBinary/chrt -f 10 ./sched.dm365.out
 * Timeslice: 0.0
 *
 * ~ # /home/kent/ArmTools/DavinciBinary/chrt -v -f 10 ./sched.dm365.out
 * pid 14277's new scheduling policy: SCHED_FIFO
 * pid 14277's new scheduling priority: 10
 * Timeslice: 0.0  --> 0 nanoseconds, indicating that it is "infinite"
 *
 * ~ # /home/kent/ArmTools/DavinciBinary/chrt -v -r 10 ./sched.dm365.out
 * pid 14298's new scheduling policy: SCHED_RR
 * pid 14298's new scheduling priority: 10
 * Timeslice: 0.100000000
 *
 * ~ # /home/kent/ArmTools/DavinciBinary/chrt -v -o 0 ./sched.dm365.out
 * pid 14315's new scheduling policy: SCHED_OTHER
 * pid 14315's new scheduling priority: 0
 * Timeslice: 0.100000000
 */

#include <stdio.h>
#include <sched.h>

int main()
{
	struct timespec ts;
	int ret;

	/* real apps must check return values */
	ret = sched_rr_get_interval(0, &ts);

	printf("Timeslice: %lu.%lu\n", ts.tv_sec, ts.tv_nsec);
}

