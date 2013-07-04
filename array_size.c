#include <stdio.h>

#define NUM_DAYS 5
typedef int days_t[ NUM_DAYS ];
#define SIZEOF_DAYS ( sizeof( days_t ) )

int main() {
    days_t  days;
    days_t *ptr = &days; 

    printf( "SIZEOF_DAYS:  %u\n", SIZEOF_DAYS  );
    printf( "sizeof(days): %u\n", sizeof(days) );
    printf( "sizeof(*ptr): %u\n", sizeof(*ptr) );
    printf( "sizeof(ptr):  %u\n", sizeof(ptr)  );
    printf( "sizeof(int):  %u\n", sizeof(int)  );

    return 0;
} 
