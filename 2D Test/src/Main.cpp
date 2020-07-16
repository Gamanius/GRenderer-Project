#include <GRenderer.h>
#include <cassert>
#include <Windows.h>

int main() {
	GRenderer::init();

	GWindow::Window w("2D Testing", { 0, 0 }, { 1280, 720 });
	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	GGraphics::init();
	w.setState(GWindow::WindowState::NORMAL);
	LOGS("Initialized!");
	LOGI("GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER));
	LOGI("Current Date: ", GGeneral::Time::getCurrentTime());

	GMath::mat2x2<int> m;
	IF_EXTENDED_MEM(
		auto alloc = GMemory::getAllocInfo();
	auto amount = GET_ALLOC_INFO_COUNT(alloc);
	for (size_t i = 0; i < amount; i++) {
		LOG(alloc[i]->fileName);
	});

	while (!w.getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		GGraphics::setColor({ 50, 0, 50 });
		GGraphics::drawRect({});
		w.swapBuffers();
		w.fetchEvents();
	}

	IF_EXTENDED_MEM(alloc = GMemory::getAllocInfo();
	amount = GET_ALLOC_INFO_COUNT(alloc);
	for (size_t i = 0; i < amount; i++) {
		LOG(alloc[i]->fileName);
	});

	GGeneral::Logger::wait();
	return 0;
}