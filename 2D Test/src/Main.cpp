#include <GRenderer.h>
#include <cassert>
#include <Windows.h>

int main() {
	assert(GRenderer::init());

	GWindow::Window w("2D Testing", { 0, 0 }, { 1280, 720 });
	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	w.setState(GWindow::WindowState::NORMAL);
	LOGS("Initialized!");
	LOGI("GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER));
	LOGI("Current Date: ", GGeneral::Time::getCurrentTime());

	while (!w.getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		w.swapBuffers();
		w.fetchEvents();
	}

	GGeneral::Logger::wait();
	return 0;
}