#include "pgm.h"
#include <string>
#include <ctime>
#include <chrono>

#pragma warning(disable: 4996)

PortableGrayMap::PortableGrayMap(const std::string& name, size_t width, size_t height,
	const std::vector<std::vector<size_t>>& pixels, size_t maxValue)
	: Image<size_t>(name, width, height, pixels) {
	try {
		setMaxValue(maxValue);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		this->width = this->height = this->maxValue = 0;
		this->pixels.clear();
	}
}

void PortableGrayMap::setMaxValue(size_t value) {
	if (value > 255)
		throw std::invalid_argument("Max value out of bounds!\n");

	maxValue = value;
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

PortableGrayMap PortableGrayMap::operator+(const PortableGrayMap& rhs) {
	// Horizontal collage
	size_t newWidth = width + rhs.width;
	size_t newMaxValue = maxValue > rhs.maxValue ? maxValue : rhs.maxValue;
	std::vector<std::vector<size_t>> newPixels;

	// This idea is taken from Stack Overflow
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	std::string currentDateTime = buf;
	//========================================

	if (height < rhs.height) {
		PortableGrayMap temp(*this);
		temp.enlargeHeight(rhs.height, BLACK_VALUE);
		newPixels = temp.pixels;
		newPixels.insert(newPixels.end(), rhs.pixels.begin(), rhs.pixels.end());

		return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, rhs.height, newPixels, newMaxValue);
	}
	else if (height > rhs.height) {
		PortableGrayMap temp(rhs);
		temp.enlargeHeight(height, BLACK_VALUE);
		newPixels = pixels;
		newPixels.insert(newPixels.end(), temp.pixels.begin(), temp.pixels.end());

		return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, height, newPixels, newMaxValue);
	}

	newPixels = pixels;
	newPixels.insert(newPixels.end(), rhs.pixels.begin(), rhs.pixels.end());

	return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, height, newPixels, newMaxValue);
}

PortableGrayMap PortableGrayMap::operator^(const PortableGrayMap& rhs) {
	// Vertical collage
	size_t newHeight = height + rhs.height;
	std::vector<std::vector<size_t>> newPixels;
	size_t newMaxValue = maxValue > rhs.maxValue ? maxValue : rhs.maxValue;

	// This idea is taken from Stack Overflow
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	std::string currentDateTime = buf;
	//========================================

	if (width < rhs.width) {
		PortableGrayMap temp(*this);
		temp.enlargeWidth(rhs.width, BLACK_VALUE);
		newPixels = temp.pixels;

		for (size_t i = 0; i < temp.width; i++) {
			newPixels[i].insert(newPixels[i].end(), rhs.pixels[i].begin(), rhs.pixels[i].end());
		}

		return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, rhs.width, newHeight, newPixels, newMaxValue);
	}
	else if (width > rhs.width) {
		PortableGrayMap temp(rhs);
		temp.enlargeWidth(width, BLACK_VALUE);
		newPixels = pixels;

		for (size_t i = 0; i < temp.width; i++) {
			newPixels[i].insert(newPixels[i].end(), temp.pixels[i].begin(), temp.pixels[i].end());
		}

		return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, width, newHeight, newPixels, newMaxValue);
	}

	newPixels = pixels;
	for (size_t i = 0; i < width; i++) {
		newPixels[i].insert(newPixels[i].end(), rhs.pixels[i].begin(), rhs.pixels[i].end());
	}

	return PortableGrayMap(name + '_' + rhs.name + '_' + currentDateTime, width, newHeight, newPixels, newMaxValue);
}

void PortableGrayMap::monochrome() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (pixels[j][i])
				pixels[j][i] = maxValue;
		}
	}
}