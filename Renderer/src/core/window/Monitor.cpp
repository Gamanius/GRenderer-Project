#include <Windows.h>
#include <vector>

#include "GRenderer.h"

bool informationFetched = false;

uint32_t primaryMonitorIndex = 0;
uint32_t indexCounter = 0;
uint32_t maxAmountOfMonitors = 0;

std::vector<GWindow::Monitor::Screen*> allScreens;

BOOL CALLBACK lpfnEnum(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	auto s = new GWindow::Monitor::Screen();
	MONITORINFOEX info;
	info.cbSize = sizeof(info);
	GetMonitorInfo(hMonitor, &info);
	if (info.dwFlags) {
		primaryMonitorIndex = indexCounter;
	}

	DISPLAY_DEVICEA device;
	device.cb = sizeof(DISPLAY_DEVICEA);
	EnumDisplayDevicesA(0, allScreens.size(), &device, EDD_GET_DEVICE_INTERFACE_NAME);
	DISPLAY_DEVICEA device1;
	device1.cb = sizeof(DISPLAY_DEVICEA);
	EnumDisplayDevicesA(device.DeviceName, 0, &device1, EDD_GET_DEVICE_INTERFACE_NAME);
	s->screenName = GGeneral::String(device1.DeviceString);

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
	if (succesfull == 0) {
		THROW("Couldn't enumerate displays");
		return false;
	}

	DISPLAY_DEVICEA device;
	device.cb = sizeof(DISPLAY_DEVICEA);
	while (EnumDisplayDevicesA(0, maxAmountOfMonitors, &device, EDD_GET_DEVICE_INTERFACE_NAME))
		maxAmountOfMonitors++;

	informationFetched = true;
	return true;
}

//Will return true if the information for the Monitors has already been fetched
const bool GWindow::Monitor::isInit() {
	return informationFetched;
}

GWindow::Monitor::Screen const* GWindow::Monitor::getPrimaryMonitorInformation() {
	if (!isInit()) {
		THROW("Monitor information not fetched. Maybe the init() hasn't been called?");
		return nullptr;
	}
	return allScreens[primaryMonitorIndex];
}

const uint32_t GWindow::Monitor::getAmountOfMonitors() {
	if (!isInit()) {
		THROW("Monitor information not fetched. Maybe the init() hasn't been called?");
		return 0;
	}
	return allScreens.size();
}

const uint32_t GWindow::Monitor::getPrimaryMonitorIndex() {
	if (!isInit()) {
		THROW("Monitor information not fetched. Maybe the init() hasn't been called?");
		return 0;
	}
	return primaryMonitorIndex;
}

GWindow::Monitor::Screen const* GWindow::Monitor::getMonitorInformation(uint32_t i) {
	if (!isInit()) {
		THROW("Monitor information not fetched. Maybe the init() hasn't been called?");
		return nullptr;
	}
	return allScreens[i];
}

const uint32_t GWindow::Monitor::getSupportedAmountOfMonitorDevices() {
	if (!isInit()) {
		THROW("Monitor information not fetched. Maybe the init() hasn't been called?");
		return 0;
	}
	return maxAmountOfMonitors;
}