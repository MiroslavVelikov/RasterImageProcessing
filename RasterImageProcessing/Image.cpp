#include "Image.h"
#include "ImageFactory.h"

Image::Image(const std::string& name, const std::string& extensionType, size_t width, size_t height) {//, const std::vector<std::vector<T>>& pixels) {
	try {
		this->name = name;
		this->extensionType = extensionType;
		setWidth(width);
		setHeight(height);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		clear();
	}
}

void Image::setWidth(size_t value) {
	if (value > MAX_SIZE)
		throw std::invalid_argument("Invalid image width!\n");

	width = value;
}
// invalid_argument

void Image::setHeight(size_t value) {
	if (value > MAX_SIZE)
		throw std::invalid_argument("Invalid image height!\n");

	height = value;
}

void Image::clear() {
	this->width = this->height = 0;
	this->name.clear(); this->extensionType.clear();
}

// ImageCreator
// ========================================================================

ImageCreator::ImageCreator(const std::string& key) {
	this->key = key;
	ImageFactory::getFactory().registerImageCreator(this);
}

const std::string& ImageCreator::getKey() const {
	return key;
}