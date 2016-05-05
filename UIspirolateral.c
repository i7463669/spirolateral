#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#define PI 3.14159265

/*Define Structures */
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


/* Function prototypes */

void max_coordinate_test(float *, float *,max_coordinates * maxC);
void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float *, int maxResolution, int);

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates *maxC, int, int, SDL_Surface * sshot, RGBcolour, int);
int max_cycles(float, float);
void turtle_draw(SDL_Renderer * renderer, parameters para, max_coordinates, int, SDL_Surface *, RGBcolour, int, int);
void Iline(SDL_Surface *img,int ,int ,int ,int , RGBcolour col);

void colourOptions(int, int, RGBcolour *colours , int, int);

int main (void)
{
	/*creating and assigning variables for the UI */
	char lcredText[4];
	char lcgreenText[4];
	char lcblueText[4];
	char bgcredText[4];
	char bgcgreenText[4];
	char bgcblueText[4];
	char angleText[4];
	char numOfSegText[4];
	char lengthText[4];
	/*Creating varialbes for the window */
	int winPosX = 100;
	int winPosY = 100;
	int winHeight = 800;
	int winWidth = winHeight + 400;

	int quit =0;

	/*setting the values for intial parameters of the program, the colours of the line and the background and the maximum coordintes */
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

	max_coordinates maxC;
	maxC.maxX = para.X;
	maxC.minX = para.X;
	maxC.maxY = para.Y;
	maxC.minY = para.Y;

	/*creating SDL_rect for the UI elements */

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

	SDL_Rect spiral;
	spiral.x = 0;
	spiral.y = 0;
	spiral.w = winHeight;
	spiral.h = winHeight;

	/* initialising TTF */
	TTF_Init();
	if( TTF_Init() != 0 )
	{

		perror("Error");
		/*returns -1 to show error */
		return -1;
	}
	/* initialising SDL */
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{

		perror("Error");
		/*returns -1 to show error */
		return -1;
	}
	int autoScale =1;

	/*seting the colour for the text in the text fields */
	SDL_Color colour = { 0, 0, 0 };
	TTF_Font *font = TTF_OpenFont("arial.ttf", 100);

	/*creates the window */
	SDL_Window *window = SDL_CreateWindow("Spirolateral", winPosX, winPosY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	/*creates renderer */
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	/*creates the texture for the Spiralateral */
	SDL_Texture * renderTexture = NULL;

	/*creates a surface for the background of the UI */
	SDL_Surface * UIbgSurf = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	/*fills is the backgroudn of the UI with the same colour as the UI image */
	SDL_FillRect(UIbgSurf, &UI, SDL_MapRGB(UIbgSurf->format, 102, 102, 102));
	/*creates a converts the surface to texture so that the UI background can be shown */
	SDL_Texture * UItexture = SDL_CreateTextureFromSurface(renderer, UIbgSurf);

	/* in the UI image */
	SDL_Surface * UIlayoutSurf = SDL_LoadBMP("UILayout.bmp");
	/*converts the UI image to a texture */
	SDL_Texture * UIlayoutTex = SDL_CreateTextureFromSurface(renderer, UIlayoutSurf);


	/*creates a surface from TTF and then converts it to texture */
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


	/*renders the UI textures using either boxes to position and scale the UI elements and prevent stretching */
	SDL_RenderCopy(renderer, UItexture, NULL, NULL);
	SDL_RenderCopy(renderer, UIlayoutTex, NULL, &UIbox);

	SDL_RenderCopy(renderer, lcredTextTex, NULL, &lcrBox);
	SDL_RenderCopy(renderer, lcgreenTextTex, NULL, &lcgBox);
	SDL_RenderCopy(renderer, lcblueTextTex, NULL, &lcbBox);

	SDL_RenderCopy(renderer, bgcredTextTex, NULL, &bgcrBox);
	SDL_RenderCopy(renderer, bgcgreenTextTex, NULL, &bgcgBox);
	SDL_RenderCopy(renderer, bgcblueTextTex, NULL, &bgcbBox);

	SDL_RenderCopy(renderer, angleTextTex, NULL, &angleBox);
	SDL_RenderCopy(renderer, numOfSegTextTex, NULL, &numOfSegBox);
	SDL_RenderCopy(renderer, lengthTextTex, NULL, &lengthBox);
	/*shows render */
	SDL_RenderPresent(renderer);
	/*creates a while to keep the window until the quit button is pressed */
	while (quit == 0)
	{
		/*create a SDL Event as incomingEvent */
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

					SDL_RenderClear(renderer);
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, winHeight, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
					SDL_FillRect(sshot, NULL, SDL_MapRGB(sshot->format, backColour.r, backColour.g, backColour.b));
					switch (incomingEvent.button.button)
					{
						/*checks to see if left mouse button is clicked */
						case SDL_BUTTON_LEFT:
						{
							int incre_type=-1;
							/*these variables store the X and Y values of the mouse when it is clicked */
							int x = incomingEvent.button.x;
							int y = incomingEvent.button.y;
							/*captSetp is the value which decides if the programs saves the pattern or not */
							int captSet = 0;
							/*this is the offect along the Y for creating the button */
							int lcOffset= 50;
							int bgcOffset = 150;
							/*this function tests to see which of the colour buttons are press and adjusts the colour of the line */
							colourOptions(x, y, &lineColour, winHeight, lcOffset);
							colourOptions(x, y, &backColour, winHeight, bgcOffset);

							/*checks if the mosue button is inside the area of the button and if it will change the following setting */
							/*angle */
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 250)&&(y<=275))
							{
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
							/*number of segments */
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 300)&&(y<=325))
							{
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
							/*length */
							if (x>=(winHeight+275)&&(x<= winHeight+300)&&(y >= 350)&&(y<=375))
							{
								if (para.length> 1)
								{
									para.length -= 1;
								}
							}

							if (x>=(winHeight+350)&&(x<= winHeight+375)&&(y >= 350)&&(y<=375))
							{
								if (para.length< 100)
								{
									para.length += 1;
								}

							}
							/*presets */
							if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 10;
								para.angle = 80;
							}
							else if (x>=(winHeight+100)&&(x<= winHeight+150)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 3;
								para.angle = 170;
							}

							else if (x>=(winHeight+150)&&(x<= winHeight+200)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 7;
								para.angle = 110;
							}
							else if (x>=(winHeight+200)&&(x<= winHeight+250)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 4;
								para.angle = 90;
							}
							else if (x>=(winHeight+250)&&(x<= winHeight+300)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 3;
								para.angle = 120;
							}
							else if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= 400)&&(y<=425))
							{
								para.numOfSeg = 5;
								para.angle = 40;
							}
							/*auto Scale */
							if (x>=(winHeight+50)&&(x<= winHeight+150) &&(y >= 350)&&(y<=375))
							{
								autoScale =1;
							}
							if (x>=(winHeight+150)&&(x<= winHeight+350) &&(y >= 350)&&(y<=375))
							{
								autoScale =0;
							}
							/*creates the spiralateral and saves image sequence */
							if (x>=(winHeight+250)&&(x<= winHeight+350) &&(y >= 500)&&(y<=550))
							{
								captSet = 1;
								turtle_draw(renderer, para,  maxC, winHeight, sshot,  lineColour, captSet, autoScale);
							}
							/*creates the spiralateral and saves image of the completed pattern */
							else if (x>=(winHeight+250)&&(x<= winHeight+350) &&(y >= 450)&&(y<=500))
							{
								captSet = 2;
								turtle_draw(renderer, para, maxC, winHeight, sshot,  lineColour, captSet, autoScale);
							}
							/*creates the spiralateral */
							else if(x>=(winHeight+50)&&(x<= winHeight+150) &&(y >= 450)&&(y<=500))
							{
								captSet = 0;
								turtle_draw(renderer, para, maxC, winHeight, sshot,  lineColour, captSet, autoScale);

							}
						}

						default:
						{
							/*converts the surface for the text to a texture */
							renderTexture = SDL_CreateTextureFromSurface(renderer, sshot);

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


							/*renders the text and the spiralateral */
							SDL_RenderCopy(renderer, UItexture, NULL, NULL);
							SDL_RenderCopy(renderer, UIlayoutTex, NULL, &UIbox);

							SDL_RenderCopy(renderer, lcredTextTex, NULL, &lcrBox);
							SDL_RenderCopy(renderer, lcgreenTextTex, NULL, &lcgBox);
							SDL_RenderCopy(renderer, lcblueTextTex, NULL, &lcbBox);

							SDL_RenderCopy(renderer, bgcredTextTex, NULL, &bgcrBox);
							SDL_RenderCopy(renderer, bgcgreenTextTex, NULL, &bgcgBox);
							SDL_RenderCopy(renderer, bgcblueTextTex, NULL, &bgcbBox);

							SDL_RenderCopy(renderer, angleTextTex, NULL, &angleBox);
							SDL_RenderCopy(renderer, numOfSegTextTex, NULL, &numOfSegBox);
							SDL_RenderCopy(renderer, lengthTextTex, NULL, &lengthBox);

							SDL_RenderCopy(renderer, renderTexture, NULL, &spiral);

							SDL_RenderPresent(renderer);

							SDL_RenderClear(renderer);
						}
					}
					break;
				}
			}
		}
	}

	/*destroys the textures when the closed button is clicked */
	SDL_DestroyTexture(UItexture);
	SDL_DestroyTexture(UIlayoutTex);

	SDL_DestroyTexture(lcredTextTex);
	SDL_DestroyTexture(lcgreenTextTex);
	SDL_DestroyTexture(lcblueTextTex);

	SDL_DestroyTexture(bgcredTextTex);
	SDL_DestroyTexture(bgcgreenTextTex);
	SDL_DestroyTexture(bgcblueTextTex);

	SDL_DestroyTexture(angleTextTex);
	SDL_DestroyTexture(numOfSegTextTex);
	SDL_DestroyTexture(lengthTextTex);

	/*frees the surfaces when the closed button is clicked */
	SDL_FreeSurface(UIbgSurf);
	SDL_FreeSurface(UIlayoutSurf);

	SDL_FreeSurface(lcredTextSurf);
	SDL_FreeSurface(lcgreenTextSurf);
	SDL_FreeSurface(lcblueTextSurf);

	SDL_FreeSurface(bgcredTextSurf);
	SDL_FreeSurface(bgcgreenTextSurf);
	SDL_FreeSurface(bgcblueTextSurf);

	SDL_FreeSurface(angleTextSurf);
	SDL_FreeSurface(numOfSegTextSurf);
	SDL_FreeSurface(lengthTextSurf);

	/*deletes renderer */
	SDL_DestroyRenderer(renderer);
	/*deletes window */
	SDL_DestroyWindow(window);
	/*Quits the program */
	SDL_Quit();
	return 0;
}

