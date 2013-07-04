#include <assert.h>

int main(int argc, const char *argv[])
{
	unsigned char c = -1;
	assert(c == -1); // This assertion fails. Yikes.

	return 0;
}
