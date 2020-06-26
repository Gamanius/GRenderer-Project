#include "GRenderer.h"
#include <fstream>
#include <sstream>
#include "test.txt"

#define VAR_NAME(x) GGeneral::toString(#x) + " = " + GGeneral::toString(x) + ", "

int main() {
	GGeneral::Logger::init();

	GMath::vec4 vector(0, 1, 2, 3);
	auto test = vector.memadd();

	auto matrix = GMath::mat4x4Identity<int>();
	matrix.translate(GMath::vec3(1, 0, 0));
	test = matrix.memadd();

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}