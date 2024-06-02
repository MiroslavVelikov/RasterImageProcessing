#include "ppm.h"
#include <string>

#pragma warning (disable: 4996)

const rgb PortablePixMap::BLACK_VALUE(0, 0, 0);

PortablePixMap::PortablePixMap(const std::string& name, const std::string& extention, size_t width, size_t height,
	const std::vector<std::vector<rgb>>& pixels, size_t maxValue)
	: Image(name, extention, width, height) {
	try {
		setPixels(pixels);
		setMaxValue(maxValue);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		Image::clear();
		this->maxValue = 0;
		this->pixels.clear();
	}
}

void PortablePixMap::setMaxValue(size_t value) {
	if (value > 255)
		throw std::invalid_argument("Max value out of bounds!\n");

	maxValue = value;
}

void PortablePixMap::setPixels(const std::vector<std::vector<rgb>>& value) {
	if (width != value.size() || height != value[0].size())
		throw std::invalid_argument("Invalid image size!\n");

	pixels = value;
}

void PortablePixMap::printInfo() const {
	std::cout << name << " - portable pixmap format\n";
}

std::string PortablePixMap::getInfo() const {
	std::string result = extensionType + '\n' + std::to_string(width) + '\n' + std::to_string(height) + '\n' + std::to_string(maxValue) + '\n';

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			result += pixels[j][i].toString() + ' ';
		}
		result += '\n';
	}
	return result;
}

void PortablePixMap::print() const {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::cout << pixels[j][i].toString() << ' ';
		}
		std::cout << '\n';
	}
}

void* PortablePixMap::getPixels() {
	return &pixels;
}


// PPMCreator
// ==============================================

PPMCreator::PPMCreator() : ImageCreator("ppm") {}

Image* PPMCreator::createImage(const std::string& name, std::istream& in) const {
	std::string extention;
	size_t width, height, maxValue;

	in >> extention;
	in >> width >> height;
	in >> maxValue;

	size_t red, green, blue;
	std::vector<std::vector<rgb>> pixels(width, std::vector<rgb>(height));
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			in >> red >> green >> blue;
			if (red > maxValue)
				red = maxValue;
			if (green > maxValue)
				green = maxValue;
			if (blue > maxValue)
				blue = maxValue;

			pixels[j][i] = rgb(red, green, blue);
		}
	}
	
	return new PortablePixMap(name, extention, width, height, pixels, maxValue);
}

static PPMCreator __;