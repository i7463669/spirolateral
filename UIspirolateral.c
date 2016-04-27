

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


void pen_down(SDL_Renderer *, int, int, int, RGBcolour c);



int main (void)
{
	//setting the values for intial parameters of the turtle
	parameters para;
	para.length = 500;
	para.numOfSeg = 5;
	para.angle = 50;
	para.X = 0;
	para.Y = 10;

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
						SDL_RenderClear(renderer);
						pen_down(renderer, para.X, para.Y, para.length, c );
						
						SDL_RenderPresent(renderer);
						printf("HI\n");

						
						break;


					}

			}
		}
		






	}







	SDL_DestroyWindow( window );
	SDL_Quit();


	return 0;
}


void pen_down(SDL_Renderer *renderer, int x0, int y0, int length, RGBcolour c)
{
	SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,255);
	for(int i=0; i<=length; i++)
	{

		SDL_RenderDrawPoint(renderer, i, 10 );
	}

}
