#pragma once
#include <vector>
#include "Image.h"

class ImageFactory {
private:
	ImageFactory() = default;
	~ImageFactory() = default;

public:
	ImageFactory(const ImageFactory&) = delete;
	ImageFactory& operator=(const ImageFactory&) = delete;

	static ImageFactory& getFactory();
	void registerImageCreator(const ImageCreator* creator);
	Image* createImage(const std::string& key, const std::string& name, std::istream& in);

private:
	const ImageCreator* getCreator(const std::string& key) const;

private:
	std::vector<const ImageCreator*> creators;
};