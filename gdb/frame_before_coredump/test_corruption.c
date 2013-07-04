#include <stdio.h>
#include <pthread.h>

void
depth3() {
	int *ptr;
	int i;

	ptr = (int *)&ptr;
	ptr++;
	for(i = 0; i < 1024; i++) {
		*ptr++ = 0xff;
	}
}

void
depth2() {
	depth3();
}

void *
depth1() {
	depth2();
}

void *
depth0(void *dummy) {
	depth1();
}

int
main(int argc, const char *argv[]) {
	pthread_t pth;
	void *value;

	puts("Hello World, before pthread_create\n");
	pthread_create(&pth, NULL, depth0, NULL);
	pthread_join(pth, &value);
	puts("Hello World, after pthread_join\n");
	return 0;
}

/*
arm-linux-gcc
__cyg_profile_func_enter: func = 0x879c, called by = 0x40059bec
Thread ID = 0x4001df60, bdfi @ 0x11008
Hello World, before pthread_create

__cyg_profile_func_enter: func = 0x8760, called by = 0x4002a8f8
Thread ID = 0x40969490, bdfi @ 0x112b0
__cyg_profile_func_enter: func = 0x8728, called by = 0x8784
Stack is corrupted:
        0x4002a8f8
__cyg_profile_func_enter: func = 0x86a0, called by = 0x8748
Stack is corrupted:
        0x4002a8f8
__cyg_profile_func_exit: func = 0x86a0, called by = 0x8748
*/
