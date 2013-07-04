#include "test.h"

int main(void){
#ifdef HAVE_MMAP
	printf("HAVE_MMAP\n");
#else
	printf("DON't HAVE_MMAP\n");
#endif
}
