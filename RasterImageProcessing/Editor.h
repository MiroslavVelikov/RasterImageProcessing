#pragma once
#include "Session.h"
#include <vector>
#include <string>

class Editor {
private:
	Editor() = default;
	~Editor() = default;

public:
	Editor(const Editor&) = delete;
	Editor& operator=(const Editor&) = delete;

	static Editor& getInstance();
	void run();
	void printHelp() const;
	void executeCommand(const std::string& command);

private:
	std::vector<Session> sessions;
	std::vector<std::string> loadedImages;
};