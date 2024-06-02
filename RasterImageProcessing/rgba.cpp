#include "rgba.h"

rgba::rgba() : rgba(0, 0, 0, 0) {}

rgba::rgba(unsigned short red, unsigned short green, unsigned short blue, unsigned short opacity) 
	: rgb(red, green, blue) {
	setOpacity(opacity);
}

void rgba::setOpacity(unsigned short value) {
	if (value > 100)
		value = 100;

	opacity = value;
}