#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vec.h"
#include "utils.h"

point new_point( double x, double y ) {
	point p;
	p.x = x;
	p.y = y;
	p.valid = 0;
	return p;
}
point nullpoint() {
	point p;
	p.x = 0;
	p.y = 0;
	p.valid = -1;
	return p;
}
line new_line_( double x1, double y1, double x2, double y2 ) {
	point p1;
	p1.x = x1;
	p1.y = y1;
	point p2;
	p2.x = x2;
	p2.y = y2;
	return new_line(p1, p2);
}
line new_line( vec2D p1, vec2D p2 ) {
	line l;
	l.p1 = p1;
	l.p2 = p2;
	return l;
}
double length_( point p1, point p2 ) {
	return sqrt(pow((p2.y - p1.y),2) + pow((p2.x - p1.x),2));
}
double length( line l ) {
	return length_(l.p1, l.p2);
}

point add( point p1, point p2 ) {
	return new_point(p1.x + p2.x, p1.y + p2.y);
}
void add_to( point * p1, point p2 ) {
	p1->x += p2.x;
	p1->y += p2.y;
}
void add_scalar( point * p, double x ) {
	p->x += x;
	p->y += x;
}

void sub( point * p1, point p2 ) {
	p1->x -= p2.x;
	p1->y -= p2.y;
}
void sub_( point * p, double x ) {
	p->x -= x;
	p->y -= x;
}
double dist(point p1, point p2) {
	return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}
void mult( point * p, double x ) {
	p->x *= x;
	p->y *= x;
}
point mult_( point p, double x ) {
	return new_point(p.x * x, p.y * x);
}
double inclination( line l ) {
	return (l.p2.y - l.p1.y) / (l.p2.x - l.p1.x);
}
point point_at_scale(line l, double scale) {
	point org = new_point(l.p2.x - l.p1.x, l.p2.y - l.p1.y);
	mult(&org , scale);
	return new_point(org.x + l.p1.x, org.y + l.p1.y);
}
point point_at_dist( line l, double dist) {
	double scale = dist / length(l);
	return point_at_scale(l, scale);
}
line scale( line l, double scale) {
	return new_line(l.p1, point_at_scale(l, scale));
}
point intersect(line l1, line l2) {
	if (inclination(l1) == inclination(l2)) return nullpoint();
	double m1 = l1.p1.y - (inclination(l1) * l1.p1.x);
	double m2 = l2.p1.y - (inclination(l2) * l2.p1.x);
	double x = (m1 - m2) / (inclination(l2) - inclination(l1));
	double y = (inclination(l1)*x) + m1;
	return new_point( x, y );
}
