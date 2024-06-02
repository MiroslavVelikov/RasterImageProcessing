#include "ImageFactory.h"
#include "Session.h"
#include <fstream>
#include "pbm.h"
#include "ppm.h"
#include "pgm.h"
#include "rgb.h"
#include <ctime>
#include <chrono>

#pragma warning(disable: 4996)

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

size_t Session::getID() const {
	return id;
}

void Session::setImages(const std::vector<std::string> args) {
	if (!args.size())
		throw std::invalid_argument("There must be at least one image for processing!\n");

	for (size_t i = 0; i < args.size(); i++) {
		addImage(args[i]);
	}
}
// invalid_argument

Image* Session::getImage(const std::string& path) const {
	Image* image = nullptr;

	std::ifstream imageFile(path, std::ios::in | std::ios::binary);

	if (!imageFile.good())
		throw std::invalid_argument("Invalid image path!\n");

	std::string name = path.substr(path.find_last_of('/') + 1); // Dont know why can not do it in one line!!!! (:
	image = ImageFactory::getFactory().createImage(path.substr(path.size() - 3), name.substr(0, name.find('.')), imageFile);

	imageFile.close();

	return image;
}

Session::~Session() {
	for (size_t i = 0; i < images.size(); i++) {
		delete images[i];
		images[i] = nullptr;
	}
}

void Session::print() {
	if (commandsQueue.size())
		executeCommands();
	std::cout << "Session ID: " << id << '\n';
	if (!images.size())
		std::cout << "Session is empty.\n";
	for (size_t i = 0; i < images.size(); i++) {
		images[i]->printInfo();
		//images[i]->print();
		//std::cout << '\n';
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

void Session::addImage(const std::string& imageName) {
	if (commandsQueue.size())
		executeCommands();
	try {
		Image* image = getImage(imageName);
		images.push_back(image);
		imagesPaths.push_back(imageName);
	}
	catch (const std::invalid_argument& e) {
		throw e;
	}
}

void Session::addCommand(const std::string& command) {
	commandsQueue.push_back(command);
}

void Session::monochrome() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';
		std::string name = image->name, extention = "P1";
		size_t width = image->width, height = image->height, maxValue = image->maxValueColor();
		std::vector<std::vector<bool>> newPixels;

		if (type == 2 || type == 5) {
			std::vector<std::vector<size_t>>* ptr = (std::vector<std::vector<size_t>>*)image->getPixels();
			newPixels = monochromeImage<size_t>(*ptr, image->maxValueColor());
		}
		else if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			newPixels = monochromeImage<rgb>(*ptr, image->maxValueColor());
		}

		images.push_back(new PortableBitMap(name, extention, width, height, newPixels));
		imagesPaths.push_back("./images/" + name + ".pbm");
	}
}

template <typename T>
std::vector<std::vector<bool>> Session::monochromeImage(std::vector<std::vector<T>>& pixels, size_t maxValue) {
	std::vector<std::vector<bool>> newPixels(pixels.size(), std::vector<bool>(pixels[0].size()));

	for (size_t i = 0; i < pixels.size(); i++) {
		for (size_t j = 0; j < pixels[0].size(); j++) {
			newPixels[i][j] = pixels[i][j] < maxValue / 2 ? 1 : 0;
		}
	}

	return newPixels;
}

void Session::grayscale() {
	for (Image* image : images) {
		size_t type = image->getType()[1] - '0';

		std::string name = image->name, extention = "P2";
		size_t width = image->width, height = image->height, maxValue = image->maxValueColor();

		if (type == 3 || type == 6) {
			std::vector<std::vector<rgb>>* ptr = (std::vector<std::vector<rgb>>*)image->getPixels();
			std::vector<std::vector<size_t>> newPixels(image->width, std::vector<size_t>(image->height));

			for (size_t i = 0; i < image->width; i++) {
				for (size_t j = 0; j < image->height; j++) {
					rgb colors = (*ptr)[i][j];
					newPixels[i][j] = 0.3 * colors.getRed() + 0.59 * colors.getGreen() + 0.11 * colors.getBlue();
				}
			}

			images.push_back(new PortableGrayMap(name, extention, width, height, newPixels, maxValue));
		}

		imagesPaths.push_back("./images/" + name + ".pgm");
	}
}

