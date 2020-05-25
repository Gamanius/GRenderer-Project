#include <Windows.h>
#include <vector>

#include "../GRenderer.h"

bool informationFetched = false;

unsigned int primaryMonitorIndex = 0;
unsigned int indexCounter = 0;

std::vector<GWindow::Monitor::Screen*> allScreens;

BOOL CALLBACK lpfnEnum(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	auto s = new GWindow::Monitor::Screen();
	MONITORINFOEX info;
	info.cbSize = sizeof(info);
	GetMonitorInfo(hMonitor, &info);
	if (info.dwFlags) {
		primaryMonitorIndex = indexCounter;
	}

	s->screenName = std::to_string(*info.szDevice);

	s->digitalPosition.x = info.rcMonitor.left;
	s->digitalPosition.y = info.rcMonitor.top;

	s->screenDimension.width = info.rcMonitor.right - info.rcMonitor.left;
	s->screenDimension.height = info.rcMonitor.bottom - info.rcMonitor.top;

	s->workDimension.width = info.rcWork.right - info.rcWork.left;
	s->workDimension.height = info.rcWork.bottom - info.rcWork.top;

	allScreens.push_back(s);

	indexCounter++;
	return TRUE;
}

bool GWindow::Monitor::init() {
	int succesfull = EnumDisplayMonitors(0, 0, lpfnEnum, 0);
	if (succesfull == 0) return false;
	informationFetched = true;
	return true;
}

//Will return true if the information for the Monitors has already been fetched
const bool GWindow::Monitor::isInit() {
	return informationFetched;
}

GWindow::Monitor::Screen const* GWindow::Monitor::getPrimaryMonitorInformation() {
	if (!isInit())
		return nullptr;
	return allScreens[primaryMonitorIndex];
}

const unsigned int GWindow::Monitor::getAmountOfMonitors() {
	if (!isInit())
		return 0;
	return allScreens.size();
}

const unsigned int GWindow::Monitor::getPrimaryMonitorIndex() {
	if (!isInit())
		return 0;
	return primaryMonitorIndex;
}

GWindow::Monitor::Screen const* GWindow::Monitor::getMonitorInformation(unsigned int i) {
	if (!isInit())
		return nullptr;
	return allScreens[i];
}