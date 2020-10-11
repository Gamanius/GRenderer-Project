#include "../GRenderer.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#define FORMAT_THROW(msg, error)\
{LPVOID lpMsgBuf = nullptr;\
\
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |	FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, (LPTSTR)&lpMsgBuf, 0, NULL);\
THROWW(msg, (char*)lpMsgBuf);\
LocalFree(lpMsgBuf);}

GNetworking::ServerSocket::ServerSocket() {}

GNetworking::ServerSocket::ServerSocket(unsigned int port) {
	listen(port);
}

GNetworking::ServerSocket::~ServerSocket() {
	for (auto s : sockets) {
		disconnect(s);
	}
	closesocket(listenSocket);
}

int wListen(SOCKET s, int log) {
	return listen(s, log);
}

SOCKET wAccept(SOCKET s, sockaddr* addr, int* addrlen) { return accept(s, addr, addrlen); }

unsigned int GNetworking::ServerSocket::accept() {
	SOCKET newSocket = wAccept(listenSocket, nullptr, nullptr);
	if (newSocket == INVALID_SOCKET) {
		auto error = WSAGetLastError();
		if (error != WSAEWOULDBLOCK)
			FORMAT_THROW("WSA error while trying to accept a new Socket: ", error);
	}
	else {
		sockets.push_back(newSocket);
	}
	return newSocket;
}

bool GNetworking::ServerSocket::listen(unsigned short port) {
	sockaddr_in test = {};
	test.sin_port = htons(port);

	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET) {
		FORMAT_THROW("Invalid Socket: ", WSAGetLastError());
		return false;
	}

	sockaddr_in info = {};
	info.sin_family = AF_INET;
	info.sin_addr.s_addr = INADDR_ANY;
	info.sin_port = htons(port);

	auto error = bind(listenSocket, (sockaddr*)&info, sizeof(info));
	if (error != 0) {
		FORMAT_THROW("Couldn't bind Socket: ", WSAGetLastError());
		return false;
	}

	if (wListen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		FORMAT_THROW("Listen failed with error: ", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}
	return true;
}

void GNetworking::ServerSocket::disconnect(unsigned int socket) {
	auto error = shutdown(socket, SD_SEND);
	if (error != 0)
		FORMAT_THROW("WSA error while trying to shutdown the connection. A graceful shutdown is not possible: ", WSAGetLastError());
	byte* buffer = new byte[MAX_NET_BUFFER_SIZE];
	auto size = recv(socket, (char*)buffer, MAX_NET_BUFFER_SIZE, 0);
	while (size > 0) {
		size = recv(socket, (char*)buffer, MAX_NET_BUFFER_SIZE, 0);
	}
	delete[] buffer;

	if (size == SOCKET_ERROR)
		THROWW("Socket error while trying to receive last data. Disconnect is not graceful");

	error = closesocket(socket);
	if (error != 0)
		FORMAT_THROW("WSA error while trying to shutdown socket: ", WSAGetLastError());
}

bool GNetworking::ServerSocket::isConnected(unsigned int socket) {
	for (auto i : sockets) {
		if (i == socket)
			return true;
	}
	return false;
}

bool GNetworking::ServerSocket::setBlockingMode(bool block) {
	blocking = !block;
	auto error = ioctlsocket(listenSocket, FIONBIO, (unsigned long*)&blocking);
	if (error != 0) {
		THROWW("WSA error while trying to set IO mode on Socket: ", error);
	}
	return error == 0;
}

bool GNetworking::ServerSocket::setBlockingMode(bool block, unsigned int socket) {
	auto b = !block;
	auto error = ioctlsocket(socket, FIONBIO, (unsigned long*)&b);
	if (error != 0) {
		THROWW("WSA error while trying to set IO mode on Socket: ", error);
	}
	return error == 0;
}

unsigned int GNetworking::ServerSocket::getConnectedAmount() const {
	return sockets.size();
}

void windowsSend(SOCKET s, byte* data, unsigned int size) {
	send(s, (char*)data, size, 0);
}

void GNetworking::ServerSocket::send(unsigned int soket, byte* data, unsigned int size) {
	windowsSend(soket, data, size);
}

GNetworking::Package GNetworking::ServerSocket::receive(unsigned int socket) {
	Package p;
	byte* buffer = new byte[MAX_NET_BUFFER_SIZE];
	p.data = buffer;
	memset(buffer, 0, MAX_NET_BUFFER_SIZE);

	WSABUF winBuffer;
	winBuffer.buf = (char*)p.data;
	winBuffer.len = MAX_NET_BUFFER_SIZE;

	unsigned long flags = MSG_PUSH_IMMEDIATE;
	auto error = WSARecv(socket, &winBuffer, 1, &p.size, &flags, nullptr, nullptr);

	if (error != 0) {
		error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK)
			goto FINISH;
		//if (p.size != 0)

		FORMAT_THROW("WSA error while trying to receive data: ", error);

		for (size_t i = 0; i < sockets.size(); i++) {
			if (sockets[i] == socket) {
				sockets.erase(sockets.begin() + i);
				break;
			}
		}
	}
	else if (p.size == 0) {
		p.size = -1;
	FINISH:
		//solve possible memory leak
		delete[] buffer;
		p.data = nullptr;
	}

	return p;
}