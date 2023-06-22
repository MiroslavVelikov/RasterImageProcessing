#pragma once
#include "Image.h"
#include <vector>

class Session {
public:
	explicit Session(const std::vector<std::string>);
	~Session();

	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;

	//...
	void crop(size_t x1, size_t y1, size_t x2, size_t y2);

	void negative();

	void rotateLeft();
	void rotateRight();
	void flipTop();
	void flipLeft();

	void print() const;

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

private:
	size_t id;
	std::vector<std::string> imagesPaths;
	std::vector<Image*> images;

	static size_t currentID;
};