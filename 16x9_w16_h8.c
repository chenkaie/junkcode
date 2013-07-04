#include <stdio.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	int x = 0, y = 0;

	for (x = 176; x <= 1920; x = x + 16)
	{
		for (y = 144; y <= 1080; y = y + 8)
		{
			if (x * 9 == y * 16)
			{
				printf("%d x %d\n", x, y);
			}
		}
	}
	return 0;
}
