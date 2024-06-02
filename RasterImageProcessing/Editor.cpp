#include "Editor.h"

Editor::~Editor() {
	for (size_t i = 0; i < sessions.size(); i++) {
		delete sessions[i];
		sessions[i] = nullptr;
	}
}

Editor& Editor::getInstance() {
	static Editor editor;
	return editor;
}

void Editor::run() {
	std::cout << " -- Welcome --\n >> Enter command: ";
	std::string input, command;
	std::vector<std::string> args;
	std::getline(std::cin, input);

	Session* workingSession = nullptr;

	while (toLower(input) != "exit") {
		args = split(input, ' ');
		command = toLower(args[0]);

		if (command == "load") {
			args.erase(args.begin());
			Session* newSession = new Session(args);

			if (!newSession->getID()) {
				std::cout << "Could not load a session!\n";
				delete newSession;
			}
			else {
				sessions.push_back(newSession);
				workingSession = sessions[sessions.size() - 1]; // it can work better
			}
		}
		else if (command == "list") {
			std::string specific = toLower(args[1]);
			if (specific == "session" && workingSession) {
				workingSession->print();
			}
			else if (specific == "sessions" && !sessions.empty()) {
				for (size_t i = 0; i < sessions.size(); i++) {
					if (sessions[i] == workingSession)
						std::cout << "Current Session\n";
					sessions[i]->print();
				}
			}
			else {
				std::cout << " -- Invalid command!\n";
			}
		}
		else if (command == "switch") {
			size_t sessionId = std::stoi(args[1]);
			if (sessions.size() >= sessionId && sessionId != 0) {
				workingSession = sessions[sessionId - 1];
				std::cout << " -- Working now in " << sessionId << " session\n";
			}
		}
		else if (command == "close") {
			if (workingSession) {
				std::cout << "Session " << workingSession->getID() << " is closed\n";
				workingSession = nullptr;
			}
			else {
				std::cout << " -- Invalid command!\n";
			}
		}
		else if (command == "save") {
			if (args.size() < 2) {
				workingSession->save();
			}
			else if (args[1] == "all") {
				for (Session* session : sessions) {
					session->save();
				}
			}
			else {
				std::cout << " -- Invalid command!\n";
			}
		}
		else if (command == "add" && workingSession) {
			std::string image;
			if (args.size() > 2) {
				for (size_t i = 1; i < args.size(); i++) {
					image += args[i];
				}
			}
			else {
				image = args[1];
			}

			try {
				workingSession->addImage(image);
			}
			catch (const std::exception& e) {
				std::cout << e.what();
			}
		}
		else if (workingSession && (command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate" || command == "flip"
			|| command == "make" || command == "crop" || command == "undo" || command == "redo")) {
			workingSession->addCommand(input);
		}
		else if (command == "help") {
			printHelp();
		}
		else {
			std::cout << " -- Invalid command!\n   /If you do not know any commands write Help/\n";
		}

		std::cout << " >> Enter command: ";
		std::getline(std::cin, input);
	}
}

void Editor::printHelp() const {
	std::cout << "\n   +---------------------+Commands+---------------------+\n";
	std::cout << "   |----------------+Main menu commands+----------------|\n";
	std::cout << "   | Load <At least one image path>                     |\n";
	std::cout << "   | List Sessions                                      |\n";
	std::cout << "   | Switch <Session ID>                                |\n";
	std::cout << "   | Save All                                           |\n";
	std::cout << "   | Exit                                               |\n";
	std::cout << "   |----------------------------------------------------|\n";
	std::cout << "   |-----------------+Session commands+-----------------|\n";
	std::cout << "   | Add <Image path>                                   |\n";
	std::cout << "   | List Session                                       |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Grayscale                                          |\n";
	std::cout << "   | Monochrome                                         |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Negative                                           |\n";
	std::cout << "   | Rotate Left                                        |\n";
	std::cout << "   | Rotate Right                                       |\n";
	std::cout << "   | Flip Top                                           |\n";
	std::cout << "   | Flip Left                                          |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Crop <X1> <Y1> <X2> <Y2>                           |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Undo                                               |\n";
	std::cout << "   | Redo                                               |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Make Collage Horizontal/Vertical                   |\n";
	std::cout << "   |  <At least two images that are of the same format> |\n";
	std::cout << "   |                                                    |\n";
	std::cout << "   | Save                                               |\n";
	std::cout << "   | Close                                              |\n";
	std::cout << "   |----------------------------------------------------|\n";
	std::cout << "   +----------------------------------------------------+\n\n";
}