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
#include "lib/vec.h"

#define QUITKEY SDLK_ESCAPE
#define WIDTH 2000
#define HEIGHT 1200

SDL_Window* screen = NULL;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect source, destination, dst;

COLOR bg_color;
int errorCount = 0;
int keypressed;
int rectCount = 0;

point p1_1;
point p1_2;

point p2_1;
point p2_2;

COLOR colors[10];
line lines[10];

int mouse = 0;
int active = 0;
double handlesize = 17.0;

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

void generate_line(){
	line l1 = new_line(p1_1, p1_2);
	line l2 = new_line(p1_2, p2_2);
	for (size_t i = 1; i <= 10; i++) {
		lines[i-1] = new_line(point_at_scale(l1, i/10.0), point_at_scale(l2, i/10.0));
	}
}
void set_active(point p) {
	if (handlesize >= dist(p1_1, p))      active = 1;
	else if (handlesize >= dist(p1_2, p)) active = 2;
	else if (handlesize >= dist(p2_1, p)) active = 3;
	else if (handlesize >= dist(p2_2, p)) active = 4;
	else active = 0;
}

void move(point p) {
	switch(active) {
		case 1: p1_1 = p; break;
		case 2: p1_2 = p; break;
		case 3: p2_1 = p; break;
		case 4: p2_2 = p; break;
	}
}
/* Cleans up after game over */
void finnish() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	//Quit SDL
	SDL_Quit();
	exit(0);
}
void on_update() {
	COLOR clr = color(255, 255, 255);
	draw_line(renderer, new_line(p1_1, p1_2), clr );
	draw_line(renderer, new_line(p2_1, p2_2), clr );
	draw_point(renderer, p1_1, handlesize, clr );
	draw_point(renderer, p1_2, handlesize, clr );
	draw_point(renderer, p2_1, handlesize, clr );
	draw_point(renderer, p2_2, handlesize, clr );
	/*for (size_t i = 0; i < 10; i++) {
		draw_line(renderer, lines[i], colors[i]);
	}*/
	draw_qudratic_bezier(renderer, new_line(p1_1, p1_2), new_line(p2_1, p2_2), 99, color(255,0,0));
}
void init_setup() {
	srand((int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if (!screen) {
		log_error("init_setup failed to create window");
	}
	bg_color = color(0, 0, 0);
	set_caption("Example One", screen);
	set_bg_color(color(0, 0,0));
	p1_1 = new_point(50.0, 300.0);
	p1_2 = new_point(500.0, 70.0);
	p2_1 = new_point(500.0, 70.0);
	p2_2 = new_point(WIDTH-50, 300.0);

	

	generate_line();
	clear();
	on_update();
	show();
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
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							if (!mouse) set_active(new_point(event.motion.x, event.motion.y));
							mouse = 1;
							break;
						case SDL_BUTTON_RIGHT:
						default: break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							mouse = 0;
							active = 0;
							break;
						case SDL_BUTTON_RIGHT: break;
						default: break;
					}
					break;
				case SDL_MOUSEMOTION:
					if(mouse){
						move(new_point(event.motion.x, event.motion.y));
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
