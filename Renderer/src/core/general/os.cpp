#include "../GRenderer.h"
#include <Windows.h>
#include <lmcons.h>

std::string GGeneral::OS::getComputerName() {
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD lenght = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameA(computerName, &lenght);
	return std::string(computerName);
}

std::string GGeneral::OS::getUserName(){
	char userName[UNLEN + 1];
	DWORD length = UNLEN + 1;
	GetUserNameA(userName, &length);
	return std::string(userName);
}

void GGeneral::OS::moveMouse(GGeneral::Point<int> newPos) {
	SetCursorPos(newPos.x, newPos.y);
}
