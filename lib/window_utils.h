
#include"/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "utils.h"
#include "color.h"
#include "vec.h"

int _random( int max );
void set_caption( char* msg, SDL_Window* screen );
SDL_Rect rectangle( int _x, int _y, int _w, int _h );
void setColor( SDL_Renderer* renderer, COLOR color );

void fill_rect(
	SDL_Renderer* renderer,
	int x,
	int y,
	int w,
	int h,
	COLOR clr
);
void draw_line(SDL_Renderer* rndr,
	line l,
	COLOR clr
);
void draw_point(SDL_Renderer* rndr, point pos, double radius, COLOR clr);
void draw_qudratic_bezier(SDL_Renderer* rndr, line l1, line l2, int res, COLOR clr);
