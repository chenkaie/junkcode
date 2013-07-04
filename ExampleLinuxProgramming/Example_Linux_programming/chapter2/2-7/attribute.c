void die_on_error(void) __attribute__ ((noreturn));

int var __attribute__ ((aligned (16)))=0;

void die_on_error(void){
	exit(-1);
}
