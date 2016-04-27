
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>


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

typedef struct turtle_parameters
{
	int xPos;
	int yPos;
	int angle;
}turtle_parameters;
typedef struct maxCoord
{
	float maxX;
	float maxY;
	float minX;
	float minY;
}maxCoord;

typedef struct scale_translate
{
	float scale;
	int positionX;
	int positionY;
}scale_translate;

typedef struct RGBcolour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
}RGBcolour;

int open_close_pattern( int, int);
void line_calculate(struct parameters para,struct  maxCoord * maxC, struct turtle_parameters * turtle);
void max_coordinate_test(int *, int *,maxCoord * maxC);
void transform_scale(struct maxCoord maxC, struct parameters * para, int *, int *, int);
void bresenham_draw(int, int, int, int);

int main (void)
{
	//setting the values for intial parameters of the turtle
	parameters para;
	para.length = 3;
	para.numOfSeg = 5;
	para.angle = 50;
	para.X = 0;
	para.Y = 0;
	
	turtle_parameters turtle;
	turtle.xPos = para.X;
	turtle.yPos = para.Y;
	turtle.angle = para.angle; 
	
	
	
	//float Xn = para.X;
	//float Yn = para.Y;
	//int angleN = para.angle;
	//float *pXn = &Xn;
	//float *pYn = &Yn;
	
	//int *pAngleN = &angleN;
	

	maxCoord maxC;
	maxC.maxX = para.X;
	maxC.minX = para.X;
	maxC.maxY = para.Y;
	maxC.minY = para.Y;
	
	
	
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 500;
	int winHeight = 500;
	
	
	/*
	
	int openCloseResult = open_close_pattern(para.angle, para.numOfSeg);
	
	
	if (openCloseResult == 0)
	{
		printf("the pattern is close\n");
		for(int i = 1; i<=para.numOfSeg; i++)
		{
			line_calculate(para, &maxC, &turtle); //max coordinates for closed pattern
		}
		
	}
	else
	{
		printf("the pattern is open\n");
		line_calculate(para, &maxC, &turtle);
	}
	transform_scale(maxC, &para.X, &para.Y, winWidth);
	*/
	
	
	
	
	

	// initialising SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{

		perror("Error");
		//returns -1 to show somethign went wrong
		return -1;
	}


	int quit =0;
	
	SDL_Window *window = SDL_CreateWindow("Spirolateral",  // The first parameter is the window title //
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		
		
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
		
		
	while (quit == 0)
	{
		SDL_Event incomingEvent;
		while( SDL_PollEvent( &incomingEvent ) )
		{
			switch( incomingEvent.type )
			{
				case SDL_QUIT:
					{
						quit = 1;
						break;
					}
				/*
				case SDL_MOUSEMOTION:
					{
					
						break;
					}
				*/
				case SDL_MOUSEBUTTONDOWN:
					{
						
						break;
					}
			}
		
		
		/*
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
			*/
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

			 //Clear the entire screen to our selected colour 
			 
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		
		}
		
	int openCloseResult = open_close_pattern(para.angle, para.numOfSeg);
	
	if (openCloseResult == 0)
	{
		printf("the pattern is close\n");
		for(int i = 1; i<=para.numOfSeg; i++)
		{
			line_calculate(para, &maxC, &turtle); //max coordinates for closed pattern
		}
		
	}
	else
	{
		printf("the pattern is open\n");
		line_calculate(para, &maxC, &turtle);
	}
	transform_scale(maxC, &para, &para.X, &para.Y, winWidth);
	
	}
	
	
	SDL_DestroyWindow( window );
	SDL_Quit();
	
	
	
	

	printf ("this is X %06f\n", maxC.minX);
	printf ("this is Y %06f\n", maxC.minY);
	printf ("this is X %06f\n", maxC.maxX);
	printf ("this is Y %06f\n", maxC.maxY);
	//float moveDifX = 0-maxCoord.minX;
	//float moveDifY = 0-maxCoord.minY;
	//int *pX = &para.X;
	//int *pY = &para.Y;
	//transform_scale(maxC, &para.X,  &para.Y, winHeight);
	printf ("After this is X %06f\n", maxC.minX);
	printf ("this is Y %06f\n", maxC.minY);
	printf ("this is X %06f\n", maxC.maxX);
	printf ("this is Y %06f\n", maxC.maxY);
	return 0;
}


