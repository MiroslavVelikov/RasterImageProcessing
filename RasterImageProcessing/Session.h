#pragma once
#include "Image.h"
#include <vector>

class Session {
public:
	explicit Session(const std::vector<std::string>);
	~Session();

	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;

	//...

	void negative();

	void rotateLeft();
	void rotateRight();
	void flipTop();
	void flipLeft();

	void print() const;

private:
	void setImages(const std::vector<std::string> args);
	Image* getImage(const std::string& path) const;

private:
	size_t id;
	std::vector<std::string> imagesPaths;
	std::vector<Image*> images;

	static size_t currentID;
};