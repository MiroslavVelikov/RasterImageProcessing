#pragma once
#include <string>

struct rgb {
public:
	friend bool operator<(const rgb& color, size_t value);

public:
	rgb();
	rgb(unsigned short red, unsigned short green, unsigned short blue);

	std::string toString() const;

	unsigned short getRed() const;
	unsigned short getGreen() const;
	unsigned short getBlue() const;

private:
	void setRed(unsigned short value);
	void setGreen(unsigned short value);
	void setBlue(unsigned short value);

private:
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	static unsigned short MAX_VALUE;
};