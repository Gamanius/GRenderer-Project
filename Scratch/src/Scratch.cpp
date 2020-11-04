#pragma once

#include <GRenderer.h>
#include <iostream>
#include <string>
#include <thread>

GNetworking::ServerSocket* serverSocket = nullptr;
unsigned int clientSocket = 0;

GNetworking::Socket* client = nullptr;

bool doLoop = true;

static void updateServerSocket() {
	while (doLoop) {
		auto p = serverSocket->receive(clientSocket);
		if (p.data != nullptr && p.size > 1)
			LOGI("Client: ", GGeneral::String(p.data));
	}
}

static void updateClientSocket() {
	while (doLoop) {
		auto p = client->receive();
		if (p.data != nullptr && p.size > 1)
			LOGI("Server: ", GGeneral::String(p.data));
	}
}

int main(int argc, char** argv) {
	auto error = GRenderer::init();
	if (error == 0)
		LOGF("Couldn't init");
	LOGS("Initialized");
	LOGI("Using Version: ", G_RENDERER_VERSION);

	unsigned int port = 0;
	bool isServer = true;
	GGeneral::String ip;

	if (argc == 3) {
		if (GGeneral::String(argv[1]).compare("server")) {
			auto s = GGeneral::String(argv[2]);
			port = std::stoi(s.cStr());
		}
		else
			goto NOT_GOOD;
	}
	else if (argc == 4) {
		if (GGeneral::String(argv[1]).compare("noserver")) {
			auto s = GGeneral::String(argv[2]);
			port = std::stoi(s.cStr());
			ip = GGeneral::String(argv[3]);
		}
		else
			goto NOT_GOOD;
		isServer = false;
	}
	else {
		THROW("Invalid Parameters");
	NOT_GOOD:
		LOGE("An error occurred: ");
		GGeneral::ErrorHandler::printAll();
		LOG("Press Enter to continue");
		GGeneral::Logger::wait();
		std::cin.get();
		exit(-1);
	}

	if (isServer) {
		serverSocket = new GNetworking::ServerSocket(port);
		LOGI("Searching for Sockets on port: ", port);
		clientSocket = serverSocket->accept();
		serverSocket->setBlockingMode(false, clientSocket);
		if (clientSocket != ~0) {
			LOGS("Connected to other socket");
		}
		else {
			goto NOT_GOOD;
		}

		std::thread t(updateServerSocket);
		while (serverSocket->isConnected(clientSocket)) {
			std::string  in;
			GGeneral::Logger::wait();
			std::cout << ">>";
			getline(std::cin, in);
			serverSocket->send(clientSocket, (byte*)in.c_str(), in.length() + 1);
		}
		doLoop = false;
		t.join();
		serverSocket->disconnect(clientSocket);
	}
	else {
		LOGI("Searching for Sockets on port: ", port, "with IP: ", ip);
		client = new GNetworking::Socket(ip, port);
		if (client->isConnected()) {
			LOGS("Connected to other socket");
		}
		else {
			goto NOT_GOOD;
		}
		std::thread t(updateClientSocket);
		while (client->isConnected()) {
			std::string  in;
			GGeneral::Logger::wait();
			std::cout << ">>";
			getline(std::cin, in);
			GNetworking::Package p;
			client->send((byte*)in.c_str(), in.length() + 1);
		}
		doLoop = false;
		t.join();
		client->disconnect();
	}
}