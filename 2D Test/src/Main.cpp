#include <GRenderer.h>
#include <cassert>
#include <Windows.h>

GWindow::Window* window = nullptr;

GGeneral::Point<float> pos1 = { 50, 50 }, pos2 = { 100, 100 };

void keyCallback(GWindow::Window* window, bool pressed, GWindow::VK key) {}

int main() {
	if (!GRenderer::init())
		abort();

	GGeneral::ErrorHandler::printAll();

	GEventWrapper::Windowhandler handler;
	window = new GWindow::Window("2D Testing", { 0, 0 }, { 1280, 720 });
	GWindow::Window w = *window;
	w.hint(GWindow::Window::ContextHints::MAJOR_VERSION, 4);
	w.hint(GWindow::Window::ContextHints::MINOR_VERSION, 5);

	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	handler.registerWindow(window);
	handler.addCallback(keyCallback);

	GGraphics::init();
	GGraphics::setViewport(w.getWindowDrawSize());
	w.setState(GWindow::WindowState::NORMAL);

	LOGS("Initialized!");
	LOGI("GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER), " Version: ", GRenderer::getGLString(GRenderer::GLString::SHADER_VERSION));
	LOGI("Current Date: ", GGeneral::Time::getCurrentTime());

	GMath::mat2x2<int> m;

	int counter = 0;
	while (!w.getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		GGraphics::setColor({ 50, 0, 50 });
		GGraphics::drawRect({ (int)pos1.x, (int)pos1.y, 50, 50 });

		GGraphics::setColor({ 255, 255, 255 });
		GGraphics::drawRect({ (int)pos2.x, (int)pos2.y, 50, 50 });

		double delta = GRenderer::delta();
		delta *= 0.3f;
		if (handler.isKeyPressed(GWindow::VK::W)) {
			pos1.y += delta;
		}if (handler.isKeyPressed(GWindow::VK::A)) {
			pos1.x -= delta;
		}if (handler.isKeyPressed(GWindow::VK::S)) {
			pos1.y -= delta;
		}if (handler.isKeyPressed(GWindow::VK::D)) {
			pos1.x += delta;
		}
		if (handler.isKeyPressed(GWindow::VK::UPARROW)) {
			pos2.y += delta;
		}if (handler.isKeyPressed(GWindow::VK::LEFTARROW)) {
			pos2.x -= delta;
		}if (handler.isKeyPressed(GWindow::VK::DOWNARROW)) {
			pos2.y -= delta;
		}if (handler.isKeyPressed(GWindow::VK::RIGHTARROW)) {
			pos2.x += delta;
		}
		if (counter > 100) {
			auto rec = GGeneral::Rectangle(pos1, 50.0f, 50.0f);
			LOGI(rec.isColliding(GGeneral::Rectangle<float>(pos2, 50.0f, 50.0f)));
			counter = 0;
		}
		counter++;
		w.swapBuffers();
		w.fetchEvents();
	}

	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();
	return 0;
}