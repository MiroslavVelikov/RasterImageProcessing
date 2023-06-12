#pragma once

struct rgb {
public:
	rgb(unsigned short red, unsigned short green, unsigned short blue);

	void setRed(unsigned short value);
	void setGreen(unsigned short value);
	void setBlue(unsigned short value);

	unsigned short getRed() const;
	unsigned short getGreen() const;
	unsigned short getBlue() const;

private:
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	static unsigned short MAX_VALUE;
};