#include "GRenderer.h"
#include <fstream>
#include <sstream>
#include "test.txt"

#define VAR_NAME(x) GGeneral::toString(#x) + " = " + GGeneral::toString(x) + ", "

int main() {
	std::ofstream s("src/test.txt");

	s << "#define RETURN_ARG_COUNT(";
	for (size_t i = 1; i < 127; i++) {
		s << "_" << i << "_, ";
	}
	s << "count, ...) count\n#define EXPAND_ARGS(args) RETURN_ARG_COUNT args\n#define COUNT_ARGS_MAX(...) EXPAND_ARGS((__VA_ARGS__, ";
	for (int i = 126 - 1; i >= 0; i--) {
		s << i << ", ";
	}
	s << "0))\n";

	s << "#define VAR_NAME1(x) VAR_PRINTEND(x)" << "\n";
	for (size_t i = 2; i < 128; i++) {
		s << "#define VAR_NAME" << i << "(";
		unsigned int j;
		for (j = 0; j < i - 1; j++) {
			s << "x" << j << ", ";
		}
		s << "x" << j << ") VAR_PRINT(x0) + VAR_NAME" << i - 1 << "(";
		for (size_t k = 1; k < i - 1; k++) {
			s << "x" << k << ", ";
		}
		s << "x" << i - 1 << ")\n";
	}
	s << "\n#define CHOOSER126(count) VAR_NAME##count" << "\n";
	for (int i = 126 - 1; i >= 0; i--) {
		s << "#define CHOOSER" << i << "(count) CHOOSER" << i + 1 << "(count)\n";
	}
	s.close();
	GGeneral::Logger::init();

	int test = 0, x = 1, y = 3, h = 3;
	LOG(PRINT_VAR(h, h, h, h, h, h, h, h, h, h, h, h, h, h, h));

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}