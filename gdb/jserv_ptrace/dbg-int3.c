#include <stdio.h>
#include <signal.h>

static volatile sig_atomic_t being_debugged = 1;
static void int3_handler(int signo) { being_debugged = 0; }

int main()
{
        signal(SIGTRAP, int3_handler);
        __asm__ __volatile__("int3");
        if (being_debugged) {
		puts("No, I don't want to serve you.");
                while (1) {
			/* endless loop */ ;
		}
        }
        puts("Yes, real routines go here.");
        return 0;
}
