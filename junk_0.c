#include <stdio.h>

const unsigned int g_dZoomPositionTableEH3300[]={
	10 ,	0 	 ,
	11 ,	1023 ,
	12 ,	1964 ,
	13 ,	2660 ,
	14 ,	3332 ,
	15 ,	3917 ,
	16 ,	4502 ,
	17 ,	5002 ,
	18 ,	5443 ,
	19 ,	5841 ,
	20 ,	6225 ,
	21 ,	6574 ,
	22 ,	6831 ,
	23 ,	7089 ,
	24 ,	7347 ,
	25 ,	7605 ,
	26 ,	7863 ,
	27 ,	8121 ,
	28 ,	8378 ,
	29 ,	8636 ,
	30 ,	8894 ,
	31 ,	9087 ,
	32 ,	9281 ,
	33 ,	9474 ,
	34 ,	9668 ,
	35 ,	9861 ,
	36 ,	9989 ,
	37 ,	10116,
	38 ,	10244,
	39 ,	10365,
	40 ,	10486,
	41 ,	10654,
	42 ,	10756,
	43 ,	10859,
	44 ,	10961,
	45 ,	11063,
	46 ,	11165,
	47 ,	11268,
	48 ,	11370,
	49 ,	11472,
	50 ,	11589,
	51 ,	11686,
	52 ,	11784,
	53 ,	11881,
	54 ,	11963,
	55 ,	12045,
	56 ,	12127,
	57 ,	12209,
	58 ,	12291,
	59 ,	12357,
	60 ,	12422,
	61 ,	12492,
	62 ,	12561,
	63 ,	12631,
	64 ,	12700,
	65 ,	12765,
	66 ,	12829,
	67 ,	12894,
	68 ,	12959,
	69 ,	13023,
	70 ,	13088,
	71 ,	13142,
	72 ,	13196,
	73 ,	13250,
	74 ,	13304,
	75 ,	13357,
	76 ,	13411,
	77 ,	13465,
	78 ,	13519,
	79 ,	13580,
	80 ,	13641,
	81 ,	13689,
	82 ,	13737,
	83 ,	13785,
	84 ,	13832,
	85 ,	13880,
	86 ,	13928,
	87 ,	13974,
	88 ,	14019,
	89 ,	14065,
	90 ,	14110,
	91 ,	14155,
	92 ,	14201,
	93 ,	14246,
	94 ,	14292,
	95 ,	14337,
	96 ,	14373,
	97 ,	14408,
	98 ,	14444,
	99 ,	14479,
	100,	14515,
	101,	14554,
	102,	14592,
	103,	14631,
	104,	14669,
	105,	14708,
	106,	14746,
	107,	14776,
	108,	14806,
	109,	14836,
	110,	14866,
	111,	14898,
	112,	14930,
	113,	14963,
	114,	14995,
	115,	15027,
	116,	15059,
	117,	15092,
	118,	15124,
	119,	15156,
	120,	15170,
	121,	15196,
	122,	15222,
	123,	15248,
	124,	15274,
	125,	15301,
	126,	15327,
	127,	15353,
	128,	15379,
	129,	15405,
	130,	15431,
	131,	15453,
	132,	15476,
	133,	15498,
	134,	15520,
	135,	15543,
	136,	15565,
	137,	15587,
	138,	15609,
	139,	15631,
	140,	15653,
	141,	15672,
	142,	15690,
	143,	15709,
	144,	15727,
	145,	15746,
	146,	15765,
	147,	15783,
	148,	15802,
	149,	15820,
	150,	15839,
	151,	15856,
	152,	15873,
	153,	15890,
	154,	15907,
	155,	15923,
	156,	15940,
	157,	15957,
	158,	15974,
	159,	15985,
	160,	15995,
	161,	16008,
	162,	16021,
	163,	16033,
	164,	16046,
	165,	16059,
	166,	16072,
	167,	16085,
	168,	16097,
	169,	16110,
	170,	16123,
	171,	16134,
	172,	16144,
	173,	16155,
	174,	16165,
	175,	16176,
	176,	16186,
	177,	16197,
	178,	16207,
	179,	16218,
	180,	16228,
	181,	16237,
	182,	16245,
	183,	16254,
	184,	16262,
	185,	16271,
	186,	16280,
	187,	16288,
	188,	16297,
	189,	16305,
	190,	16314,
	191,	16321,
	192,	16328,
	193,	16335,
	194,	16342,
	195,	16349,
	196,	16356,
	197,	16363,
	198,	16370,
	199,	16377,
	200,	16384};

#define EPTZ_FIFOCMD_STOP             "eCamCtrl.cgi?stream=%d@zs=0@zoom=stop"

#  define IS_FLIP_SIDE	0x8000
#  define FLIP_SIDE_BIT_FILTER	0xFFFF7FFF

#  define PANGU_RESOLUTION 0.045 //PANGU one step to degree: 90-(-20.025)/2445
#  define PANGU_OFFSET_STEP 445 //-20.025 degree = 0 ; 0 degree = 445 ; 90 degree = 2445 ;
#  define PANGU_OFFSET_DEGREE 20.025 // -20.025 ~ 0 ~ 90
#  define CAM_MODULE_RESOLUTION 0.088 //one step to degree

int PanguToCamModuleX(unsigned int dwPanguX)
{
		double dCamModuleX;
		dCamModuleX = dwPanguX * PANGU_RESOLUTION;
		//X : 0 ~ 180 -> -180 ~ 0
		if ( dCamModuleX >180 ) dCamModuleX -= 360;
		dCamModuleX /= CAM_MODULE_RESOLUTION;
		return (int)dCamModuleX;
}

int main(void)
{
	unsigned int dwX = 5;
	printf("%u\n", 0x0F &( dwX>>8 )); 
	dwX = PanguToCamModuleX(7044);
	printf("%u\n", 0x0F & ( dwX>>8 )); 
	printf("%u\n", 0x0F & ( -dwX>>8 )); 

	return 0;
	
	while (1) 
	{
		printf("%d\n", (704 + 31) & (~31));
		printf("%d\n", (736 + 31) & (~31));
		printf("%d\n", (720 + 31) & (~31));
		/* code */
		printf(".\n");
		sleep(1);
	}
	printf("%ld\n", sizeof(g_dZoomPositionTableEH3300)/sizeof(unsigned int));
	unsigned int *g_dZoomPositionTable = g_dZoomPositionTableEH3300;
	printf( "sizeof(*ptr): %ld\n", sizeof(*g_dZoomPositionTable) );
	char szCmdBuf[37] = "";
	snprintf(szCmdBuf, sizeof(szCmdBuf), EPTZ_FIFOCMD_STOP, 1); 
	printf("%s\n",szCmdBuf);

	asm("nop ; nop ; nop ; nop");		
	if(1) { printf("shit\n"); return 0;};
	asm("nop ; nop ; nop ; nop");		
	unsigned char string[] = "camctrl.cgi?getpan";
	/*unsigned char ucParm1[5] = {0x81, 0x01, 0x04, 0x79, '\n'};*/
	unsigned char ucParm[5] = {81, 82, 83, 84, '\n'};
	printf("%s\n", ucParm);
	printf("Hello World!\n");
	fprintf(stderr, "%s\n", string+12);
	return 0;
}
