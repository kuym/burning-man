#include <stdio.h>

signed short const kSinLUT[65] =
{
	0,804,1607,2410,3211,4011,4807,5601,
	6392,7179,7961,8739,9511,10278,11038,11792,
	12539,13278,14009,14732,15446,16150,16845,17530,
	18204,18867,19519,20159,20787,21402,22004,22594,
	23169,23731,24278,24811,25329,25831,26318,26789,
	27244,27683,28105,28510,28897,29268,29621,29955,
	30272,30571,30851,31113,31356,31580,31785,31970,
	32137,32284,32412,32520,32609,32678,32727,32757,
	32767
};

signed short	ksin(unsigned int v)
{
	v &= 0xFF;
	signed short s = (v & 0x40)? kSinLUT[64 - (v & 0x3F)] : kSinLUT[(v & 0x3F)];
	return((v & 0x80)? -s : s);
}

volatile unsigned int gT = 0;
volatile signed int	gL = 0, gR = 0, gLD = 68, gRD = 96;

int main(void)
{
	for(int i = 0; i < 512; i++)
	{
		int v; //= ksin(i) >> 4;

		if(gT++ & 1)
		{
			v = gR;
			gR += gRD;
			if(gR >= 3276)
			{
				gR = 3276;
				gRD = -gRD;
			}
			else if(gR <= -3276)
			{
				gR = -3276;
				gRD = -gRD;
			}
		}
		else
		{
			v = gL;
			gL += gLD;
			if(gL >= 3276)
			{
				gL = 3276;
				gLD = -gLD;
			}
			else if(gL <= -3276)
			{
				gL = -3276;
				gLD = -gLD;
			}
		}


		printf("%i\n", v);
	}
}