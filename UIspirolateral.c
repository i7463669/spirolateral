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

typedef struct RGBcolour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
}RGBcolour;



int open_close_pattern( int, int);

//void bresenham_draw(int, int, int, int);

void max_coordinate_test(float *, float *,max_coordinates * maxC);
void find_max_coordinates(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int , int );
void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float *, int maxResolution);

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int, int, SDL_Surface * sshot);
void pen_down(SDL_Renderer *, int, int, int, RGBcolour c);
int max_cycles(float, float);
void turtle_draw(SDL_Renderer * renderer, parameters para, turtle_parameters turtle, max_coordinates, int, SDL_Surface *);
void Iline(SDL_Surface *img,int ,int ,int ,int , RGBcolour col);


int main (void)
{
	//setting the values for intial parameters of the turtle
	parameters para;
	para.length = 20;
	para.numOfSeg = 10;
	para.angle = 80;
	para.X = 0;
	para.Y = 0;

	turtle_parameters turtle;
	turtle.x = para.X;
	turtle.y = para.Y;
	turtle.angle = para.angle;
	turtle.length = para.length;

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
		SDL_WINDOW_SHOWN);


	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, winHeight, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_FillRect(sshot, NULL, SDL_MapRGB(sshot->format, 255, 255, 255));
	SDL_Texture * renderTexture = NULL;
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

								turtle.length = para.length;
								printf("hay %d\n", turtle.length);
								int openCloseResult  = open_close_pattern(para.angle, para.numOfSeg);
								if (openCloseResult == 0)
								{
									printf("closed\n");
									turtle_draw(renderer, para, turtle, maxC, winHeight, sshot);
								}
								else
								{
									printf("open\n");
									turtle_draw(renderer, para, turtle, maxC, winHeight, sshot);
								}
								SDL_Rect srcX;
								srcX.x = 0;
								srcX.y = 0;
								srcX.w = winHeight;
								srcX.h = winHeight;
								renderTexture = SDL_CreateTextureFromSurface(renderer, sshot);
								SDL_RenderCopy(renderer, renderTexture, NULL, &srcX);
								SDL_RenderPresent(renderer);
								
							}
							//SDL_Surface *surfaceEncode = SDL_ConvertrSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
							 
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



void turtle_draw(SDL_Renderer * renderer, parameters para, turtle_parameters turtle, max_coordinates maxC, int winHeight, SDL_Surface * sshot)
{
	printf("length %d\n", para.angle);
	int numOfCycles = max_cycles(para.angle, para.numOfSeg);

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
			
			
			turtle_move(renderer, &turtle, para.angle, para.length, sshot);
			

		}
		
			//--------------------------------------------------------------------------------------------
			//http://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot
			char filepath[] = "screenshot";
			sprintf(filepath, "screen%d.bmp", i);
			printf("\n%s\n", filepath);
			//SDL_Surface *sshot = SDL_CreateRGBSurface(0, winHeight, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
			//SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
			
			SDL_SaveBMP(sshot, filepath);
			//SDL_FreeSurface(sshot);
			
			
			
			//---------------------------------------------------------------------------------------
			
	}
}


int max_cycles(float angle, float numOfSeg)
{
	printf("angle %f\n", numOfSeg);
	angle = 180-angle;
	printf("angle %f\n", angle);
	float outcome = 1;
	float i=0;
	while (outcome !=0)
	{
		i++;
		outcome = ((angle*numOfSeg)/(360/i));
		outcome = fmod(outcome, 1);
	}
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

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int angle, int length, SDL_Surface * sshot)
{
	float Xdif, Ydif;
	float rad = PI/180;
	float X0, Y0;
	RGBcolour col;
	col.r = 0;
	col.g = 0;
	col.b = 0;


	X0 = turtle->x;
	Y0 = turtle->y;
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
	
	Xdif = turtle->length*(cos(rad*(turtle->angle)));
	turtle->x += Xdif;
	Ydif = turtle->length*(sin(rad*(turtle->angle)));
	turtle->y += Ydif;
	//SDL_RenderDrawLine(renderer, (int)X0, (int)Y0, (int)turtle->x, (int)turtle->y);
	Iline(sshot, X0, Y0, turtle->x, turtle->y, col);

	if (turtle->angle >= 360)
	{
		turtle->angle -=360;
	}
	turtle->angle += angle;
	turtle->length += length;
}
//-------------------------------------------------------------------------------------------------------------------------------
//Eikes code
void Iline(SDL_Surface *img,int x0,int y0,int xn,int yn,RGBcolour col)
{
	int dx = abs(xn-x0), sx = x0<xn ? 1 : -1;
	int dy = abs(yn-y0), sy = y0<yn ? 1 : -1;
	int error = (dx>dy ? dx : -dy)/2, e2;
	Uint32 pixel = SDL_MapRGB(img->format,col.r,col.g,col.b);
	Uint32 *pixels = (Uint32*)img->pixels; /* pixel array in the SDL_Surface record */
	while(1)
	{
		/* draw point only if coordinate is valid, i.e. within the pixel array */
		/* x0+y0*img->w is the 1D offset location for the 2D pixel coordinate (x0,y0) */
		if(x0>=0 && x0<img->w && y0>=0 && y0<img->h) pixels[x0+y0*img->w]=pixel;
		if(x0==xn && y0==yn) break;
		e2 = error;
		if(e2 >-dx) { error -= dy; x0 += sx; }
		if(e2 < dy) { error += dx; y0 += sy; }
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------




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
	if (turtle->angle >= 360)
	{
		turtle->angle -=360;
	}
	turtle->angle += angle;
	turtle->length += length;
}

void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float * length, int maxResolution)
{
	printf("scmaxale %f\n", maxC.maxX);
	int moveDifX = 0 - (int)maxC.minX;
	int moveDifY = 0 - (int)maxC.minY;
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};
	
	float minTransformX, minTransformY, maxTransformX, maxTransformY = 0;
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


	printf("scmaxale %f\n", maxC.maxX);
	scale *= maxResolution/maxC.maxX;
	scale *= maxResolution/maxC.maxY;

	printf("scale %f\n", scale);

	moveDifX *= scale;
	moveDifY *= scale;
	(*length)*= scale;

	turtle->x = moveDifX;
	turtle->y = moveDifY;
	printf("move X %f, move Y %f\n", turtle->x, turtle->y);
}
