#pragma once

#include <GRenderer.h>
#include <iostream>

int main() {
	auto error = GRenderer::init();
	error = error & GNetworking::init();
	if (error == 0)
		LOGF("Couldn't init");

	auto sock = new GNetworking::Socket("jlb734-47100.portmap.host", 47100);
	sock->setBlockingMode(false);
	while (sock->isConnected()) {
		auto b = sock->receive();
		LOGI(b.size);
		if (b.data != nullptr)
			LOG(GGeneral::String(b.data));
		//Sleep(1000);
		//sock.disconnect();
	}

	delete sock;
	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();
}