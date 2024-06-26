#pragma once
#include <vector>
#include <iostream> // cout
#include <stdexcept> // invalid_argument

class Session;

class Image {
private:
	friend Session;

public:
	Image(const std::string& name, const std::string& extensionType, size_t width, size_t height);

	virtual void print() const = 0;

	virtual void printInfo() const = 0;
	virtual std::string getInfo() const = 0;

	const std::string& getType() const { return extensionType; };

	virtual void* getPixels() = 0;
	virtual size_t maxValueColor() const = 0;

	size_t getWidth() const;
	size_t getHeight() const;

protected:
	virtual void clear();

private:
	void setWidth(size_t value);
	void setHeight(size_t value);

protected:
	std::string name;
	std::string extensionType;
	size_t width;
	size_t height;

private:
	static const unsigned short MAX_SIZE = UINT16_MAX;
};

// ImageCreator
// ========================================================================

class ImageCreator {
private:
	std::string key; // "image"

public:
	explicit ImageCreator(const std::string& key);
	virtual ~ImageCreator() = default;
	ImageCreator(const ImageCreator&) = delete;
	ImageCreator& operator=(const ImageCreator&) = delete;

	const std::string& getKey() const;
	virtual Image* createImage(const std::string& name, std::istream& in) const = 0;
};