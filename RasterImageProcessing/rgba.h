#pragma once
#include "rgb.h"

struct rgba : public rgb {
public:
	rgba();
	rgba(unsigned short red, unsigned short green, unsigned short blue, unsigned short opacity);

	unsigned short getOpacity() const;

private:
	void setOpacity(unsigned short value);

private:
	unsigned short opacity;
};