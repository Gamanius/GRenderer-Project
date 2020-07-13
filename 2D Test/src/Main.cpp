#include <GRenderer.h>
#include <cassert>
#include <Windows.h>

int main() {
	assert(GRenderer::init());

	auto alloc = GMemory::getAllocInfo();
	auto amount = GET_ALLOC_INFO_COUNT(alloc);
	for (size_t i = 0; i < amount; i++) {
		LOG(alloc[i]->fileName, " Size: ", alloc[i]->size);
	}

	//GWindow::Window w("2D Testing", { 0, 0 }, { 1280, 720 });
	//w.createOpenGLcontext();
	//w.setOpenGLContextActive(true);
	//w.setState(GWindow::WindowState::NORMAL);
	//LOGS("Initialized!");
	//LOGI("GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER));
	//LOGI("Current Date: ", GGeneral::Time::getCurrentTime());
	//
	//GMath::mat2x2<int> m;
	//auto alloc = GMemory::getAllocInfo();
	//auto amount = GET_ALLOC_INFO_COUNT(alloc);
	//for (size_t i = 0; i < amount; i++) {
	//	LOG(alloc[i]->fileName);
	//}
	//
	//while (!w.getCloseRequest()) {
	//	GRenderer::clear({ 50, 50, 50 });
	//	w.swapBuffers();
	//	w.fetchEvents();
	//}

	GGeneral::Logger::wait();
	return 0;
}