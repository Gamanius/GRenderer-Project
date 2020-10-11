#include "../GRenderer.h"
#include <Windows.h>
#include <lmcons.h>

#define FORMAT_THROW(msg, error)\
{LPVOID lpMsgBuf = nullptr;\
\
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |	FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, (LPTSTR)&lpMsgBuf, 0, NULL);\
THROW(msg, (char*)lpMsgBuf);\
LocalFree(lpMsgBuf);}

GGeneral::String GGeneral::OS::getComputerName() {
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD lenght = MAX_COMPUTERNAME_LENGTH + 1;
	auto error = GetComputerNameA(computerName, &lenght);
	if (error == 0) {
		FORMAT_THROW("Error while trying to get computer name: ", GetLastError());
	}
	return GGeneral::String(computerName);
}

GGeneral::String GGeneral::OS::getUserName() {
	char userName[UNLEN + 1];
	DWORD length = UNLEN + 1;
	auto error = GetUserNameA(userName, &length);
	if (error == 0) {
		FORMAT_THROW("Error while trying to get user name: ", GetLastError());
	}
	return GGeneral::String(userName);
}

void GGeneral::OS::moveMouse(GGeneral::Point<int> newPos) {
	SetCursorPos(newPos.x, newPos.y);
}