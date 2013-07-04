#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define VERSION "0.2"

#define DATA_START        1
#define DATA_STOP         2500
#define DATA_LENGHT       2500
#define BYTES_TO_RECEIVE  2500


typedef enum {
	TMT_FRTSCTS,
	TMT_FXONXOFF,
	TMT_FNONE
} Flow;

typedef enum {
	TMT_B3,
	TMT_B6,
	TMT_B12,
	TMT_B24,
	TMT_B48,
	TMT_B96,
	TMT_B192
} Bps;

typedef struct {
        char device[11];
        Bps   bps;
        Flow  flow;
} CommParam;

#endif /* _SERIAL_H_ */