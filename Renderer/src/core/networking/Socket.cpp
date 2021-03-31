#include "GRenderer.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#define FORMAT_THROW(msg, error)\
{LPVOID lpMsgBuf = nullptr;\
\
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |	FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, (LPTSTR)&lpMsgBuf, 0, NULL);\
THROWW(msg, (char*)lpMsgBuf);\
LocalFree(lpMsgBuf);}

GNetworking::Socket::Socket() {}

GNetworking::Socket::Socket(GGeneral::String ip, uint16_t port) {
	connect(ip, GGeneral::toString(port));
}

GNetworking::Socket::~Socket() {
	if (connected) {
		shutdown(this->socketNr, SD_BOTH);
		auto error = closesocket(this->socketNr);
		if (error != 0)
			THROW("WSA error while trying to close socket: ", WSAGetLastError());
	}
}

int socketConnect(SOCKET s, const sockaddr* addr, int n) {
	return connect(s, addr, n);
}

bool GNetworking::Socket::connect(GGeneral::String ip, GGeneral::String port) {
	addrinfo hints, * result = nullptr;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	auto error = getaddrinfo(ip, port, &hints, &result);
	if (error != 0) {
		THROW("Couldn't resolve IP/Port");
		return false;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	auto ptr = result;

	this->socketNr = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	error = socketConnect(this->socketNr, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (error == SOCKET_ERROR) {
		auto t = GetLastError();
		THROW("Error while trying to connect");
		closesocket(this->socketNr);
		this->socketNr = INVALID_SOCKET;
		return false;
	}
	freeaddrinfo(result);
	this->connected = true;

	return true;
}

void GNetworking::Socket::disconnect() {
	connected = false;
	auto error = shutdown(this->socketNr, SD_SEND);
	if (error != 0)
		FORMAT_THROW("WSA error while trying to shutdown the connection. A graceful shutdown is not possible: ", WSAGetLastError());

	//set to unblocking
	//setBlockingMode(false);

	byte* buffer = new byte[MAX_NET_BUFFER_SIZE];
	auto size = recv(socketNr, (char*)buffer, MAX_NET_BUFFER_SIZE, 0);
	while (size > 0) {
		size = recv(socketNr, (char*)buffer, MAX_NET_BUFFER_SIZE, 0);
	}
	delete[] buffer;

	if (size == SOCKET_ERROR)
		THROWW("Socket error while trying to receive last data. Disconnect is not graceful", WSAGetLastError());

	error = closesocket(this->socketNr);
	if (error != 0)
		THROW("WSA error while trying to shutdown socket: ", WSAGetLastError());
}

void windowsSSend(SOCKET s, byte* data, u_long size) {
	if (send(s, (char*)data, size, 0) == SOCKET_ERROR) {
		THROW("An error occurred when trying to send data: ", WSAGetLastError());
	}
}

void GNetworking::Socket::send(byte* data, u_long size) {
	windowsSSend(this->socketNr, data, size);
}

bool GNetworking::Socket::isConnected() {
	return this->connected;
}

bool GNetworking::Socket::setBlockingMode(bool block) {
	blocking = !block;
	auto error = ioctlsocket(socketNr, FIONBIO, (u_long*)&blocking);
	if (error != 0) {
		FORMAT_THROW("WSA error while trying to set IO mode on Socket: ", error);
	}
	return error == 0;
}

GNetworking::Package GNetworking::Socket::receive() {
	Package p;
	byte* buffer = new byte[MAX_NET_BUFFER_SIZE];
	p.data = buffer;
	memset(buffer, 0, MAX_NET_BUFFER_SIZE);

	WSABUF winBuffer;
	winBuffer.buf = (char*)p.data;
	winBuffer.len = MAX_NET_BUFFER_SIZE;

	u_long flags = 0;
	auto error = WSARecv(socketNr, &winBuffer, 1, &p.size, &flags, nullptr, nullptr);

	if (error != 0) {
		error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK)
			goto FINISH;
		else if (error == WSAECONNRESET) {
			THROWW("Connection has been reset");
			connected = false;
			goto FINISH;
		}

		this->connected = false;
		if (p.size != 0)
			FORMAT_THROW("WSA error while trying to receive data: ", WSAGetLastError());
	}
	else if (p.size == 0) {
		connected = false;

	FINISH:
		//solve possible memory leak
		delete[] buffer;
		p.data = nullptr;
	}

	return p;
}