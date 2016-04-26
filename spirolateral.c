
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
}parameters;

typedef struct maxCoord
{
	float maxX;
	float maxY;
	float minX;
	float minY;
}maxCoord;

int open_close_pattern( int, int);
void line_calculate(struct parameters para,struct  maxCoord *  maxC, int *, float *, float *);
void boundary_test(float *, float *,maxCoord * maxC);
maxCoord transform_scale(struct maxCoord maxC, int *, int *);


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
	
	//float *pXn = &Xn;
	//float *pYn = &Yn;
	int angleN = para.angle;
	//int *pAngleN = &angleN;
	
	maxCoord maxC;
	maxC.maxX = para.X;
	maxC.minX = para.X;
	maxC.maxY = para.Y;
	maxC.minY = para.Y;
	
	
	
	int winPosX = 1000;
	int winPosY = 1000;
	int winWidth = 1000;
	int winHeight = 1000;
/*
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		// Something went very wrong in the initialisation, all we can do is exit 
		perror("Whoops! Something went very wrong, cannot initialise SDL :(");
		return -1;
	}

	// Now we have got SDL initialised, we are ready to create a window!
	int quit =0;
	SDL_Event e;
	
	
		SDL_Window *window = SDL_CreateWindow("My Pointy Window!!!",  // The first parameter is the window title //
			winPosX, winPosY,
			winWidth, winHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			
		SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	while (quit == 0)
	{
		SDL_Event incomingEvent;
		while( SDL_PollEvent( &incomingEvent ) )
		{
			if (e.type == SDL_QUIT )
			{
				
				quit = 1;
				break;
			}
		}
	}
*/
	
	int openCloseResult = open_close_pattern(para.angle, para.numOfSeg);
	if (openCloseResult == 0)
	{
		printf("the pattern is close\n");
		for(int i = 1; i<=para.numOfSeg; i++)
		{
			line_calculate(para, &maxC, &angleN, &Xn, &Yn); //max coordinates for closed pattern
		}
	}
	else
	{
		printf("the pattern is open\n");
		line_calculate(para, &maxC, &angleN, &Xn, &Yn);
		
	}
	printf ("this is X %06f\n", maxC.minX);
	printf ("this is Y %06f\n", maxC.minY);
	printf ("this is X %06f\n", maxC.maxX);
	printf ("this is Y %06f\n", maxC.maxY);
	//float moveDifX = 0-maxCoord.minX;
	//float moveDifY = 0-maxCoord.minY;
	int *pX = &para.X;
	int *pY = &para.Y;
	maxC = transform_scale(maxC, pX, pY);
	printf ("After this is X %06f\n", maxC.minX);
	printf ("this is Y %06f\n", maxC.minY);
	printf ("this is X %06f\n", maxC.maxX);
	printf ("this is Y %06f\n", maxC.maxY);
	return 0;
}




struct maxCoord transform_scale(struct maxCoord maxC, int *pX, int *pY)
{
	float moveDifX = 0 - maxC.minX;
	float moveDifY = 0 - maxC.minY;
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};
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
	maxC.minX = minTransformX;
	maxC.minY = minTransformY;
	maxC.maxX = maxTransformX;
	maxC.maxY = maxTransformY;
	
	return maxC;
	
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


void boundary_test(float *pXn, float *pYn, struct maxCoord * maxC)
{
	if (*pXn>maxC->maxX)
	{
		maxC->maxX = *pXn;
	}
	if (*pXn<maxC->minX)
	{
		maxC->minX = *pXn;
	}
		if (*pYn>maxC->maxY)
	{
		maxC->maxY = *pYn;
	}
	if (*pYn<maxC->minY)
	{
		maxC->minY = *pYn;
	}
}

void line_calculate( struct parameters para, struct maxCoord * maxC, int *pAngleN, float *pXn, float *pYn)
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
		
		 boundary_test(pXn, pYn, maxC);
		
		length *=2;
		*pAngleN += para.angle;
		if (*pAngleN >= 360)
		{
			*pAngleN -=360;
		}
	}
}