draw(SDL_Renderer *renderer int x0, int y0, int Xn, int Yn, RGBcolour c)
{
	int dx = abs(xn-x0), sx = x0<Xn ? 1 : -1;
	int dy = abs(yn-y0), sy = y0<Yn ? 1 : -1;
	int error = (dx>dy ? dx : -dy)/2, e2;
	
	SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,255);
	while(1)
	{
		/* draw point only if coordinate is valid */
		SDL_RenderDrawPoint(renderer,x0,y0);
		if(x0==Xn && y0==Yn) break;
		e2 = error;
		if(e2 >-dx) { error -= dy; x0 += sx; }
		if(e2 < dy) { error += dx; y0 += sy; }
	}
	
}








void bresenham_draw(int x0, int y0, int Xn, int Yn)
{
	float error;
	int difX = Xn-x0;
	int difY = Yn-y0;
	error = 2*(difY-difX);
	
	draw(SDL_Renderer *renderer, x0, y0, Xn, Yn, RGBcolour c)
}


void transform_scale(struct maxCoord maxC, struct parameters * para, int *pX, int *pY,int maxResolution)
{
	scale_translate scaTran;

	float moveDifX = 0 - maxC.minX;
	float moveDifY = 0 - maxC.minY;
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};
	float minTransformX = 0;
	float minTransformY = 0;
	float maxTransformX = 0;
	float maxTransformY = 0;
	float scale = 1;

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
	
	scaTran.positionX = moveDifX;
	scaTran.positionY = moveDifY;
	
	if ((maxC.maxX =! maxResolution) && (maxC.maxX < maxResolution))
	{
		scale *= (maxResolution/maxC.maxX);
	}
	if ((maxC.maxY =! maxResolution) && (maxC.maxX < maxResolution))
	{
		scale *= (maxResolution/maxC.maxX);
	}
	para->length *= scale;
	para->X = moveDifX;
	para->Y = moveDifY;
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


void max_coordinate_test(int *pXn, int *pYn, struct maxCoord * maxC)
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

void line_calculate( struct parameters para, struct maxCoord * maxC, struct turtle_parameters * turtle)
{
	
	int Xdif, Ydif;
	float rad = PI/180;
	int length = para.length;

	for (int i = 1; i<=para.numOfSeg; i++)
	{
		Xdif = para.length*(sin(rad*(turtle->angle)));
		turtle->xPos += Xdif;
		Ydif = para.length*(cos(rad*(turtle->angle)));
		turtle->yPos += Ydif;
		
		 max_coordinate_test(&turtle->xPos, &turtle->yPos, maxC);
		
		length *=2;
		
		if (turtle->angle >= 360)
		{
			turtle->angle -=360;
		}
		turtle->angle += para.angle;
	}
}

void pen_down( struct parameters para, struct maxCoord * maxC, struct turtle_parameters * turtle)
{
	
	int Xdif, Ydif;
	float rad = PI/180;
	int length = para.length;
	int X0, Y0;
	for (int i = 1; i<=para.numOfSeg; i++)
	{
		X0 = turtle->xPos;
		Y0 = turtle->yPos;
		Xdif = para.length*(sin(rad*(turtle->angle)));
		turtle->xPos += Xdif;
		Ydif = para.length*(cos(rad*(turtle->angle)));
		turtle->yPos += Ydif;
		
		length *=2;
		
		if (turtle->angle >= 360)
		{
			turtle->angle -=360;
		}
		turtle->angle += para.angle;
		
		bresenham_draw(X0, Y0, turtle->xPos, turtle->yPos);
	}
}
