#include <GRenderer.h>
#include <iostream>

int main() {
	auto error = GRenderer::init();
	error = error & GNetworking::init();
	if (error == 0) {
		LOGF("A fatal error occurred");
		exit(-1);
	}

	auto source = GFile::loadFileS("src/source.gproj");
	GScript::Interpreter i(source);
	auto test = i.prepare();

	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();

}