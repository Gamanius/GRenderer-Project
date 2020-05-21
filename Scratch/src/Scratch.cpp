#include <GRenderer.h>

#include <iostream>

int main() {
	GGeneral::Logger::init();
	GGeneral::Logger::printMessage("test", GGeneral::Logger::Severity::S_MSG, -1);
	std::cin.get();
}