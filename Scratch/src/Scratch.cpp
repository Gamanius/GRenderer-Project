#pragma once

#include <GRenderer.h>
#include <iostream>
#include <Windows.h>

int main() {
	auto error = GRenderer::init();
	error = error & GNetworking::init();
	if (error == 0)
		LOGF("Couldn't init");

	GWindow::Window window("heyo", { 100, 100 }, { 1280, 720 });
	window.createOpenGLcontext();
	window.setOpenGLContextActive();
	window.setState(GWindow::WindowState::MAXIMIZED);
	GGraphics::init();
	GGraphics::setViewport(window.getWindowDrawSize());

	GRenderer::setWireFrameMode(false);

	auto t = GFile::Graphics::loadCursor("rsc/img/cursor.cur");
	window.setCursor(t);
	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();

	auto img = GFile::Graphics::loadImage("rsc/img/s.png");
	img->flip();
	//auto tex = GRenderer::Texture(*img);

	while (!window.getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		using namespace GGraphics;
		setColor({ 0,0,0 });
		drawImg({ 50, 50 }, *img);
		drawRect({ 50, 50, 50, 50 });
		window.swapBuffers();
		window.fetchEvents();
	}

	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();
}