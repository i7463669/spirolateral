
#include <stdio.h>
#include <math.h>
//#include <SDL2/SDL.h>


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
	float maxX;
	float maxY;
	float minX;
	float minY;
}maxCoord;

int open_close_pattern( int, int);
maxCoord line_calculate(parameters para, maxCoord maxCoord, int *, float *, float *);
maxCoord boundary_test(float *, float *,maxCoord maxCoord);
maxCoord transform_scale(maxCoord mxCoord, int *, int *);


int main (void)
{
	parameters para;
	para.length = 3;
	para.numOfSeg = 5;
	para.angle = 40;

	para.X = 0;
	para.Y = 0;
	
	
	float Xn = para.X;
	float Yn = para.Y;
	
	float *pXn = &Xn;
	float *pYn = &Yn;
	int angleN = para.angle;
	int *pAngleN = &angleN;
	
	maxCoord maxCoord;
	maxCoord.maxX = para.X;
	maxCoord.minX = para.X;
	maxCoord.maxY = para.Y;
	maxCoord.minY = para.Y;
	
	
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 200;
	int winHeight = 200;
	/*
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		// Something went very wrong in the initialisation, all we can do is exit 
		perror("Whoops! Something went very wrong, cannot initialise SDL :(");
		return -1;
	}

	// Now we have got SDL initialised, we are ready to create a window!
	
	SDL_Window *window = SDL_CreateWindow("My Pointy Window!!!",  // The first parameter is the window title //
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	*/
	
	int openCloseResult = open_close_pattern(para.angle, para.numOfSeg);
	if (openCloseResult == 0)
	{
		printf("the pattern is close\n");
		for(int i = 1; i<=para.numOfSeg; i++)
		{
			maxCoord = line_calculate(para, maxCoord, pAngleN, pXn, pYn); //mac coordinates for closed pattern
		}
	}
	else
	{
		printf("the pattern is open\n");
		maxCoord = line_calculate(para, maxCoord, pAngleN, pXn, pYn);
		
	}
	printf ("this is X %06f\n", maxCoord.minX);
	printf ("this is Y %06f\n", maxCoord.minY);
	printf ("this is X %06f\n", maxCoord.maxX);
	printf ("this is Y %06f\n", maxCoord.maxY);
	//float moveDifX = 0-maxCoord.minX;
	//float moveDifY = 0-maxCoord.minY;
	int *pX = &para.X;
	int *pY = &para.Y;
	maxCoord = transform_scale(maxCoord, pX, pY);
	printf ("After this is X %06f\n", maxCoord.minX);
	printf ("this is Y %06f\n", maxCoord.minY);
	printf ("this is X %06f\n", maxCoord.maxX);
	printf ("this is Y %06f\n", maxCoord.maxY);
	return 0;
}




maxCoord transform_scale(maxCoord maxCoord, int *pX, int *pY)
{
	float moveDifX = 0 - maxCoord.minX;
	float moveDifY = 0 - maxCoord.minY;
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxCoord.minX, maxCoord.minY, 1};
	float maxXYvalue[3] = {maxCoord.maxX, maxCoord.maxY, 1};
	float minTransformX = 0;
	float minTransformY = 0;
	float maxTransformX = 0;
	float maxTransformY = 0;
	for( int i =0; i<3; i++)
	{
		minTransformX += (matrixT[0][i])*(minXYvalue[i]);
		minTransformY += (matrixT[1][i])*(minXYvalue[i]);
	}
	for( int j =0; j<3; j++)
	{
		maxTransformX += (matrixT[0][j])*(maxXYvalue[j]);
		maxTransformY += (matrixT[1][j])*(maxXYvalue[j]);
	}
	maxCoord.minX = minTransformX;
	maxCoord.minY = minTransformY;
	maxCoord.maxX = maxTransformX;
	maxCoord.maxY = maxTransformY;
	
	return maxCoord;
	
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

maxCoord boundary_test(float *pXn, float *pYn, maxCoord maxCoord)
{
	if (*pXn>maxCoord.maxX)
	{
		maxCoord.maxX = *pXn;
	}
	if (*pXn<maxCoord.minX)
	{
		maxCoord.minX = *pXn;
	}
		if (*pYn>maxCoord.maxY)
	{
		maxCoord.maxY = *pYn;
	}
	if (*pYn<maxCoord.minY)
	{
		maxCoord.minY = *pYn;
	}
	return maxCoord;
}

maxCoord line_calculate( parameters para, maxCoord maxCoord, int *pAngleN, float *pXn, float *pYn)
{
	
	float Xdif, Ydif;
	float rad = PI/180;
	float length = para.length;

	for (int i = 1; i<=para.numOfSeg; i++)
	{
		Xdif = para.length*(sin(rad*(*pAngleN)));
		*pXn += Xdif;
		Ydif = para.length*(cos(rad*(*pAngleN)));
		*pYn += Ydif;
		
		maxCoord = boundary_test(pXn, pYn, maxCoord);
		
		length *=2;
		*pAngleN += para.angle;
		if (*pAngleN >= 360)
		{
			*pAngleN -=360;
		}
	}
	return maxCoord;
}

