
#include <stdlib.h>
#include <stdio.h>

#include "color.h"
#include "utils.h"


COLOR _color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	COLOR color;
	color.red   = red;
	color.green = green;
	color.blue  = blue;
	color.alpha = alpha;
	return color;
}
COLOR color(uint8_t red, uint8_t green, uint8_t blue) {
	return _color(red, green, blue, 255);
}
uint8_t red(COLOR color) {
	return color.red;
}
uint8_t green(COLOR color) {
	return color.green;
}
uint8_t blue(COLOR color) {
	return color.blue;
}
uint8_t alpha(COLOR color) {
	return color.alpha;
}
double _alpha(COLOR color) {
	return 255.0/color.alpha;
}
uint8_t brightness(COLOR color) {
	return (uint8_t)((color.red + color.green + color.blue)/3);
}

char * debug(COLOR color) {
	char * msg = malloc(43*sizeof(char));
	snprintf(msg, 43, "red: %d, green: %d, blue: %d, alpha: %d",
			 color.red, color.green, color.blue, color.alpha);
	return msg;
}
