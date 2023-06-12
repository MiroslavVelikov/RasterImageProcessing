#pragma once
#include <vector>
#include <iostream> // cout
#include <stdexcept> // invalid_argument

template <typename T>
class Image {
public:
	Image(const std::string& name, size_t width, size_t height, const std::vector<std::vector<T>>& pixels);

	void negative();

	void rotateLeft();
	void rotateRight();
	void flipTop();
	void flipLeft();

	void crop(size_t x1, size_t y1, size_t x2, size_t y2);

	void print() const;

	virtual void printInfo() const = 0;
	virtual std::string getInfo() const = 0; //Must add extention

protected:
	void enlargeHeight(size_t newHeight, size_t blackValue);
	void enlargeWidth(size_t newWidth, size_t blackValue);

private:
	void setWidth(size_t value);
	void setHeight(size_t value);
	void setPixels(const std::vector<std::vector<T>>& value);

protected:
	std::string name;
	std::string extensionType; // FIX THIS
	size_t width;
	size_t height;
	std::vector<std::vector<T>> pixels;

private:
	static const unsigned short MAX_SIZE = UINT16_MAX;
};

#include "Image.tpp"
//==============================================================================================================================================