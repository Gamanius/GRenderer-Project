#include <GRenderer.h>

#include <iostream>

int main() {
	GGeneral::Logger::init();
	auto something = GGeneral::Logger::addUserName("heyo");
	GGeneral::Logger::printMessage("test", GGeneral::Logger::Severity::S_MSG, something);
	GGeneral::Dimension3D d(10, 200);
	GGeneral::Logger::printMessage(d, GGeneral::Logger::Severity::S_INFO, -1);
	GGeneral::Point p(1);
	GGeneral::Logger::printMessage(p, GGeneral::Logger::Severity::S_INFO, -1);
	GGeneral::Point3D p3d(5, 6);
	GGeneral::Logger::printMessage(p3d, GGeneral::Logger::Severity::S_INFO, -1);
	GWindow::Monitor::init();
	auto s = GWindow::Monitor::getPrimaryMonitorInformation();
	GGeneral::Logger::printMessage(*GWindow::Monitor::getMonitorInformation(2), GGeneral::Logger::Severity::S_INFO, -1);

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
	std::cin.get();
}