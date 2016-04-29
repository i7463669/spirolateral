

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
	float length;
}parameters;

typedef struct turtle_parameters
{
	float x;
	float y;
	int angle;
	int length;
}turtle_parameters;
typedef struct max_coordinates
{
	float maxX;
	float maxY;
	float minX;
	float minY;
}max_coordinates;

typedef struct scaleTranslateValue
{
	float scale;
	int positionX;
	int positionY;
}scaleTranslateValue;

typedef struct RGBcolour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
}RGBcolour;



int open_close_pattern( int, int);
//void line_calculate(struct parameters para,struct  maxCoord * maxC, struct turtle_parameters * turtle);


void bresenham_draw(int, int, int, int);

void max_coordinate_test(float *, float *,max_coordinates * maxC);
void find_max_coordinates(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int , int );
void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float *, int maxResolution);

//void transform_scale(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int, int);
void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int, int);
void pen_down(SDL_Renderer *, int, int, int, RGBcolour c);
int max_cycles(float, float);


int main (void)
{
	//setting the values for intial parameters of the turtle
	parameters para;
	para.length = 20;
	para.numOfSeg = 5;
	para.angle = 100;
	para.X = 0;
	para.Y = 0;

	turtle_parameters turtle;
	turtle.x = para.X;
	turtle.y = para.Y;
	turtle.angle = para.angle;
	turtle.length = para.length;



	//float Xn = para.X;
	//float Yn = para.Y;
	//int angleN = para.angle;
	//float *pXn = &Xn;
	//float *pYn = &Yn;

	//int *pAngleN = &angleN;


	max_coordinates maxC;
	maxC.maxX = para.X;
	maxC.minX = para.X;
	maxC.maxY = para.Y;
	maxC.minY = para.Y;



	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 600;
	int winHeight = 500;

	RGBcolour c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	
	
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
		//returns -1 to show something went wrong
		return -1;
	}


	int quit =0;

	SDL_Window *window = SDL_CreateWindow("Spirolateral",  // The first parameter is the window title //
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	
	
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
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
						printf("hi");
						break;
					}
				
				*/
				case SDL_MOUSEBUTTONDOWN:
				{
					SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(renderer);
					switch (incomingEvent.button.button)
					{
					
					
					
						case SDL_BUTTON_LEFT:
						{
							printf("LeftClick\n");
							int x = incomingEvent.button.x;
							//tests if the mouse position x is greater than 100
							printf("X position\t%d\n", x);
							printf("hay %d\n", turtle.length);
							if (x>=100)
							{
								para.length = 20;
								turtle.length = para.length;
								printf("hay %d\n", turtle.length);
								int repeat = 20;
								int openCloseResult  = open_close_pattern(para.angle, para.numOfSeg);
								if (openCloseResult == 0)
								{
									int numOfCycles = max_cycles(para.angle, para.numOfSeg);
									printf("closed\n");
									for (int k = 1; k<= numOfCycles; k++)
									{
										turtle.length= para.length;
										for (int d=1; d <=para.numOfSeg; d++)
										{
											find_max_coordinates(renderer, &turtle, &maxC, para.angle, para.length);
										}
										
									} 
									turtle.angle = para.angle;
									transform_scale(maxC, &turtle, &para.length, winHeight);
									for (int i = 1; i<=numOfCycles; i++)
									{
										turtle.length= para.length;
										for (int j = 1; j<= para.numOfSeg; j++)
										{
											turtle_move(renderer, &turtle, para.angle, para.length);
										}
										
									}
								}
								else
								{
									printf("open\n");
								int repeat = 5;
									for (int k = 1; k<= repeat; k++)
									{
										turtle.length= para.length;
										for (int d=1; d <=para.numOfSeg; d++)
										{
											find_max_coordinates(renderer, &turtle, &maxC, para.angle, para.length);
										}
										
									} 
									turtle.angle = para.angle;
									transform_scale(maxC, &turtle, &para.length, winHeight);
									for (int i = 1; i<= repeat; i++)
									{
										turtle.length= para.length;
										for (int j = 1; j<= para.numOfSeg; j++)
										{
											turtle_move(renderer, &turtle, para.angle, para.length);
										}
										
									}
								}
							
							
								
								//pen_down(renderer, para.X, para.Y, para.length, c );
									
								SDL_RenderPresent(renderer);
								
							}
							break;
						}
						default:
						{
						printf("not left click\n");
						}
					}
					break;
				}
			}
		
		
		}
	}


	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}

