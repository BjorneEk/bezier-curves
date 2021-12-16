// sdltest.c
//#ifdef _WIN32a
#include"/Library/Frameworks/SDL2.framework/Headers/SDL.h"   /* All SDL App's need this */
//#else
//#include <linux/time.h>
#define __timespec_defined 1
#define __timeval_defined 1
#define __itimerspec_defined 1
//#include "SDL2/SDL.h"
//#endif
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/color.h"
#include "lib/utils.h"
#include "lib/window_utils.h"

#define QUITKEY SDLK_ESCAPE
#define WIDTH 1024
#define HEIGHT 768

SDL_Window* screen = NULL;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect source, destination, dst;

COLOR bg_color;
int errorCount = 0;
int keypressed;
int rectCount = 0;

int x_pos = 30;
int y_pos = 30;

int speed = 3;

uint8_t FORWARDS  = 0;
uint8_t LEFT      = 1;
uint8_t BACKWARDS = 2;
uint8_t RIGHT     = 3;
uint8_t DIR = 2;

void log_error(char* msg) {
	printf("%s\n", msg);
	errorCount++;
}
void set_bg_color(COLOR color) {
	bg_color = color;
	fill_rect( renderer, 0, 0, WIDTH, HEIGHT, bg_color );
}
void clear(){
	fill_rect( renderer, 0, 0, WIDTH, HEIGHT, bg_color );
}
void show() {
	SDL_RenderPresent(renderer);
}
/* Initialize all setup, set screen mode, load images etc */
void init_setup() {
	srand((int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if (!screen) {
		log_error("init_setup failed to create window");
	}
	bg_color = color(200, 200, 200);
	set_caption("Example One", screen);
	set_bg_color(color(0, 255,0));
}

/* Cleans up after game over */
void finnish() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	//Quit SDL
	SDL_Quit();
	exit(0);
}

/* read a character */
char geta_char() {
	int result = -1;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
		{
			result = event.key.keysym.sym;
			break;
		}
	}
	return result;
}
void on_update() {
	if ( DIR == FORWARDS )  y_pos -= speed;
	if ( DIR == LEFT )      x_pos -= speed;
	if ( DIR == BACKWARDS ) y_pos += speed;
	if ( DIR == RIGHT )     x_pos += speed;

	COLOR clr = color(255, 0, 0);
	fill_rect(renderer, x_pos, y_pos, 50, 50, clr);
	draw_line(renderer, 0, 0, x_pos, y_pos, clr );
}
/* main game loop. Handles demo mode, high score and game play */
void event_loop() {
	int gameRunning = 1;
	while (gameRunning) {
		clear();
		on_update();
		show();
		while ( SDL_PollEvent( &event ) ) {
			switch ( event.type ) {
				case SDL_KEYDOWN:
					switch ( event.key.keysym.sym ) {
						case 'w' :
							DIR = FORWARDS;
							break;
						case 'a' :
							DIR = LEFT;
							break;
						case 's' :
							DIR = BACKWARDS;
							break;
						case 'd' :
							DIR = RIGHT;
							break;
						case 'r' :
							SDL_ShowSimpleMessageBox(1, "hej", "på dig", screen);
							break;
						case QUITKEY :
							gameRunning = 0;
							break;
					}
					break;
				case SDL_QUIT: { /* if mouse click to close window */
					gameRunning = 0;
					break;
				}
				//case SDL_KEYUP: {
				//	break;
				//}
			}
		}
	}
}

int main(int argc, char * args[]) {
	init_setup();
	event_loop();
	finnish();
	return 0;
}
