#include <GRenderer.h>

#include <iostream>

int main() {
	GGeneral::Logger::init();

	GWindow::Window w;
	w.setState(GWindow::WindowState::NORMAL);

	LOG("fe");
	while (!w.getCloseRequest()) {
		GWindow::Window::fetchEvents();
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();

	return 0;
}