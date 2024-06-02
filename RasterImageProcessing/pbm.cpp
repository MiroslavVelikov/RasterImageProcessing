#include "pbm.h"
#include <string>

PortableBitMap::PortableBitMap(const std::string& name, const std::string& extention, size_t width, size_t height, const std::vector<std::vector<bool>>& pixels)
	: Image(name, extention, width, height) {
	try {
		setPixels(pixels);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		this->pixels.clear();
		Image::clear();
	}
}

void PortableBitMap::printInfo() const {
	std::cout << name << " - portable bitmap format\n";
}

std::string PortableBitMap::getInfo() const {
	std::string result = extensionType + '\n' + std::to_string(width) + '\n' + std::to_string(height) + '\n';

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			result += std::to_string(pixels[j][i]) + ' ';
		}
		result += '\n';
	}
	return result;
}

void PortableBitMap::setPixels(const std::vector<std::vector<bool>>& value) {
	if (width != value.size() || height != value[0].size())
		throw std::invalid_argument("Invalid image size!\n");

	pixels = value;
}

void PortableBitMap::print() const {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			std::cout << pixels[j][i] << ' ';
		}
		std::cout << '\n';
	}
}

void* PortableBitMap::getPixels() {
	return &pixels;
}

// PMBCreator
// ==============================================================

PBMCreator::PBMCreator() : ImageCreator("pbm") {}

Image* PBMCreator::createImage(const std::string& name, std::istream& in) const {
	std::string extention;
	size_t width, height;

	in >> extention;
	in >> width >> height;
	
	char temp;
	std::vector<std::vector<bool>> pixels(width, std::vector<bool>(height));
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			in >> temp;
			pixels[j][i] = (temp - '0');
		}
	}

	return new PortableBitMap(name, extention, width, height, pixels);
}

static PBMCreator __;