#include <stdio.h>
#include <math.h>

#define PI 3.14159265

/* define functions */
typedef struct parameters
{
	int X;
	int Y;
	int numOfSeg;
	int angle;
	int length;
} parameters;

typedef struct maxCoord
{
	int maxX;
	int maxY;
	int minX;
	int minY;
}maxCoord;

parameters scale_position_check(struct parameters para);
int open_close_pattern( int, int);
void overlap_caluclate(struct parameters para, struct maxCoord maxCoord, float *, float *, float *);
maxCoord boundary_test(float *, float *, struct maxCoord maxCoord);


int main (void)
{
	parameters para;
	para.length = 3;
	para.numOfSeg = 5;
	para.angle = 36;
	para.X = 20;
	para.Y = 0;
	scale_position_check(para);
	
	return 0;
}

parameters scale_position_check(struct parameters para)
{
	int opencloseResult;
	printf("the X andd Y Coordinates, %d:%d\n",para.X, para.Y);
	
	opencloseResult = open_close_pattern(para.angle, para.numOfSeg);
	if (opencloseResult == 0)
	{
		printf("the pattern is closed\n");
	}
	else
	{
		printf("the pattern is open\n");
	}
	return para;
}



int open_close_pattern(int angle, int numOfSeg)
{
	if ((numOfSeg*angle)%180 ==0)
	{
		if (numOfSeg%2 ==0)
		{
			if ((numOfSeg <=2) || ((angle*numOfSeg)%360 == 0))
			{
				return 0;		/* open*/
			}
			else
			{
				return 1;		/* closed*/
			}
		}
		else
		{
			if ((numOfSeg*angle)%360 == 0)
			{
				return 0;		/* open*/
			}
			else
			{
				return 1;		/* closed*/
			}
		}
	}
	else
	{
		return 0;				/* open*/
	}
}

maxCoord boundary_test(float *pXn, float *pYn, struct maxCoord maxCoord)
{
	if (*pXn>maxCoord.maxX)
	{
		maxCoord.maxX = *pXn;
	}
	return maxCoord;
}

void overlap_calculate(struct parameters para, struct maxCoord maxCoord, float *pAngleN, float *pXn, float *pYn)
{
	
	float Xdif, Ydif;
	float rad = PI/180;
	float length = para.length;

	for (int i = 1; i<=para.numOfSeg; i++)
	{
		Xdif = para.length*(sin(rad*(*pAngleN)));
		*pXn +=Xdif;
		Ydif = para.length*(cos(rad*(*pAngleN)));
		*pYn +=Ydif;
		
		maxCoord = boundary_test(pXn, pYn, maxCoord);
		
		length *=2;
		*pAngleN += para.angle;
		if (*pAngleN >= 360)
		{
			*pAngleN -=360;
		}
	}
}

maxCoord max_coordinates(struct parameters para, struct maxCoord maxCoord, int opencloseResult)
{

	
	float *pXn = NULL;
	float *pYn = NULL;
	float *pAngleN = NULL;
	float angleN;
	float Xn = para.X;
	float Yn = para.Y;
	angleN = para.angle;
	pAngleN = &(angleN);
	pXn = &Xn;
	pYn = &Yn;
	maxCoord.maxX = *pXn;
	maxCoord.minX = *pXn;
	maxCoord.maxY = *pYn;
	maxCoord.minY = *pYn;
	
	if (opencloseResult == 0)
	{
		overlap_calculate(para, maxCoord, pAngleN, pXn, pYn);
		/*
		do
		{
			
		}while ((Xn && Yn) != (para.X && para.Y));
		*/
		
	}
	else
	{
		for (int i=1; i <= 5; i++)
		{
			
		}
	}
	
	return maxCoord;
}
