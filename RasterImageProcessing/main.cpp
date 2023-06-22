#include <iostream>
#include <fstream>
#include "ImageFactory.h"
#include "Session.h"
#include "pbm.h"

// Make it work even if there is random comented text there

int main() {
	std::string img1, img2, img3, img4;
	img1 = "./images/J.pbm";
	img2 = "./images/J_OneLiner.pbm";
	img3 = "./images/FEEP.pgm";
	img4 = "./images/Colors.ppm";

	std::vector<std::string> vec{ img1 };// , img2, img3, img4 };

	Session session(vec);
	session.print();
	session.crop(2, 2, 16, 5);
	session.print();

	return 0;
}