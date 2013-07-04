#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/stat.h> 

int main(int argc, char* argv[]) 
{ 
	int i; 
	int idx; 
	int width; 
	int height; 
	int pixels; 
	int frame_no; 
	FILE *inputfp = NULL; 
	FILE *outputfp = NULL; 
	unsigned char *pBuffer; 
	struct stat state; 

	if (argc != 5) 
	{ 
		fprintf(stderr, "Usage : %s <input file name> \
				<output file name> <width> <height>\n",argv[0]); 
			return -1; 
	} 

	width = atoi(argv[3]); 
	height = atoi(argv[4]); 

	if(width <= 0 || height <= 0) 
	{ 
		fprintf(stderr, "parameter error [width = %d, height=%d]\n",width, height); 
		return -1; 
	} 

	if (stat(argv[1], &state) < 0) 
	{ 
		fprintf(stderr, "Faile to stat %s\n",argv[1]); 
		return -1; 
	} 
	frame_no = (state.st_size/((width*height/2)*3)); 

	inputfp = fopen(argv[1], "rb"); 
	if (!inputfp) 
	{ 
		fprintf(stderr, "fopen failed for input file[%s]\n",argv[1]); 
		return -1; 
	} 

	outputfp = fopen(argv[2], "wb"); 
	if (!outputfp) 
	{ 
		fprintf(stderr, "fopen failed for output file[%s]\n",argv[2]); 
		return -1; 
	} 

	pixels = width * height; 
	pBuffer = (unsigned char *)malloc(pixels); 

	for (i=0; i<frame_no; i++) 
	{ 
		// Read Y 
		fread (pBuffer, pixels, sizeof(unsigned char), inputfp); 

		// Write Y 
		fwrite(pBuffer, pixels, sizeof(unsigned char), outputfp); 

		// Read Cb Cr 
		fread (pBuffer, (pixels/2), sizeof(unsigned char), inputfp); 

		// Write Cb 
		for(idx = 0; idx <  (pixels/2); idx+=2) 
		{ 
			fwrite((pBuffer + idx), 1, sizeof(unsigned char), outputfp); 
		} 

		// Write Cr 
		for(idx = 1; idx <  (pixels/2); idx+=2) 
		{ 
			fwrite((pBuffer + idx), 1, sizeof(unsigned char), outputfp); 
		} 
	} 

	free(pBuffer); 
	fclose(inputfp); 
	fclose(outputfp); 
	return 0; 
} 
