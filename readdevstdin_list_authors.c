// http://blog.linux.org.tw/~jserv/archives/2011/06/include_devstdi.html
// Compile by:
//   echo '"jserv, chenkaie"' | gcc list_authors.c

#include <stdio.h>

int main() {
	puts(
#include "/dev/stdin"
		);
	return 0;
}
