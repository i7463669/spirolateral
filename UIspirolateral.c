#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
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
void max_coordinate_test(float *, float *,max_coordinates * maxC);
void find_max_coordinates(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int , int );
void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float *, int maxResolution, int);

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int, int, SDL_Surface * sshot, RGBcolour);
//void pen_down(SDL_Renderer *, int, int, int, RGBcolour c);
int max_cycles(float, float);
void turtle_draw(SDL_Renderer * renderer, parameters para, turtle_parameters turtle, max_coordinates, int, SDL_Surface *, RGBcolour, int, int);
void Iline(SDL_Surface *img,int ,int ,int ,int , RGBcolour col);

void drawingOperation(SDL_Renderer * renderer, parameters , turtle_parameters , max_coordinates , int ,SDL_Surface * , RGBcolour, int, int );

void field_change(Uint8 *, SDL_Surface *, SDL_Texture *, SDL_Renderer *, SDL_Color , char *, int, TTF_Font *);
void colourOptions(int, int, RGBcolour *colours , int, int);




int main (void)
{
	//setting the values for intial parameters of the turtle
	parameters para;
	para.length = 10;
	para.numOfSeg = 15;
	para.angle = 56;
	para.X = 0;
	para.Y = 0;
	
	RGBcolour lineColour;
	lineColour.r = 10;
	lineColour.g = 255;
	lineColour.b = 255;

	RGBcolour backColour;
	backColour.r = 0;
	backColour.g = 0;
	backColour.b = 0;

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
	int winHeight = 800;
	int winWidth = winHeight + 400;
	/*
	RGBcolour c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	*/
	// initialising SDL
	TTF_Init();
	if( TTF_Init() != 0 )
	{

		perror("Error");
		//returns -1 to show something went wrong
		return -1;
	}
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

	SDL_SetRenderDrawColor( renderer, backColour.r, backColour.g, backColour.b, 255 );
	SDL_RenderClear(renderer);
	
	
	
	
	SDL_Surface * UIbg = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	
	SDL_Texture * renderTexture = NULL;
	
	SDL_Rect UI;
	UI.x = winHeight;
	UI.y = 0;
	UI.w = 400;
	UI.h = winHeight;
	
	SDL_Rect UIbox;
	UIbox.x = winHeight;
	UIbox.y = 0;
	UIbox.w = 400;
	UIbox.h = 600;
	SDL_FillRect(UIbg, &UI, SDL_MapRGB(UIbg->format, 102, 102, 102));
	
	SDL_Texture * UItexture = SDL_CreateTextureFromSurface(renderer, UIbg);
	SDL_RenderCopy(renderer, UItexture, NULL, NULL);
	
	SDL_Surface * UIlayout = SDL_LoadBMP("UILayout.bmp");
	SDL_Texture * UIlayoutTex = SDL_CreateTextureFromSurface(renderer, UIlayout);
	SDL_RenderCopy(renderer, UIlayoutTex, NULL, &UIbox);
	
	
	int autoScale =1;
	
	//int textpos = winHeight+150;
	char lcredText[4];
	char lcgreenText[4];
	char lcblueText[4];
	
	char bgcredText[4];
	char bgcgreenText[4];
	char bgcblueText[4];
	char angleText[4];
	char numOfSegText[4];
	char lengthText[4];
	SDL_Color colour = { 0, 0, 0 };
	TTF_Font *font = TTF_OpenFont("arial.ttf", 100);
		
		
	sprintf(lcredText, "%03d", lineColour.r);
	SDL_Surface *lcredTextSurf = TTF_RenderText_Solid(font,lcredText, colour);
	SDL_Texture *lcredTextTex = SDL_CreateTextureFromSurface(renderer,lcredTextSurf);
	
	sprintf(lcgreenText, "%03d", lineColour.g);
	SDL_Surface *lcgreenTextSurf = TTF_RenderText_Solid(font,lcgreenText, colour);
	SDL_Texture *lcgreenTextTex = SDL_CreateTextureFromSurface(renderer,lcgreenTextSurf);
	
	sprintf(lcblueText, "%03d", lineColour.b);
	SDL_Surface *lcblueTextSurf = TTF_RenderText_Solid(font,lcblueText, colour);
	SDL_Texture *lcblueTextTex = SDL_CreateTextureFromSurface(renderer,lcblueTextSurf);
	
	sprintf(bgcredText, "%03d", backColour.r);
	SDL_Surface *bgcredTextSurf = TTF_RenderText_Solid(font,bgcredText, colour);
	SDL_Texture *bgcredTextTex = SDL_CreateTextureFromSurface(renderer,bgcredTextSurf);
	
	sprintf(bgcgreenText, "%03d", backColour.g);
	SDL_Surface *bgcgreenTextSurf = TTF_RenderText_Solid(font,bgcgreenText, colour);
	SDL_Texture *bgcgreenTextTex = SDL_CreateTextureFromSurface(renderer,bgcgreenTextSurf);
	
	sprintf(bgcblueText, "%03d", backColour.b);
	SDL_Surface *bgcblueTextSurf = TTF_RenderText_Solid(font,bgcblueText, colour);
	SDL_Texture *bgcblueTextTex = SDL_CreateTextureFromSurface(renderer,bgcblueTextSurf);
	
	sprintf(angleText, "%03d", para.angle);
	SDL_Surface *angleTextSurf = TTF_RenderText_Solid(font,angleText, colour);
	SDL_Texture *angleTextTex = SDL_CreateTextureFromSurface(renderer,angleTextSurf);
	
	sprintf(numOfSegText, "%03d", para.numOfSeg);
	SDL_Surface *numOfSegTextSurf = TTF_RenderText_Solid(font,numOfSegText, colour);
	SDL_Texture *numOfSegTextTex = SDL_CreateTextureFromSurface(renderer,numOfSegTextSurf);
	
	sprintf(lengthText, "%03d", (int)para.length);
	SDL_Surface *lengthTextSurf = TTF_RenderText_Solid(font,lengthText, colour);
	SDL_Texture *lengthTextTex = SDL_CreateTextureFromSurface(renderer,lengthTextSurf);
	
	
	
	
	
	
	SDL_Rect lcrBox;
	lcrBox.x = winHeight+150;
	lcrBox.y = 50;
	lcrBox.w = 50;
	lcrBox.h = 25;
	
	SDL_Rect lcgBox;
	lcgBox.x = winHeight+150;
	lcgBox.y = 75;
	lcgBox.w = 50;
	lcgBox.h = 25;
	
	SDL_Rect lcbBox;
	lcbBox.x = winHeight+150;
	lcbBox.y = 100;
	lcbBox.w = 50;
	lcbBox.h = 25;
	
	
	SDL_Rect bgcrBox;
	bgcrBox.x = winHeight+150;
	bgcrBox.y = 150;
	bgcrBox.w = 50;
	bgcrBox.h = 25;
	
	SDL_Rect bgcgBox;
	bgcgBox.x = winHeight+150;
	bgcgBox.y = 175;
	bgcgBox.w = 50;
	bgcgBox.h = 25;
	
	SDL_Rect bgcbBox;
	bgcbBox.x = winHeight+150;
	bgcbBox.y = 200;
	bgcbBox.w = 50;
	bgcbBox.h = 25;
	
	SDL_Rect angleBox;
	angleBox.x = winHeight+150;
	angleBox.y = 250;
	angleBox.w = 50;
	angleBox.h = 25;
	
	SDL_Rect numOfSegBox;
	numOfSegBox.x = winHeight+150;
	numOfSegBox.y = 300;
	numOfSegBox.w = 50;
	numOfSegBox.h = 25;
	
	SDL_Rect lengthBox;
	lengthBox.x = winHeight+300;
	lengthBox.y = 350;
	lengthBox.w = 50;
	lengthBox.h = 25;
	
	
	
	SDL_RenderCopy(renderer, lcredTextTex, NULL, &lcrBox);
	SDL_RenderCopy(renderer, lcgreenTextTex, NULL, &lcgBox);
	SDL_RenderCopy(renderer, lcblueTextTex, NULL, &lcbBox);
	
	SDL_RenderCopy(renderer, bgcredTextTex, NULL, &bgcrBox);
	SDL_RenderCopy(renderer, bgcgreenTextTex, NULL, &bgcgBox);
	SDL_RenderCopy(renderer, bgcblueTextTex, NULL, &bgcbBox);
	
	
	
	SDL_RenderCopy(renderer, angleTextTex, NULL, &angleBox);
	SDL_RenderCopy(renderer, numOfSegTextTex, NULL, &numOfSegBox);
	SDL_RenderCopy(renderer, lengthTextTex, NULL, &lengthBox);
	SDL_RenderPresent(renderer);
	//SDL_Surface *sshot = SDL_CreateRGBSurface(0, winHeight, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	//SDL_FillRect(sshot, NULL, SDL_MapRGB(sshot->format, backColour.r, backColour.g, backColour.b));
	
	
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
					//SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(renderer);
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, winHeight, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
					SDL_FillRect(sshot, NULL, SDL_MapRGB(sshot->format, backColour.r, backColour.g, backColour.b));
					switch (incomingEvent.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							int incre_type=-1;

							printf("LeftClick\n");
							int x = incomingEvent.button.x;
							int y = incomingEvent.button.y;
							//tests if the mouse position x is greater than 100
							printf("X position\t%d\n", x);
							int captSet = 0;
							int lcOffset= 50;
							int bgcOffset = 150;
							colourOptions(x, y, &lineColour, winHeight, lcOffset);
							colourOptions(x, y, &backColour, winHeight, bgcOffset);
							
							
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 250)&&(y<=275))
							{
								printf("YES");
								if (para.angle> 1)
								{
									para.angle-=1;
								}

							}
							if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= 250)&&(y<=275))
							{
								if (para.angle< 179)
								{
									para.angle +=1;
								}

							}
							
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 300)&&(y<=325))
							{
								printf("YES");
								if (para.numOfSeg> 1)
								{
									para.numOfSeg-=1;
								}

							}
							if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= 300)&&(y<=325))
							{
								if (para.numOfSeg< 16)
								{
									para.numOfSeg +=1;
								}

							}
							
							
							
							if (x>=(winHeight+275)&&(x<= winHeight+300)&&(y >= 350)&&(y<=375))
							{
								printf("why is this not working %d\n", (int)para.length);
								printf("YES\n");
								if (para.length> 1)
								{
									para.length -= 1;
									printf("why is this not working %d\n", (int)para.length);
								}

							}
							if (x>=(winHeight+275)&&(x<= winHeight+300)&&(y >= 350)&&(y<=375))
							{
								if (para.length< 100)
								{
									para.length += 1;
								}

							}
							
							
							
							
							
							
							
							
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 400)&&(y<=425))
							{
								printf("\nme\n");
								para.numOfSeg = 10;
								para.angle = 80;
							}
							else if (x>=(winHeight+100)&&(x<= winHeight+150)&&(y >= 400)&&(y<=425))
							{
								printf("\nproblem\n");
								para.numOfSeg = 3;
								para.angle = 170;
							}
							else if (x>=(winHeight+150)&&(x<= winHeight+200)&&(y >= 400)&&(y<=425))
							{
								printf("\nproblem\n");
								para.numOfSeg = 7;
								para.angle = 110;
							}
							else if (x>=(winHeight+200)&&(x<= winHeight+250)&&(y >= 400)&&(y<=425))
							{
								printf("\nproblem\n");
								para.numOfSeg = 4;
								para.angle = 90;
							}
							else if (x>=(winHeight+250)&&(x<= winHeight+300)&&(y >= 400)&&(y<=425))
							{
								printf("\nproblem\n");
								para.numOfSeg = 3;
								para.angle = 120;
							}							
							else if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= 400)&&(y<=425))
							{
								printf("\nproblem\n");
								para.numOfSeg = 5;
								para.angle = 40;
							}
							
							
							if (x>=(winHeight+50)&&(x<= winHeight+150) &&(y >= 350)&&(y<=375))
							{
								autoScale =1;
							}
							if (x>=(winHeight+150)&&(x<= winHeight+350) &&(y >= 350)&&(y<=375))
							{
								autoScale =0;
							}
							
							
							if (x>=(winHeight+250)&&(x<= winHeight+350) &&(y >= 500)&&(y<=550))
							{
								captSet = 1;
								drawingOperation(renderer, para, turtle, maxC, winHeight, sshot,  lineColour, captSet, autoScale);
							}
							else if (x>=(winHeight+250)&&(x<= winHeight+350) &&(y >= 450)&&(y<=500))
							{
								captSet = 2;
								drawingOperation(renderer, para, turtle, maxC, winHeight, sshot,  lineColour, captSet, autoScale);
							}
							else if(x>=(winHeight+50)&&(x<= winHeight+150) &&(y >= 450)&&(y<=500))
							{
								captSet = 0;
								drawingOperation(renderer, para, turtle, maxC, winHeight, sshot,  lineColour, captSet, autoScale);
								
							}
							
								/*
								turtle.length = para.length;
								int openCloseResult  = open_close_pattern(para.angle, para.numOfSeg);
								if (openCloseResult == 0)
								{
									printf("closed\n");
									turtle_draw(renderer, para, turtle, maxC, winHeight, sshot, lineColour);
								}
								else
								{
									printf("open\n");
									turtle_draw(renderer, para, turtle, maxC, winHeight, sshot, lineColour);
								}
								*/
								
								/*
								sprintf(lcredText, "%03d", lineColour.r);
								SDL_Surface *textSurf = TTF_RenderText_Solid(lcredText,lineCr, colour);
								textTex = SDL_CreateTextureFromSurface(renderer,textSurf);
								*/
								
								
								
								SDL_Rect spiral;
								spiral.x = 0;
								spiral.y = 0;
								spiral.w = winHeight;
								spiral.h = winHeight;
								UItexture = SDL_CreateTextureFromSurface(renderer, UIbg);
								SDL_RenderCopy(renderer, UItexture, NULL, NULL);
								renderTexture = SDL_CreateTextureFromSurface(renderer, sshot);
								SDL_RenderCopy(renderer, renderTexture, NULL, &spiral);
								
								
								SDL_RenderCopy(renderer, UIlayoutTex, NULL, &UIbox);
								
								
								//SDL_RenderCopy(renderer, textTex, NULL, &crBox);
								//SDL_FreeSurface(textSurf);
								sprintf(lcredText, "%03d", lineColour.r);
								SDL_Surface *lcredTextSurf = TTF_RenderText_Solid(font,lcredText, colour);
								SDL_Texture *lcredTextTex = SDL_CreateTextureFromSurface(renderer,lcredTextSurf);
								
								sprintf(lcgreenText, "%03d", lineColour.g);
								SDL_Surface *lcgreenTextSurf = TTF_RenderText_Solid(font,lcgreenText, colour);
								SDL_Texture *lcgreenTextTex = SDL_CreateTextureFromSurface(renderer,lcgreenTextSurf);
								
								sprintf(lcblueText, "%03d", lineColour.b);
								SDL_Surface *lcblueTextSurf = TTF_RenderText_Solid(font,lcblueText, colour);
								SDL_Texture *lcblueTextTex = SDL_CreateTextureFromSurface(renderer,lcblueTextSurf);
								
								sprintf(bgcredText, "%03d", backColour.r);
								SDL_Surface *bgcredTextSurf = TTF_RenderText_Solid(font,bgcredText, colour);
								SDL_Texture *bgcredTextTex = SDL_CreateTextureFromSurface(renderer,bgcredTextSurf);
								
								sprintf(bgcgreenText, "%03d", backColour.g);
								SDL_Surface *bgcgreenTextSurf = TTF_RenderText_Solid(font,bgcgreenText, colour);
								SDL_Texture *bgcgreenTextTex = SDL_CreateTextureFromSurface(renderer,bgcgreenTextSurf);
								
								sprintf(bgcblueText, "%03d", backColour.b);
								SDL_Surface *bgcblueTextSurf = TTF_RenderText_Solid(font,bgcblueText, colour);
								SDL_Texture *bgcblueTextTex = SDL_CreateTextureFromSurface(renderer,bgcblueTextSurf);
								
								sprintf(angleText, "%03d", para.angle);
								SDL_Surface *angleTextSurf = TTF_RenderText_Solid(font,angleText, colour);
								SDL_Texture *angleTextTex = SDL_CreateTextureFromSurface(renderer,angleTextSurf);
								
								sprintf(numOfSegText, "%03d", para.numOfSeg);
								SDL_Surface *numOfSegTextSurf = TTF_RenderText_Solid(font,numOfSegText, colour);
								SDL_Texture *numOfSegTextTex = SDL_CreateTextureFromSurface(renderer,numOfSegTextSurf);
								
								sprintf(lengthText, "%03d", (int)para.length);
								SDL_Surface *lengthTextSurf = TTF_RenderText_Solid(font,lengthText, colour);
								SDL_Texture *lengthTextTex = SDL_CreateTextureFromSurface(renderer,lengthTextSurf);
								printf("length %f\n", para.length);
								
								
								SDL_RenderCopy(renderer, bgcredTextTex, NULL, &bgcrBox);
								SDL_RenderCopy(renderer, bgcgreenTextTex, NULL, &bgcgBox);
								SDL_RenderCopy(renderer, bgcblueTextTex, NULL, &bgcbBox);
								
								SDL_RenderCopy(renderer, lcredTextTex, NULL, &lcrBox);
								SDL_RenderCopy(renderer, lcgreenTextTex, NULL, &lcgBox);
								SDL_RenderCopy(renderer, lcblueTextTex, NULL, &lcbBox);
								SDL_RenderCopy(renderer, angleTextTex, NULL, &angleBox);
								SDL_RenderCopy(renderer, numOfSegTextTex, NULL, &numOfSegBox);
								SDL_RenderCopy(renderer, lengthTextTex, NULL, &lengthBox);
								
								
								SDL_RenderPresent(renderer);
								//SDL_FreeSurface(textSurf);
								SDL_RenderClear(renderer);

							
							//SDL_Surface *surfaceEncode = SDL_ConvertrSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);

							break;
						}
						default:
						{
						printf("press left click\n");
						}
					}
					break;
				}
			}
		}
	}
	
	SDL_DestroyTexture(UIlayoutTex);
	SDL_FreeSurface(UIlayout);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}