int max_cycles(float angle, float numOfSeg)
{

	angle = 180-angle;
	float outcome;
	float i=0;
	while (outcome !=0)
	{
		i++;
		outcome = ((angle*numOfSeg)/(360/i));
		printf ("oh hello outcome nice to see you %f\n", outcome);
		outcome = fmod(outcome, 1);
		
		
		printf ("oh hello i nice to see you %f\n", i);
	}
	printf("mememememmee %f", i);
	if (angle == 80 && ((int)numOfSeg % 2 ==1))
	{
		i *=2;
	}
	
	return i;
	
}



void pen_down(SDL_Renderer *renderer, int x0, int y0, int length, RGBcolour c)
{
	SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,255);
	for(int i=0; i<=length; i++)
	{

		SDL_RenderDrawPoint(renderer, i, 10 );
	}

}

int open_close_pattern(int angle, int numOfSeg)
{
	angle = 180-angle;
	printf ("%d\n", angle);
	if ((numOfSeg*angle)%180 ==0)
	{
		if (numOfSeg%2 ==0)
		{
			if ((numOfSeg <=2) || ((angle*numOfSeg)%360 == 0))
			{
				return 1;		/* open*/
			}
			else
			{
				return 0;		/* closed*/
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

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int angle, int length)
{
	float Xdif, Ydif;
	float rad = PI/180;
	float tempX, tempY;
	
	tempX = turtle->x;
	tempY = turtle->y;
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );


	Xdif = turtle->length*(cos(rad*(turtle->angle)));
	turtle->x += Xdif;
	
	
	Ydif = turtle->length*(sin(rad*(turtle->angle)));
	turtle->y += Ydif;
	
	SDL_RenderDrawLine(renderer, (int)tempX, (int)tempY, (int)turtle->x, (int)turtle->y);
	
	//length *=2;
	
	if (turtle->angle >= 360)
	{
		turtle->angle -=360;
	}
	turtle->angle += angle;
	turtle->length += length;
}

void max_coordinate_test(float *pXn, float *pYn, struct max_coordinates * maxC)
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


void find_max_coordinates(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int angle, int length)
{
	float Xdif, Ydif;
	float rad = PI/180;


	Xdif = turtle->length*(cos(rad*(turtle->angle)));
	turtle->x += Xdif;
	
	
	Ydif = turtle->length*(sin(rad*(turtle->angle)));
	turtle->y += Ydif;
	
	max_coordinate_test(&turtle->x, &turtle->y, maxC);
	
	//length *=2;
	
	if (turtle->angle >= 360)
	{
		turtle->angle -=360;
	}
	turtle->angle += angle;
	turtle->length += length;
}

void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float * length, int maxResolution)
{
	scaleTranslateValue scaleTran;
	printf("scmaxale %f\n", maxC.maxX);
	int moveDifX = 0 - (int)maxC.minX;
	int moveDifY = 0 - (int)maxC.minY;
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};
	float minTransformX = 0;
	float minTransformY = 0;
	float maxTransformX = 0;
	float maxTransformY = 0;
	float scale = 1;
	printf("tranform %f\n", maxC.maxY);
	printf("tranform %f\n", maxC.maxX);
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
	printf("tranform %f\n", maxTransformX);
	printf("tranform %f\n", maxC.maxX);
	scaleTran.positionX = moveDifX;
	scaleTran.positionY = moveDifY;

	printf("scmaxale %f\n", maxC.maxX);
	scale *= maxResolution/maxC.maxX;
	/*
	if (maxC.maxY>maxResolution)
	{
		
	}
	*/
	printf("scale %f\n", scale);

	//scale *= maxResolution/maxC.maxY;
	moveDifX *= scale;
	moveDifY *= scale;
	(*length)*= scale;

	turtle->x = moveDifX;
	turtle->y = moveDifY;
	printf("move X %f, move Y %f\n", turtle->x, turtle->y);
}
