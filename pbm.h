#pragma once
#include "Image.hpp"

class PortableBitMap : public Image<bool> {
public:
	PortableBitMap(const std::string& name, size_t width, size_t height, const std::vector<std::vector<bool>>& pixels);

	void printInfo() const override;
	std::string getInfo() const override;
	
	PortableBitMap operator+(const PortableBitMap& rhs); // Horizontal collage
	PortableBitMap operator^(const PortableBitMap& rhs); // Vertical collage

private:
	static const bool BLACK_VALUE = 1;
};