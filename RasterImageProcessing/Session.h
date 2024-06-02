#pragma once
#include "Image.h"
#include <vector>

class Session {
public:
	explicit Session(const std::vector<std::string>);
	~Session();

	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;

	size_t getID() const;

	void crop(size_t x1, size_t y1, size_t x2, size_t y2);

	void negative();

	void rotateLeft();
	void rotateRight();
	void flipTop();
	void flipLeft();

	void addImage(const std::string& imageName);

	void monochrome();
	void grayscale();

	void print();

	void addCommand(const std::string& command);
	
	void horizontalCollage(const std::vector<std::string>& images);
	void verticalCollage(const std::vector<std::string>& images);

	void save();

private:
	void setImages(const std::vector<std::string> args);
	Image* getImage(const std::string& path) const;

	template <typename T>
	void negativeImage(std::vector<std::vector<T>>& pixels);

	template <typename T>
	void flipImageLeft(std::vector<std::vector<T>>& pixels);

	template <typename T>
	void flipImageTop(std::vector<std::vector<T>>& pixels);

	template <typename T>
	void rotateImageLeft(std::vector<std::vector<T>>& pixels, size_t& width, size_t& height);

	template <typename T>
	void rotateImageRight(std::vector<std::vector<T>>& pixels, size_t& width, size_t& height);

	template <typename T>
	void cropImage(size_t x1, size_t y1, size_t x2, size_t y2, std::vector<std::vector<T>>& pixels, size_t& width, size_t& height);

	template <typename T>
	std::vector<std::vector<bool>> monochromeImage(std::vector<std::vector<T>>& pixels, size_t maxValue);

	std::vector<Image*> getImages(const std::vector<std::string>& names) const;

	template <typename T>
	void stickPixelsHorizontaly(std::vector<std::vector<T>>& pixels, const std::vector<Image*>& images) const;

	template <typename T>
	void stickPixelsVertically(std::vector<std::vector<T>>& pixels, const std::vector<Image*>& images) const;

	std::string createName(const std::vector<Image*> images, const std::string& ext) const;
	
	void executeCommands();

private:
	size_t id;
	std::vector<std::string> imagesPaths;
	std::vector<Image*> images;
	std::vector<std::string> commandsQueue;

	static size_t currentID;
};

std::vector<std::string> split(const std::string& input, const char& symbol);
std::string toLower(const std::string& value);