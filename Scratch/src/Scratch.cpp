#include <GRenderer.h>

#include <iostream>

int main() {
	GGeneral::Logger::init();
	auto something = GGeneral::Logger::addUserName("heyo");
	GGeneral::Logger::printMessage("test", GGeneral::Logger::Severity::S_MSG, something);
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}