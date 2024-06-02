#pragma once
#include "Image.h"
#include "rgb.h"

class PortablePixMap : public Image {
public:
	PortablePixMap(const std::string& name, const std::string& extention, size_t width, size_t height,
		const std::vector<std::vector<rgb>>& pixels, size_t maxValue);

	void printInfo() const override;
	std::string getInfo() const override;
	void print() const override;

	void* getPixels() override;
	size_t maxValueColor() const override { return maxValue; };

private:
	void setMaxValue(size_t value);
	void setPixels(const std::vector<std::vector<rgb>>& value);

private:
	static const rgb BLACK_VALUE;

	std::vector<std::vector<rgb>> pixels;
	size_t maxValue;
};

// PPMCreator
// ======================================================================

class PPMCreator : public ImageCreator {
public:
	PPMCreator();
	Image* createImage(const std::string& name, std::istream& in) const override;
};