void colourOptions(int x, int y, RGBcolour *colour, int winHeight, int offset)
{
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset)&&(y<=offset+25))
	{
		if (colour->r> 0)
		{
			colour->r -=1;
		}

	}
	
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset)&&(y<=offset+25))
	{
		if (colour->r< 255)
		{
			colour->r +=1;
		}
	}
	
	
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset+25)&&(y<=offset+50))
	{
		if (colour->g> 0)
		{
			colour->g -=1;
		}

	}
	
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset+25)&&(y<=offset+50))
	{
		if (colour->g< 255)
		{
			colour->g +=1;
		}
	}
	
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset+50)&&(y<=offset+75))
	{
		if (colour->b> 0)
		{
			colour->b -=1;
		}

	}
	
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset+50)&&(y<=offset+75))
	{
		if (colour->b< 255)
		{
			colour->b +=1;
		}
	}
}




void field_change(Uint8 * field, SDL_Surface * textSurf, SDL_Texture *textTex, SDL_Renderer * renderer, SDL_Color colour, char * lineCr, int incre_type, TTF_Font *font)
{
	if (incre_type == -1)
	{
		field -=1;
	}
	else
	{
		field +=1;
	}
	
	sprintf(lineCr, "%03d", *field);
	textSurf = TTF_RenderText_Solid(font, lineCr, colour);
	textTex = SDL_CreateTextureFromSurface(renderer,textSurf);
}






