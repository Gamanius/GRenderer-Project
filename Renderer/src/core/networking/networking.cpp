#include "GRenderer.h"

#include <winsock2.h>
#include <ws2tcpip.h>

bool GNetworking::init() {
	WSADATA wsaData;
	int error;

	// Initialize Winsock
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0) {
		THROW("Couldn't start WSA (Winsock).");
		return false;
	}
	return true;
}