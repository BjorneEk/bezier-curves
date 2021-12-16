
#include "window_utils.h"
#include "utils.h"
#include "color.h"
#include <stdlib.h>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "vec.h"

/* returns a number between 1 and max */
int _random(int max) {
	return (rand() % max) + 1;
}

/* Sets Window caption according to state - eg in debug mode or showing fps */
void set_caption(char* msg, SDL_Window* screen) {
	SDL_SetWindowTitle(screen, msg);
}

SDL_Rect rectangle( int _x, int _y, int _w, int _h ) {
	SDL_Rect rect;
	rect.h = _h;
	rect.w = _w;
	rect.y = _y;
	rect.x = _x;
	return rect;
}

void setColor( SDL_Renderer* renderer, COLOR color) {
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
}

void fill_rect( SDL_Renderer* renderer, int x, int y, int w, int h, COLOR clr ) {
	setColor(renderer, clr);
	SDL_Rect rect;
	rect = rectangle( x, y, w, h );
	SDL_RenderFillRect(renderer, &rect);
}
void set_pixel( SDL_Renderer* renderer, point p, COLOR clr ) {
	setColor(renderer, clr);
	SDL_RenderDrawPoint(renderer, (int)p.x, (int)p.y);
}
void line_low(SDL_Renderer* rndr, line l, COLOR clr) {
	double dx = l.p2.x - l.p1.x;
	double dy = l.p2.y - l.p1.y;
	double yi = 1;
	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}
	double D = (2 * dy) - dx;
	double y = l.p1.y;
	for (double x = l.p1.x; x <= l.p2.x; x++) {
		set_pixel(rndr, new_point(x, y), clr);
		if (D > 0) {
			y = y + yi;
			D = D + (2 * (dy - dx));
		} else
			D = D + 2 * dy;
	}
}
void line_high(SDL_Renderer* rndr, line l, COLOR clr) {
	double dx = l.p2.x - l.p1.x;
	double dy = l.p2.y - l.p1.y;
	double xi = 1;
	if (dy < 0) {
		xi = -1;
		dx = -dx;
	}
	double D = (2 * dx) - dy;
	double x = l.p1.x;
	for (double y = l.p1.y; y <= l.p2.y; y++) {
		set_pixel(rndr, new_point(x, y), clr);
		if (D > 0) {
			x = x + xi;
			D = D + (2 * (dx - dy));
		} else
			D = D + 2 * dx;
	}
}
void draw_line(SDL_Renderer* rndr, line l, COLOR clr){
	int x0 = l.p1.x;
	int y0 = l.p1.y;
	int x1 = l.p2.x;
	int y1 = l.p2.y;
	int dx =  abs(x1 - x0);
	int sx = ( x0 < x1 ) ? 1.0 : -1.0;
	int dy = -abs(y1 - y0);
	int sy = ( y0 < y1 ) ? 1.0 : -1.0;
	int err = dx + dy;  /* error value e_xy */
	while (!(x0 == x1 && y0 == y1)){  /* loop */
		set_pixel( rndr, new_point(x0, y0), clr );
		int e2 = 2 * err;
		if (e2 >= dy) {/* e_xy+e_x > 0 */
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {/* e_xy+e_y < 0 */
			err += dx;
			y0 += sy;
		}
	}
}/*
void draw_line( SDL_Renderer* rndr, line l, COLOR clr ) {
	if (abs((int)(l.p2.y - l.p1.y)) < abs((int)(l.p2.x - l.p1.x))) {
		if (l.p1.x > l.p2.x) line_low(rndr, new_line(l.p2, l.p1), clr);
		else line_low(rndr, l, clr);
	} else {
		if (l.p1.y > l.p2.y) line_high(rndr, new_line(l.p2, l.p1), clr);
		else line_high(rndr, l, clr);
	}
}*/
void draw_point(SDL_Renderer* rndr, point pos, double radius, COLOR clr) {
	for (size_t i = 0; i <= (int)(radius*2); i++) {
		for (size_t j = 0; j <= (int)(radius*2); j++) {
			int x = (i-radius) * (i-radius);
			int y = (j-radius) * (j-radius);
			if ((x + y) <= (int)(radius)){
				set_pixel(rndr, add(pos, new_point(i-radius,j-radius)), clr);
			}
		}
	}
}
COLOR getColor(int val){
	COLOR colors[33];
	colors[0] = _color(255,0,0,125);
	colors[1] = _color(255,0,0,255);
	colors[2] = _color(255,0,0,125);

	colors[3] = _color(255,128,0,125);
	colors[4] = _color(255,128,0,255);
	colors[5] = _color(255,128,0,125);

	colors[6] = _color(255,255,0,125);
	colors[7] = _color(255,255,0,255);
	colors[8] = _color(255,255,0,125);

	colors[9] = _color(128,255,0,125);
	colors[10] = _color(128,255,0,255);
	colors[11] = _color(128,255,0,125);

	colors[12] = _color(0,255,0,125);
	colors[13] = _color(0,255,0,255);
	colors[14] = _color(0,255,0,125);

	colors[15] = _color(0,255,128,125);
	colors[16] = _color(0,255,128,255);
	colors[17] = _color(0,255,128,125);

	colors[18] = _color(0,128,255,128);
	colors[19] = _color(0,128,255,255);
	colors[20] = _color(0,128,255,128);

	colors[21] = _color(0,0,255,125);
	colors[22] = _color(0,0,255,255);
	colors[23] = _color(0,0,255,125);

	colors[24] = _color(128,0,255,125);
	colors[25] = _color(128,0,255,255);
	colors[26] = _color(128,0,255,125);

	colors[27] = _color(255,0,255,125);
	colors[28] = _color(255,0,255,255);
	colors[29] = _color(255,0,255,125);

	colors[30] = _color(255,0,128,125);
	colors[31] = _color(255,0,128,255);
	colors[32] = _color(255,0,128,125);

	return colors[val % 33];
}
void draw_qudratic_bezier(SDL_Renderer* rndr, line l1, line l2, int res, COLOR clr) {
	point next;
	for (size_t i = 1; i < res+2; i++) {
		line ln1 = new_line(point_at_scale(l1, i/(double)(res+2)), point_at_scale(l2, i/(double)(res+2)));
		line ln2 = new_line(point_at_scale(l1, (i+1)/(double)(res+2)), point_at_scale(l2, (i+1)/(double)(res+2)));
		draw_line(rndr, ln1, getColor(i));
		set_pixel(rndr, intersect(ln1, ln2), clr);
	}
	line l1new = new_line(l1.p2, l1.p1);
	line l2new = new_line(l2.p2, l2.p1);
	for (size_t i = 1; i < res+2; i++) {
		line ln1 = new_line(point_at_scale(l1new, i/(double)(res+2)), point_at_scale(l2new, i/(double)(res+2)));
		line ln2 = new_line(point_at_scale(l1new, (i+1)/(double)(res+2)), point_at_scale(l2new, (i+1)/(double)(res+2)));
		draw_line(rndr, ln1, getColor(i));
		set_pixel(rndr, intersect(ln1, ln2), clr);
	}

}
