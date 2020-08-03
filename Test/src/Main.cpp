#include <GRenderer.h>
#include <iostream>

int main() {
	auto error = GRenderer::init();
	error = error & GNetworking::init();
	if (error == 0) {
		LOGF("A fatal error occurred");
		exit(-1);
	}
	LOGS("Init");

	GNetworking::ServerSocket* so = new GNetworking::ServerSocket(7340);

	auto socket = *so;
	auto t = socket.accept();
	socket.setBlockingMode(true, t);
	if (t != ~0)
		LOGS("Connected");
	else
		exit(0);
	GGeneral::String s("dwa");
	socket.send(t, (byte*)s.cStr(), s.getSize());
	socket.receive(t);
	delete so;
	GGeneral::ErrorHandler::printAll();

	std::cin.get();
}