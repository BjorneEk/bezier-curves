#pragma once

#include "utils.h"

typedef struct vec_2d {
	double x;
	double y;
	int valid;
} vec2D, point, vec_2D;

typedef struct line {
	vec2D p1;
	vec2D p2;
} line;


point nullpoint();
point new_point( double x, double y );

line new_line_(
	double x1,
	double y1,
	double x2,
	double y2
);
line new_line( vec2D p1, vec2D p2 );

double length( line l );

point add( point p1, point p2 );
void add_to( point * p1, point p2 );
void add_scalar( point * p, double x );

void sub( point * p1, point p2 );
void sub_( point * p, double x );

void mult( point * p, double x );
point mult_( point p, double x );
double dist(point p1, point p2);
double inclination( line l );

point point_at_dist( line l, double dist);
point point_at_scale(line l, double scale);

line scale( line l, double scale);

point intersect(line l1, line l2);
