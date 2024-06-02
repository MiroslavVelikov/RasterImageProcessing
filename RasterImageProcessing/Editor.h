#pragma once
#include "Session.h"
#include <vector>
#include <string>

class Editor {
private:
	Editor() = default;
	~Editor();

public:
	Editor(const Editor&) = delete;
	Editor& operator=(const Editor&) = delete;

	static Editor& getInstance();
	void run();
	void printHelp() const;

private:
	std::vector<Session*> sessions;
	std::vector<std::string> loadedImages;
};