void Session::horizontalCollage(const std::vector<std::string>& images) {
	if (images.size() < 2)
		throw std::invalid_argument("Too few arguments!\n");

	const std::vector<Image*> selected = getImages(images);

	if (selected.size() < 2)
		throw std::invalid_argument("You might have added wrong format or wrongly spelled images!\n");

	size_t width = 0, maxHeight = 0;
	for (Image* image : selected) {
		width += image->width;
		if (maxHeight < image->height)
			maxHeight = image->height;
	}

	std::string format = images[0].substr(images[0].size() - 3), name = createName(selected, format), path = "./Images/" + name;

	if (format == "pbm") {
		std::vector<std::vector<bool>> pixels(width, std::vector<bool>(maxHeight, 1));
		stickPixelsHorizontaly(pixels, selected);
		this->images.push_back(new PortableBitMap(name.substr(0, name.size() - 4), "P1", width, maxHeight, pixels));
	}
	else if (format == "pgm") {
		std::vector<std::vector<size_t>> pixels(width, std::vector<size_t>(maxHeight, 0));
		stickPixelsHorizontaly(pixels, selected);
		this->images.push_back(new PortableGrayMap(name.substr(0, name.size() - 4), "P2", width, maxHeight, pixels, 255));
	}
	else if (format == "ppm") {
		std::vector<std::vector<rgb>> pixels(width, std::vector<rgb>(maxHeight, rgb(0, 0, 0)));
		stickPixelsHorizontaly(pixels, selected);
		this->images.push_back(new PortablePixMap(name.substr(0, name.size() - 4), "P3", width, maxHeight, pixels, 255));
	}

	imagesPaths.push_back(path);
}

void Session::verticalCollage(const std::vector<std::string>& images) {
	/*if (images.size() < 2)
		throw std::invalid_argument("Too few arguments!\n");

	std::vector<Image*> indexes = getImages(images);

	if (indexes.size() < 2)
		throw std::invalid_argument("You might have added wrong format or wrongly spelled images!\n");*/

	if (images.size() < 2)
		throw std::invalid_argument("Too few arguments!\n");

	const std::vector<Image*> selected = getImages(images);

	if (selected.size() < 2)
		throw std::invalid_argument("You might have added wrong format or wrongly spelled images!\n");

	size_t height = 0, maxWidth = 0;
	for (Image* image : selected) {
		height += image->height;
		if (maxWidth < image->width)
			maxWidth = image->width;
	}

	std::string format = images[0].substr(images[0].size() - 3), name = createName(selected, format), path = "./Images/" + name;

	if (format == "pbm") {
		std::vector<std::vector<bool>> pixels(maxWidth, std::vector<bool>(height, 1));
		stickPixelsVertically(pixels, selected);
		this->images.push_back(new PortableBitMap(name.substr(0, name.size() - 4), "P1", maxWidth, height, pixels));
	}
	else if (format == "pgm") {
		std::vector<std::vector<size_t>> pixels(maxWidth, std::vector<size_t>(height, 0));
		stickPixelsVertically(pixels, selected);
		this->images.push_back(new PortableGrayMap(name.substr(0, name.size() - 4), "P2", maxWidth, height, pixels, 255));
	}
	else if (format == "ppm") {
		std::vector<std::vector<rgb>> pixels(maxWidth, std::vector<rgb>(height, rgb(0, 0, 0)));
		stickPixelsVertically(pixels, selected);
		this->images.push_back(new PortablePixMap(name.substr(0, name.size() - 4), "P2", maxWidth, height, pixels, 255));
	}

	imagesPaths.push_back(path);
}

std::vector<Image*> Session::getImages(const std::vector<std::string>& names) const {
	std::vector<Image*> result;
	std::string currNam, format = names[0].substr(names[0].size() - 3);

	for (std::string name : names) {
		currNam = name.substr(0, name.size() - 4);

		for (Image* image : images) {
			if (currNam == image->name && format == name.substr(name.size() - 3)) {
				result.push_back(image);
			}
		}
	}

	return result;
}

