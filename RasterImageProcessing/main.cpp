#include <iostream>
#include "Editor.h"
#include <fstream>

// Make it work even if there is random comented text there

int main() {
	Editor::getInstance().run();
	return 0;
}