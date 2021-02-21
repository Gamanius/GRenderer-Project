#include "GRenderer.h"

std::vector<GGeneral::Logger::Message> allmsg;

void GGeneral::ErrorHandler::add(GGeneral::String errorMessage, Logger::Severity sev) {
	GGeneral::Logger::Message m = {};
	m.msg = GGeneral::String(errorMessage);
	m.sev = sev;
	allmsg.push_back(m);
}

void GGeneral::ErrorHandler::printAll() {
	if (allmsg.size() == 0)
		return;
	LOGI("Start of Errors (", allmsg.size(), " in total): ");
	LOG("--------------------------------------------------");
	for (auto& msg : allmsg) {
		GGeneral::Logger::printMessage(msg.msg, msg.sev);
	}
	LOG("--------------------------------------------------");
}

GGeneral::String GGeneral::ErrorHandler::getLastError() {
	return allmsg[allmsg.size()].msg;
}

void GGeneral::ErrorHandler::clearBuffer() {
	allmsg.clear();
}