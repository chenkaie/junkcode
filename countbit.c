/*
 * $ gcc countbit.c -o countbit.out
 * $ ./countbit.out
 * ===============================================================
 * <PROFILING> Start : [ProfilingStart] (1414405319.256769)
 * <PROFILING> End   : [ProfilingEnd] (1414405339.508215) g_uiDiff = 20251,446
 * ===============================================================
 * ===============================================================
 * <PROFILING> Start : [ProfilingStart] (1414405339.508239)
 * <PROFILING> End   : [ProfilingEnd] (1414405355.221734) g_uiDiff = 15713,495
 * ===============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval g_tvStart, g_tvEnd;
unsigned int g_uiDiff;

void ProfilingStart()
{
    g_uiDiff = 0;
    gettimeofday(&g_tvStart, NULL);
    fprintf(stderr, "===============================================================\n");
    fprintf(stderr, "<PROFILING> Start : [%s] (%lu.%06lu) \n"
	       , __FUNCTION__
	       , g_tvStart.tv_sec
	       , g_tvStart.tv_usec);
}

void ProfilingEnd()
{
    gettimeofday(&g_tvEnd, NULL);
    g_uiDiff = ( (g_tvEnd.tv_sec - g_tvStart.tv_sec) * 1000000 )  + (g_tvEnd.tv_usec - g_tvStart.tv_usec);
    fprintf(stderr, "<PROFILING> End   : [%s] (%lu.%06lu) g_uiDiff = %d,%03d\n"
	       , __func__ 
		   , g_tvEnd.tv_sec
		   , g_tvEnd.tv_usec
		   , g_uiDiff/1000
		   , g_uiDiff%1000);
    fprintf(stderr, "===============================================================\n");
}

int count_bit_1 (unsigned int n)
{
	int bits = 0;
	while (n != 0)
	{
		if (n & 1) bits++;
		n >>= 1;
	}
	return bits;
}

int count_bit_2 (unsigned int n)
{
	int bits = 0;
	while (n != 0)
	{
		if (n & 1 << 0) bits++;
		if (n & 1 << 1) bits++;
		if (n & 1 << 2) bits++;
		if (n & 1 << 3) bits++;
		n >>= 4;
	}
	return bits;
}

int main(int argc, const char *argv[])
{
	unsigned int i, x;

	ProfilingStart();
	for (i = 0; i < 100000000; i++) 
	{
		x = random();
		count_bit_1(x);
	}
	ProfilingEnd();

	ProfilingStart();
	for (i = 0; i < 100000000; i++) 
	{
		x = random();
		count_bit_2(x);
	}
	ProfilingEnd();

	return 0;
}
