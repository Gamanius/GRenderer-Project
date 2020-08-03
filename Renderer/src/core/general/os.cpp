#include "../GRenderer.h"
#include <Windows.h>
#include <lmcons.h>

GGeneral::String GGeneral::OS::getComputerName() {
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD lenght = MAX_COMPUTERNAME_LENGTH + 1;
	auto error = GetComputerNameA(computerName, &lenght);
	if (error == 0) {
		THROW("Error while trying to get computer name. Code: ", GetLastError());
	}
	return GGeneral::String(computerName);
}

GGeneral::String GGeneral::OS::getUserName() {
	char userName[UNLEN + 1];
	DWORD length = UNLEN + 1;
	auto error = GetUserNameA(userName, &length);
	if (error == 0) {
		THROW("Error while trying to get user name. Code: ", GetLastError());
	}
	return GGeneral::String(userName);
}

void GGeneral::OS::moveMouse(GGeneral::Point<int> newPos) {
	SetCursorPos(newPos.x, newPos.y);
}