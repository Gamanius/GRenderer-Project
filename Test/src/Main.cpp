#include <GRenderer.h>

int main() {
	GRenderer::init();

	GWindow::Window window;
	window.setState(GWindow::WindowState::NORMAL);
	window.createOpenGLcontext();
	window.setOpenGLContextActive(true);

	GGraphics::init();

	while (!window.getCloseRequest()) {
		GRenderer::clear({ 255, 255, 255 });
		GGraphics::setColor({ 0 });
		GGraphics::drawRect(GGeneral::Rectangle<int>(0, 0, 50, 50));

		window.swapBuffers();
		window.fetchEvents();
	}
}