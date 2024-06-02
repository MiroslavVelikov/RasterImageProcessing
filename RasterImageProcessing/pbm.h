#pragma once
#include "Image.h"

class PortableBitMap : public Image {
public:
	PortableBitMap(const std::string& name, const std::string& extensionType, size_t width, size_t height, const std::vector<std::vector<bool>>& pixels);

	void printInfo() const override;
	std::string getInfo() const override;
	void print() const override;

	void* getPixels() override;
	size_t maxValueColor() const override { return BLACK_VALUE; };

	//std::vector<std::vector<bool>>& getPixels() { return pixels; };

private:
	void setPixels(const std::vector<std::vector<bool>>& value);

private:
	static const bool BLACK_VALUE = 1;
	std::vector<std::vector<bool>> pixels;
};

// PBMCreator
// ======================================================================

class PBMCreator : public ImageCreator {
public:
	PBMCreator();
	Image* createImage(const std::string& name, std::istream& in) const override;
};