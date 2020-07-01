#include "../GRenderer.h"
#include <Windows.h>
#include <lmcons.h>

GGeneral::String GGeneral::OS::getComputerName() {
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD lenght = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameA(computerName, &lenght);
	return GGeneral::String(computerName);
}

GGeneral::String GGeneral::OS::getUserName() {
	char userName[UNLEN + 1];
	DWORD length = UNLEN + 1;
	GetUserNameA(userName, &length);
	return GGeneral::String(userName);
}

void GGeneral::OS::moveMouse(GGeneral::Point<int> newPos) {
	SetCursorPos(newPos.x, newPos.y);
}