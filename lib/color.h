#pragma once

#include "utils.h"

typedef struct COLOR {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} COLOR;

COLOR _color(
	uint8_t red,
	uint8_t green,
	uint8_t blue,
	uint8_t alpha
);
COLOR color(
	uint8_t red,
	uint8_t green,
	uint8_t blue
);

uint8_t red(   COLOR color );
uint8_t green( COLOR color );
uint8_t blue(  COLOR color );
uint8_t alpha( COLOR color );
double _alpha( COLOR color );

uint8_t brightness( COLOR color );
char * debug( COLOR color );