void drawingOperation(SDL_Renderer * renderer, parameters para, turtle_parameters turtle, max_coordinates maxC, int winHeight,SDL_Surface * sshot, RGBcolour lineColour, int captSet, int autoScale)
{
	para.angle = 180-para.angle;
	turtle.angle = para.angle;
	turtle.length = para.length;
	int openCloseResult  = open_close_pattern(para.angle, para.numOfSeg);
	if (openCloseResult == 0)
	{
		printf("closed\n");
		turtle_draw(renderer, para, turtle, maxC, winHeight, sshot, lineColour, captSet, autoScale);
	}
	else
	{
		printf("open\n");
		turtle_draw(renderer, para, turtle, maxC, winHeight, sshot, lineColour, captSet, autoScale);
	}
}

void turtle_draw(SDL_Renderer * renderer, parameters para, turtle_parameters turtle, max_coordinates maxC, int winHeight, SDL_Surface * sshot, RGBcolour lineColour, int captSet, int autoScale)
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
	printf ("scale me%d", autoScale);
	turtle.angle = para.angle;
	
	transform_scale(maxC, &turtle, &para.length, winHeight, autoScale);

	for (int i = 1; i<=numOfCycles; i++)
	{
		turtle.length= para.length;
		for (int j = 1; j<= para.numOfSeg; j++)
		{
			turtle_move(renderer, &turtle, para.angle, para.length, sshot, lineColour);
		}
			
			if (captSet == 1)
			{
			char filepath[30];
			sprintf(filepath, "screen%03d.bmp", i);
			printf("\n%s\n", filepath);
			SDL_SaveBMP(sshot, filepath);
			}
			//---------------------------------------------------------------------------------------

	}
	if (captSet == 2)
	{
	char filepath[30];
	sprintf(filepath, "screen.bmp");
	printf("\n%s\n", filepath);
	SDL_SaveBMP(sshot, filepath);
	}
}


