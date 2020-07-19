#include <GRenderer.h>
#include <cassert>
#include <Windows.h>

GWindow::Window* window = nullptr;

void callback(GWindow::WindowEvent event, void* data) {
	using namespace GWindow;
	if (event == WindowEvent::KEY_PRESS || event == WindowEvent::KEY_RELEASE) {
		LOGI((VK)(int)data);
	}
	if (event == WindowEvent::WINDOW_RESIZE) {
		GGraphics::setViewport(window->getWindowDrawSize());
	}
}

int main() {
	if (!GRenderer::init())
		abort();

	window = new GWindow::Window("2D Testing", { 0, 0 }, { 1280, 720 });
	GWindow::Window w = *window;
	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	w.addCallbackFunction(callback);
	GGraphics::init();
	GGraphics::setViewport(w.getWindowDrawSize());
	w.setState(GWindow::WindowState::NORMAL);
	LOGS("Initialized!");
	LOGI("GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER));
	LOGI("Current Date: ", GGeneral::Time::getCurrentTime());

	GMath::mat2x2<int> m;

	while (!w.getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		GGraphics::setColor({ 50, 0, 50 });
		GGraphics::drawRect({ 0, 0, 1280, 100 });
		LOGI(w.getCurrentWindowState());
		w.swapBuffers();
		w.fetchEvents();
	}

	GGeneral::Logger::wait();
	return 0;
}