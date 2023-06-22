#include "pgm.h"
#include <string>

#pragma warning(disable: 4996)

PortableGrayMap::PortableGrayMap(const std::string& name, const std::string& extention, size_t width, size_t height,
	const std::vector<std::vector<size_t>>& pixels, size_t maxValue)
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

void PortableGrayMap::setMaxValue(size_t value) {
	if (value > 255)
		throw std::invalid_argument("Max value out of bounds!\n");

	maxValue = value;
}

void PortableGrayMap::setPixels(const std::vector<std::vector<size_t>>& value) {
	if (width != value.size() || height != value[0].size())
		throw std::invalid_argument("Invalid image size!\n");

	pixels = value;
}

void PortableGrayMap::printInfo() const {
	std::cout << name << " - portable graymap format\n";
}

std::string PortableGrayMap::getInfo() const {
	std::string result = name + '\n' + std::to_string(width) + '\n' + std::to_string(height) + '\n';

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			result += std::to_string(pixels[j][i]) + ' ';
		}
		result += '\n';
	}
	return result;
}

void PortableGrayMap::print() const {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::cout << pixels[j][i] << ' ';
		}
		std::cout << '\n';
	}
}

// PGMCreator
// ==============================================

PGMCreator::PGMCreator() : ImageCreator("pgm") {}

Image* PGMCreator::createImage(const std::string& name, std::istream& in) const {
	std::string extention;
	size_t width, height, maxValue;

	in >> extention;
	in >> width >> height;
	in >> maxValue;

	size_t temp;
	std::vector<std::vector<size_t>> pixels(width, std::vector<size_t>(height));
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			in >> temp;
			if (temp > maxValue)
				temp = maxValue;
			pixels[j][i] = temp;
		}
	}

	return new PortableGrayMap(name, extention, width, height, pixels, maxValue);
}

static PGMCreator __;