int max_cycles(float angle, float numOfSeg)
{
	printf("angle %f\n", numOfSeg);
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


/*
void pen_down(SDL_Renderer *renderer, int x0, int y0, int length, RGBcolour c)
{
	SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,255);
	for(int i=0; i<=length; i++)
	{

		SDL_RenderDrawPoint(renderer, i, 10 );
	}

}
*/


int open_close_pattern(int angle, int numOfSeg)
{
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

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, int angle, int length, SDL_Surface * sshot, RGBcolour lineColour)
{
	float Xdif, Ydif;
	float rad = PI/180;
	float X0, Y0;


	X0 = turtle->x;
	Y0 = turtle->y;
	//SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );

	Xdif = turtle->length*(cos(rad*(turtle->angle)));
	turtle->x += Xdif;
	Ydif = turtle->length*(sin(rad*(turtle->angle)));
	turtle->y += Ydif;
	//SDL_RenderDrawLine(renderer, (int)X0, (int)Y0, (int)turtle->x, (int)turtle->y);
	Iline(sshot, X0, Y0, turtle->x, turtle->y, lineColour);

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
	float X0, Y0;


	X0 = turtle->x;
	Y0 = turtle->y;
	//SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );

	Xdif = turtle->length*(cos(rad*(turtle->angle)));
	turtle->x += Xdif;
	Ydif = turtle->length*(sin(rad*(turtle->angle)));
	turtle->y += Ydif;
	
	max_coordinate_test(&turtle->x, &turtle->y, maxC);
	printf("\n%f\t%f\t%f\t%f\n", maxC->minX, maxC->minY, maxC->maxX, maxC->maxY);
	if (turtle->angle >= 360)
	{
		turtle->angle -=360;
	}
	turtle->angle += angle;
	turtle->length += length;
}

void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float * length, int maxResolution, int autoScale)
{
	printf("scmaxale %f\n", maxC.maxX);
	int moveDifX = (0+2) - (int)maxC.minX;
	int moveDifY = (0+2) - (int)maxC.minY;
	printf("tranform %d\t%d\n", moveDifX, moveDifY);
	//printf("tranform %d\n", moveDifY);
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};


	float minTransformX=0, minTransformY=0, maxTransformX=0, maxTransformY = 0;
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
	printf("X tranform %f\n", maxC.minY);
	printf("Y tranform %f\n", maxC.minX);
	printf("\nafter me    %f\t%f\t%f\t%f\n", maxC.minX, maxC.minY, maxC.maxX, maxC.maxY);

	printf("scmaxale %f\n", maxC.maxX);
	if (autoScale == 1)
	{
		scale *= (maxResolution-10)/maxC.maxX;
		maxC.maxX *=scale;
		maxC.maxY *=scale;
			printf("scale %f\n", scale);

		if (maxC.maxY > maxResolution)
		{
			scale *= (maxResolution-10)/maxC.maxY;
		}
	

		printf("scale %f\n", scale);

		moveDifX *= scale;

		moveDifY *= scale;
		(*length)*= scale;
	}
	turtle->x = moveDifX;
	turtle->y = moveDifY;
	printf("move X %f, move Y %f\n", turtle->x, turtle->y);
}
