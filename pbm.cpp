#include "pbm.h"
#include <string>
#include <ctime>
#include <chrono>

#pragma warning(disable: 4996)

PortableBitMap::PortableBitMap(const std::string& name, size_t width, size_t height, const std::vector<std::vector<bool>>& pixels)
	: Image<bool>(name, width, height, pixels) {}

void PortableBitMap::printInfo() const {
	std::cout << name << " - portable bitmap format\n";
}

std::string PortableBitMap::getInfo() const {
	std::string result = name + '\n' + std::to_string(width) + '\n' + std::to_string(height) + '\n';

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			result += std::to_string(pixels[j][i]) + ' ';
		}
		result += '\n';
	}
	return result;
}

PortableBitMap PortableBitMap::operator+(const PortableBitMap& rhs) {
	// Horizontal collage
	size_t newWidth = width + rhs.width;
	std::vector<std::vector<bool>> newPixels;

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
		PortableBitMap temp(*this);
		temp.enlargeHeight(rhs.height, BLACK_VALUE);
		newPixels = temp.pixels;
		newPixels.insert(newPixels.end(), rhs.pixels.begin(), rhs.pixels.end());

		return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, rhs.height, newPixels);
	}
	else if (height > rhs.height) {
		PortableBitMap temp(rhs);
		temp.enlargeHeight(height, BLACK_VALUE);
		newPixels = pixels;
		newPixels.insert(newPixels.end(), temp.pixels.begin(), temp.pixels.end());

		return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, height, newPixels);
	}

	newPixels = pixels;
	newPixels.insert(newPixels.end(), rhs.pixels.begin(), rhs.pixels.end());

	return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, newWidth, height, newPixels);
}

PortableBitMap PortableBitMap::operator^(const PortableBitMap& rhs) {
	// Vertical collage
	size_t newHeight = height + rhs.height;
	std::vector<std::vector<bool>> newPixels;

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
		PortableBitMap temp(*this);
		temp.enlargeWidth(rhs.width, BLACK_VALUE);
		newPixels = temp.pixels;
		
		for (size_t i = 0; i < temp.width; i++) {
			newPixels[i].insert(newPixels[i].end(), rhs.pixels[i].begin(), rhs.pixels[i].end());
		}

		return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, rhs.width, newHeight, newPixels);
	}
	else if (width > rhs.width) {
		PortableBitMap temp(rhs);
		temp.enlargeWidth(width, BLACK_VALUE);
		newPixels = pixels;

		for (size_t i = 0; i < temp.width; i++) {
			newPixels[i].insert(newPixels[i].end(), temp.pixels[i].begin(), temp.pixels[i].end());
		}

		return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, width, newHeight, newPixels);
	}

	newPixels = pixels;
	for (size_t i = 0; i < width; i++) {
		newPixels[i].insert(newPixels[i].end(), rhs.pixels[i].begin(), rhs.pixels[i].end());
	}

	return PortableBitMap(name + '_' + rhs.name + '_' + currentDateTime, width, newHeight, newPixels);
}