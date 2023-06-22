#include "ImageFactory.h"

const ImageCreator* ImageFactory::getCreator(const std::string& key) const {
    for (size_t i = 0; i < creators.size(); i++) {
        if (creators[i]->getKey() == key)
            return creators[i];
    }

    return nullptr;
}

ImageFactory& ImageFactory::getFactory() {
    static ImageFactory factory;
    return factory;
}

void ImageFactory::registerImageCreator(const ImageCreator* creator) {
    creators.push_back(creator);
}

Image* ImageFactory::createImage(const std::string& key, const std::string& name, std::istream& in) {
    const ImageCreator* creator = this->getCreator(key);
    return creator->createImage(name, in);
}