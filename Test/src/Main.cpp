#include <GRenderer.h>
#include <windows.h>
#include <iostream>

int main() {
	GRenderer::init();
	LOGI(GGamepad::getAmountOfConnectedGPad());
	auto g = GGamepad::getGamepad(1);
	GGamepad::GamepadState state = g.getState();
	while (!state.button_a) {
		LOG(state);
		state = g.getState();
		Sleep(16);
		GGeneral::Logger::wait();
	}
}