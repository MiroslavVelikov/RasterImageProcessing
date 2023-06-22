#include <iostream>
#include <fstream>
#include "ImageFactory.h"
#include "Session.h"
#include "pbm.h"

// Make it work even if there is random comented text there

int main() {
	/*std::string img1, img2;
	img1 = "./images/J.pbm";
	img2 = "./images/J_OneLiner.pbm";
	
	std::vector<std::string> vec{ img1, img2 };

	Session session(vec);
	session.print();*/
	
	std::ifstream imageStream("./images/J.pbm");
	Image* img = ImageFactory::getFactory().createImage("pbm", "J", imageStream);
	img->print();
	
	PortableBitMap* pbm = dynamic_cast<PortableBitMap*>(img);
	
	delete img;
	/*std::string text = "Miro.jpg";
	std::cout << text.substr(text.size() - 3);
	*/
	//std::string input, name;
	//std::cin >> input >> name;
	//std::ifstream imageStream("./images/J.pbm");

	//if (!imageStream.is_open()) {
	//    std::cout << "Error!" << std::endl;
	//    return -1;
	//}

	//Image* image = ImageFactory::getFactory().createImage(input, name, imageStream);//std::cin);
	//image->print();
	//delete image;
	//image = nullptr;
	//return 0;
}