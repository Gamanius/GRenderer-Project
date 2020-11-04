#include <GRenderer.h>
#include <iostream>

int main(int argv, char** argc) {
	LOGI("Starting");
	auto error = GRenderer::init();
	error = error & GNetworking::init();
	if (error == 0) {
		LOGF("A fatal error occurred");
		exit(-1);
	}
	LOGS("Successful!");
	LOGI("Using Version: ", G_RENDERER_VERSION);

	GGeneral::String source;
	if (argv > 1)
		source = GFile::loadFileS(argc[1]);
	else
		source = GFile::loadFileS("src/source.gproj");

	auto start = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;
	GFScript::Tokenizer t(source);
	auto test = t.createTokens();
	if (test != nullptr) {
		auto end = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;
		LOGS("Created tokens in ", (end - start), "ms");
		GFScript::Interpreter i(test);

		start = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;
		bool d = i.prepare(true);
		end = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;

		if (d) {
			LOGS("Created byte code in ", (end - start), "ms");
			start = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;
			i.execute();
			end = (double)(GGeneral::Time::getNanoTime()) / 1000000.0;
			LOGS("Executed code in ", (end - start), "ms");
		}
		else
			LOGE("An error occurred: ");
	}

	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();
	if (argv > 1)
		system("pause");
}