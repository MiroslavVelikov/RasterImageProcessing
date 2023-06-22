#include "ImageFactory.h"
#include "Session.h"
#include <fstream>
#include "pbm.h"

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
		//images[i]->print();
		//std::cout << '\n';
	}
}

void Session::negative() {
	//if(!)
}

void rotateLeft();
void rotateRight();
void flipTop();
void flipLeft();

template <typename T>
inline void negativeImage(std::vector<T>& pixels) {
	flipImageTop(pixels);
	flipImageLeft(pixels);
}

template <typename T>
inline void flipImageLeft(std::vector<T>& pixels) {
	size_t width = pixels.size();
	for (size_t i = 0; i < width / 2; i++) {
		std::swap(pixels[i], pixels[width - i - 1]);
	}
}

template <typename T>
void flipImageTop(std::vector<T>& pixels) {
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
void rotateImageLeft(std::vector<T>& pixels, size_t& width, size_t& height) {
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
void rotateImageRight(std::vector<T>& pixels, size_t& width, size_t& height) {
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
