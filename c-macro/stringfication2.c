#include <stdio.h>

#define WARN_IF(EXP) \
     do { if (EXP) \
             fprintf (stderr, "Warning: " #EXP "\n"); } \
     while (0)

typedef struct TCCSyms {
	char *str;
	void *ptr;
} TCCSyms;

#define TCCSYM(a) { #a, &a, },
/* add the symbol you want here if no dynamic linking is done */
static TCCSyms tcc_syms[] = {
	TCCSYM(printf)
	TCCSYM(fprintf)
	TCCSYM(fopen)
	TCCSYM(fclose)
	{ NULL, NULL },
};

int main() {
    int x = 0;
    WARN_IF(x == 0);

	int i;
	for (i=0; tcc_syms[i].str != NULL; i++)
		printf("symbol:%-10s address:%d\n", tcc_syms[i].str, tcc_syms[i].ptr);
}
