#include <GRenderer.h>

int main() {
	GRenderer::init();

	GWindow::Window* main = new GWindow::Window();
	main->createOpenGLcontext();
	main->setOpenGLContextActive();
	main->setState(GWindow::WindowState::NORMAL);

	GGeneral::HSVColor hsvcolor(0, 0, .3);
	while(!main->getCloseRequest()) {
		GRenderer::clear(hsvcolor.HSVtoRGB());

		main->fetchEvents();
		main->swapBuffers();
	}
	/*
	auto source = GFile::loadFileS("src/source.gproj");

	GFScript::Tokenizer tok(source);
	auto t = tok.createTokens();
	GFScript::Interpreter i(t);
	i.prepare(true);
	i.execute();
	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();*/
}