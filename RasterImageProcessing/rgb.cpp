#include <string>
#include "rgb.h"

unsigned short rgb::MAX_VALUE = 255;

rgb::rgb() : rgb(0, 0, 0) {}

rgb::rgb(unsigned short red, unsigned short green, unsigned short blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void rgb::setRed(unsigned short value) {
	if (value > MAX_VALUE)
		value = MAX_VALUE;

	red = value;
}

void rgb::setGreen(unsigned short value) {
	if (value > MAX_VALUE)
		value = MAX_VALUE;

	green = value;
}

void rgb::setBlue(unsigned short value) {
	if (value > MAX_VALUE)
		value = MAX_VALUE;

	blue = value;
}

unsigned short rgb::getRed() const {
	return red;
}

unsigned short rgb::getGreen() const {
	return green;
}

unsigned short rgb::getBlue() const {
	return blue;
}

std::string rgb::toString() const {
	return std::to_string(red) + ' ' + std::to_string(green) + ' ' + std::to_string(blue);
}

bool operator<(const rgb& color, size_t value) {
	return (color.red + color.green + color.blue) / 3 < value;
}