#include <string.h>

void convert_yuv420_to_nv21(unsigned char * dest, const unsigned char * source, int width, int height)
{
	int area = height * width;
	int sqarea = area >> 3;
	int qarea = area >> 2;

	int count = sqarea;
	const unsigned short * su = (const unsigned short *) (source + area);
	const unsigned short * sv = (const unsigned short *) (source + area + qarea);
	unsigned int * uv = (unsigned int *)(dest + area);
	
	/* copy y as is */
	memcpy(dest, source, area);

	do
	{
		unsigned int u = *su++;
		unsigned int v = *sv++;
		
		*uv++ = ( ( (u & 0x00FF) << 8 ) |
			( (u & 0xFF00) << 16) |
			( (v & 0x00FF) )      |
			( (v & 0xFF00) << 8) );
	} while (--count);
	
}

int main(int argc, const char *argv[])
{
	return 0;
}
