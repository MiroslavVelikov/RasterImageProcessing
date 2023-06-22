#include "ImageFactory.h"
#include "Session.h"
#include <fstream>
#include "pbm.h"
#include "rgb.h"

size_t Session::currentID = 1;

Session::Session(const std::vector<std::string> images) {
	try {
		id = currentID;
		setImages(images);
		std::cout << "Session with ID : " << currentID++ << " started\n";
	}
	catch (const std::invalid_argument& e) {
		id = 0;
		this->images.clear();
		imagesPaths.clear();
		std::cout << e.what();
	}
}

void Session::setImages(const std::vector<std::string> args) {
	if (!args.size())
		throw std::invalid_argument("There must be atleast one image for processing!\n");

	for (size_t i = 0; i < args.size(); i++) {
		try {
			Image* image = getImage(args[i]);
			images.push_back(image);
			imagesPaths.push_back(args[i]);
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what();
		}
	}
}
// invalid_argument

Image* Session::getImage(const std::string& path) const {
	Image* image = nullptr;

	std::ifstream imageFile(path);

	if (!imageFile.good())
		throw std::invalid_argument("Invalid image path!\n");

	std::string name = path.substr(path.find_last_of('/') + 1); // Dont know why can not do it in one line!!!! (:
	image = ImageFactory::getFactory().createImage(path.substr(path.size() - 3), name.substr(0, name.find('.')), imageFile);

	std::ifstream imageStream("./images/J.pbm");
	Image* img = ImageFactory::getFactory().createImage("pbm", "J", imageStream);

	imageFile.close();

	return image;
}

Session::~Session() {
	for (size_t i = 0; i < images.size(); i++) {
		delete images[i];
		images[i] = nullptr;
	}
}

void Session::print() const {
	std::cout << "Session ID: " << id << '\n';
	for (size_t i = 0; i < images.size(); i++) {
		images[i]->printInfo();
		images[i]->print();
		std::cout << '\n';
	}
}

void Session::negative() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			negativeImage<bool>(*ptr);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			negativeImage<size_t>(*ptr);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			negativeImage<rgb>(*ptr);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

void Session::rotateLeft() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			rotateImageLeft<bool>(*ptr, image->width, image->height);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			rotateImageLeft<size_t>(*ptr, image->width, image->height);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			rotateImageLeft<rgb>(*ptr, image->width, image->height);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

void Session::rotateRight() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			rotateImageRight<bool>(*ptr, image->width, image->height);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			rotateImageRight<size_t>(*ptr, image->width, image->height);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			rotateImageRight<rgb>(*ptr, image->width, image->height);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

void Session::flipTop() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			flipImageTop<bool>(*ptr);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			flipImageTop<size_t>(*ptr);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			flipImageTop<rgb>(*ptr);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

void Session::flipLeft() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			flipImageLeft<bool>(*ptr);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			flipImageLeft<size_t>(*ptr);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			flipImageLeft<rgb>(*ptr);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

template <typename T>
inline void Session::negativeImage(std::vector<std::vector<T>>& pixels) {
	flipImageTop<T>(pixels);
	flipImageLeft<T>(pixels);
}

template <typename T>
inline void Session::flipImageLeft(std::vector<std::vector<T>>& pixels) {
	size_t width = pixels.size();
	for (size_t i = 0; i < width / 2; i++) {
		std::vector<T> temp = pixels[i];
		pixels[i] = pixels[width - i - 1];
		pixels[width - i - 1] = temp;
		//std::swap(pixels[i], pixels[width - i - 1]);
	}
}

template <typename T>
inline void Session::flipImageTop(std::vector<std::vector<T>>& pixels) {
	size_t width = pixels.size();
	size_t height = pixels[0].size();
	for (size_t i = 0; i < height / 2; i++) {
		for (size_t j = 0; j < width; j++) {
			T temp = pixels[j][i];
			pixels[j][i] = pixels[j][height - i - 1];
			pixels[j][height - i - 1] = temp;
			//std::swap(pixels[j][i], pixels[j][height - i - 1]);
		}
	}
}

template <typename T>
inline void Session::rotateImageLeft(std::vector<std::vector<T>>& pixels, size_t& width, size_t& height) {
	std::vector<std::vector<T>> rotated(height, std::vector<T>(width));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			rotated[i][width - j - 1] = pixels[j][i];
		}
	}

	pixels = rotated;
	width = height;
	height = pixels[0].size();
}

template <typename T>
inline void Session::rotateImageRight(std::vector<std::vector<T>>& pixels, size_t& width, size_t& height) {
	std::vector<std::vector<T>> rotated(height, std::vector<T>(width));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			rotated[height - i - 1][j] = pixels[j][i];
		}
	}

	pixels = rotated;
	width = height;
	height = pixels[0].size();
}

void Session::crop(size_t x1, size_t y1, size_t x2, size_t y2) {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		if (type == 1 || type == 4) {
			std::vector<std::vector<bool>>* ptr = (std::vector<std::vector<bool>>*)image->getPixels();
			cropImage<bool>(x1, y1, x2, y2, *ptr, image->width, image->height);
		}
		else if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			cropImage<size_t>(x1, y1, x2, y2, *ptr, image->width, image->height);
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			cropImage<rgb>(x1, y1, x2, y2, *ptr, image->width, image->height);
		}
		else {
			throw std::invalid_argument("Invalid type of image!\n");
		}
	}
}

template <typename T>
inline void Session::cropImage(size_t x1, size_t y1, size_t x2, size_t y2, std::vector<std::vector<T>>& pixels, size_t& width, size_t& height) {
	if (x1 >= x2 || x1 >= width || y1 >= y2 || y1 >= height) {
		height = width = 0;
		pixels.clear();
		return;
	}

	if (x2 >= width)
		x2 = width - 1;
	if (y2 >= height)
		y2 = height - 1;

	std::vector<std::vector<T>> croped(x2 - x1 + 1, std::vector<T>(y2 - y1 + 1));

	for (size_t i = y1; i <= y2; i++) {
		for (size_t j = x1; j <= x2; j++) {
			croped[j - y1][i - x1] = pixels[j][i];
		}
	}

	pixels = croped;
	width = pixels.size();
	height = pixels[0].size();
}