void colourOptions(int x, int y, RGBcolour *colour, int winHeight, int offset)
/* this functions checks if the button is clicked bying checkig the position of the mouse when clicked
 this prosition. if so it will adjust the variables */
{
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset)&&(y<=offset+25))
	{
		if (colour->r> 9)
		{
			colour->r -=10;
		}
	}
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset)&&(y<=offset+25))
	{
		if (colour->r< 246)
		{
			colour->r +=10;
		}
	}
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset+25)&&(y<=offset+50))
	{
		if (colour->g> 9)
		{
			colour->g -=10;
		}

	}
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset+25)&&(y<=offset+50))
	{
		if (colour->g< 246)
		{
			colour->g +=10;
		}
	}
	if (x>=(winHeight+50)&&(x<= winHeight+100)&&(y >= offset+50)&&(y<=offset+75))
	{
		if (colour->b> 9)
		{
			colour->b -=10;
		}
	}
	if (x>=(winHeight+300)&&(x<= winHeight+350)&&(y >= offset+50)&&(y<=offset+75))
	{
		if (colour->b< 246)
		{
			colour->b +=10;
		}
	}
}




void turtle_draw(SDL_Renderer * renderer, parameters para, max_coordinates maxC, int winHeight, SDL_Surface * sshot, RGBcolour lineColour, int captSet, int autoScale)
{
	/* this fuction has two fuctions. first itcalucaltes the maximum and mininum point of the pattern
	 then positions the pattern so that it is on screen. it also scales the pattern so that all of it
	 stays on the surface. this can be disabled by the user so that they can chose their own value
	 next the draws the spiralateral out using the new positionn and scale. */
	para.angle = 180-para.angle;
	/* sets teh turtle parameters to the users chosen values. */
	turtle_parameters turtle;
	turtle.x = para.X;
	turtle.y = para.Y;
	turtle.angle = para.angle;
	turtle.length = para.length;
	/* creates the string which the file will be saved under as */
	char filepath[30];
	int find =0;
	int draw =1;
	/* calculates the total number of cycles in the spirolateral */
	int numOfCycles = max_cycles(para.angle, para.numOfSeg);

	/* this section calcualtes the max and min coordinates and saves them to the maxC struct */
	for (int k = 1; k<= numOfCycles; k++)
	{
		turtle.length= para.length;
		for (int d=1; d <=para.numOfSeg; d++)
		{
			/* this find the max and min coordinates */
			turtle_move(renderer, &turtle, &maxC, para.angle, para.length, sshot, lineColour, find);
		}
	}
	/* resets the angle */
	turtle.angle = para.angle;
	/* moves teh spirolateral and then scales it if the not disabled by the user */
	transform_scale(maxC, &turtle, &para.length, winHeight, autoScale);
	/* this fucntion draws the spiralaterial by using the new starting pos and the new length */
	for (int i = 1; i<=numOfCycles; i++)
	{
		turtle.length= para.length;
		for (int j = 1; j<= para.numOfSeg; j++)
		{
			/* this draws the line for the spiralaterals */
			turtle_move(renderer, &turtle, &maxC, para.angle, para.length, sshot, lineColour, draw);
		}
			/* if the save image sequence of the spiralateral button was pressed */
			if (captSet == 1)
			{
			sprintf(filepath, "screen%03d.bmp", i);
			SDL_SaveBMP(sshot, filepath);
			}

	}
	/* if the save an image of the final pattern if save image button was pressed */
	if (captSet == 2)
	{
		sprintf(filepath, "screen.bmp");
		SDL_SaveBMP(sshot, filepath);
	}
}

