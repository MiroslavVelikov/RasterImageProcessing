#pragma once
#include "Image.h"

class PortableGrayMap : public Image {
public:
	PortableGrayMap(const std::string& name, const std::string& extention ,size_t width, size_t height,
		const std::vector<std::vector<size_t>>& pixels, size_t maxValue);

	void printInfo() const override;
	std::string getInfo() const override;
	void print() const override;
	
	void* getPixels() override;
	size_t maxValueColor() const override { return maxValue; };

private:
	void setMaxValue(size_t value);
	void setPixels(const std::vector<std::vector<size_t>>& value);

private:
	static const bool BLACK_VALUE = 0;

	std::vector<std::vector<size_t>> pixels;
	size_t maxValue;
};

// PGMCreator
// ======================================================================

class PGMCreator : public ImageCreator {
public:
	PGMCreator();
	Image* createImage(const std::string& name, std::istream& in) const override;
};