template <typename T>
void Session::stickPixelsHorizontaly(std::vector<std::vector<T>>& pixels, const std::vector<Image*>& images) const {
	size_t currentPixel = 0;
	for (Image* image : images) {
		std::vector<std::vector<T>>* currPixels = (std::vector<std::vector<T>>*)image->getPixels();
		for (size_t i = 0; i < image->width; i++, currentPixel++) {
			for (size_t j = 0; j < image->height; j++) {
				pixels[currentPixel][j] = (*currPixels)[i][j];
			}
		}
	}
}

template <typename T>
void Session::stickPixelsVertically(std::vector<std::vector<T>>& pixels, const std::vector<Image*>& images) const {
	size_t currentPixel = 0;
	for (Image* image : images) {
		std::vector<std::vector<T>>* currPixels = (std::vector<std::vector<T>>*)image->getPixels();
		for (size_t i = 0; i < image->height; i++, currentPixel++) {
			for (size_t j = 0; j < image->width; j++) {
				pixels[j][currentPixel] = (*currPixels)[j][i];
			}
		}
	}
}

std::string Session::createName(const std::vector<Image*> images, const std::string& ext) const {
	// This idea is taken from Stack Overflow
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	std::string currentDateTime = buf;
	//========================================

	std::string name = "";
	for (Image* image : images) {
		name += image->name + '_';
	}

	name += currentDateTime;
	name += '.' + ext;

	return name;
}

void Session::save() {
	if (commandsQueue.size())
		executeCommands();

	for (size_t i = 0; i < images.size(); i++) {
		std::ofstream output(imagesPaths[i], std::ios::out | std::ios::binary);
		if (!output.good())
			throw std::runtime_error("Failed to save current session!\n");
		output << images[i]->getInfo();
		output.close();
	}
}

void Session::executeCommands() {
	size_t undoCount = 0, redoCount = 0;
	std::string command;

	for (int i = commandsQueue.size() - 1; i >= 0; i--) {
		command = commandsQueue[i];
		if (command == "undo" && redoCount) {
			redoCount--;
		}
		else if (command == "undo") {
			undoCount++;
		}
		else if (command == "redo") {
			redoCount++;
		}
		else if (undoCount) {
			commandsQueue[i] = "";
			redoCount = 0;
		}
		else {
			redoCount = 0;
		}
	}

	std::vector<std::string> args;
	for (std::string input : commandsQueue) {
		args = split(input, ' ');
		command = toLower(args[0]);
		if (command == "grayscale") {
			grayscale();
		}
		else if (command == "monochrome") {
			monochrome();
		}
		else if (command == "negative") {
			negative();
		}
		else if (command == "rotate") {
			toLower(args[1]) == "right" ? rotateRight() : rotateLeft();
		}
		else if (command == "flip") {
			toLower(args[1]) == "top" ? flipTop() : flipLeft();
		}
		else if (command == "crop") {
			crop(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]));
		}
		else if (command == "make") {
			std::string type = toLower(args[2]);

			if (args.size() >= 3) {
				args.erase(args.begin(), args.begin() + 3);
			}

			try {
				type == "horizontal" ? horizontalCollage(args) : verticalCollage(args);
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what();
			}
		}
	}
	commandsQueue.clear();
}

std::vector<std::string> split(const std::string& input, const char& symbol) {
	size_t lines = 0;
	for (size_t i = 0; input[i]; i++) {
		if (input[i] == symbol)
			lines++;
	}

	if (!lines)
		return std::vector<std::string>{input};

	std::vector<std::string> arr(lines + 1);
	lines = 0;
	for (size_t i = 0; input[i]; i++) {
		if (input[i] == symbol)
			lines++;
		else
			arr[lines] += input[i];
	}

	return arr;
}

std::string toLower(const std::string& value) {
	std::string result = "";
	for (char symbol : value) {
		if (symbol >= 'A' && symbol <= 'Z')
			result += char(symbol + 32);
		else
			result += symbol;
	}

	return result;
}