int max_cycles(float angle, float numOfSeg)
/* finds the maximum number of the cycles for the chosen number of Segments ad angle */
{
	float outcome = 1;
	float i=0;
	while (outcome !=0)
	/* iterates throught the outcome until it reach outcome is whole */
	{
		i++;
		outcome = ((angle*numOfSeg)/(360/i));
		outcome = fmod(outcome, 1);
	}

	if (angle == 80 && ((int)numOfSeg % 2 ==1))
	{
		i *=2;
	}
	/* returns the number of the cycles */
	return i;
}

void turtle_move(SDL_Renderer * renderer, turtle_parameters * turtle, max_coordinates * maxC, int angle, int length, SDL_Surface * sshot, RGBcolour lineColour, int draw)
{
	/* this fuction either calculates the max and min coordinates or draws the spiralateral */
	//float Xdif, Ydif;
	float rad = PI/180;
	float X0, Y0;
	/*sets the orignal position */
	X0 = turtle->x;
	Y0 = turtle->y;
	turtle->x += turtle->length*(cos(rad*(turtle->angle)));
	//turtle->x += Xdif;
	turtle->y += turtle->length*(sin(rad*(turtle->angle)));
	//turtle->y += Ydif;
	/* if draw is one then it will draw the spirolateral */
	if (draw ==1)
	{
		Iline(sshot, X0, Y0, turtle->x, turtle->y, lineColour);
	}
	/* if draw  is 0 then it will find the max coordinates */
	else if (draw ==0)
	{
		max_coordinate_test(&turtle->x, &turtle->y, maxC);
	}
	/* keeps the agle with in the range of 0-360 */
	(turtle->angle)%=360;
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
/* this function saves the max ad min points for the x and y coordinates ii the max_coordinate struct*/
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

void transform_scale(struct max_coordinates maxC, struct turtle_parameters * turtle, float * length, int maxResolution, int autoScale)
{
	/* this function scales and positions the spiralateral to makes sure that it is not goig
	 off the surface when the auto scale option is ticked */

	/* finds the distnace which is needed to move the min coordinates to the to y=0 and x=0 */
	int moveDifX = (0+2) - (int)maxC.minX;
	int moveDifY = (0+2) - (int)maxC.minY;
	/* creates the transformation matrix */
	float matrixT[3][3] = {{1, 0, moveDifX}, {0, 1, moveDifY}, {0,0,1}};
	/* seets up the other [art of the traformation matrix by putting the max x and y and min x and y */
	float minXYvalue[3] = {maxC.minX, maxC.minY, 1};
	float maxXYvalue[3] = {maxC.maxX, maxC.maxY, 1};


	float maxTransformX=0, maxTransformY = 0;
	float scale = 1;
	/* transforms the points */

	for( int j =0; j<3; j++)
	{
		maxTransformX += (matrixT[0][j])*(maxXYvalue[j]);
		maxTransformY += (matrixT[1][j])*(maxXYvalue[j]);
	}
	/* assigns the final tranformation to the min and max coordinates  */

	maxC.maxX = maxTransformX;
	maxC.maxY = maxTransformY;

	if (autoScale == 1)
	{
		/* gets the scale factor wither relation to the max X adn the resolutioin alone the X */
		scale *= (maxResolution-10)/maxC.maxX;
		/* scales the max X so that its the same as the X resolution */
		maxC.maxX *=scale;
		maxC.maxY *=scale;
		/* if the max Y is greater than the resolution then it is reduces the scale  */
		if (maxC.maxY > maxResolution)
		{
			scale *= (maxResolution-10)/maxC.maxY;
		}
		/* applies the scale factor to the distance moved along the X and Y and the lenght of a segment */

		moveDifX *= scale;
		moveDifY *= scale;
		(*length)*= scale;
	}
	/* applies the transformation to the intial turtle position */
	turtle->x = moveDifX;
	turtle->y = moveDifY;
}
