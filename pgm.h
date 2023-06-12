#pragma once
#include "Image.hpp"

class PortableGrayMap : public Image<size_t> {
public:
	PortableGrayMap(const std::string& name, size_t width, size_t height, const std::vector<std::vector<size_t>>& pixels, size_t maxValue);

	void printInfo() const override;
	std::string getInfo() const override;

	PortableGrayMap operator+(const PortableGrayMap& rhs); // Horizontal collage
	PortableGrayMap operator^(const PortableGrayMap& rhs); // Vertical collage

	void monochrome();

private:
	void setMaxValue(size_t value);
	//MUST CHECK IF THERE IS BIGGER NUM THAN MAX VALUE
private:
	size_t maxValue;
	static const bool BLACK_VALUE = 0;
};