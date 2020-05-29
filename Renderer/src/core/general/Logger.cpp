#include "../GRenderer.h"

#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <array>

//Some general Vars
std::list<GGeneral::Logger::Message> msgBuffer;
std::thread workerThread;

std::vector<std::string> userNames;

const std::array<unsigned int, 6> SeverityColors = { 8, 9, 10, 6, 4, 64 };

volatile GGeneral::Logger::Severity severityFilter = GGeneral::Logger::Severity::S_MSG;

volatile bool isInit = false;
volatile bool shouldThreadWork = true;
volatile bool shouldThreadTerminate = false;
volatile bool threadBufferClearLock = false;
volatile bool discardAllMsg = false;

std::string getSystemTime() {
	//Outdateted...maybe use something better than ctime n0ob
	struct tm currentTime;
	time_t now = time(0);
	localtime_s(&currentTime, &now);
	std::string seconds = std::to_string(currentTime.tm_sec);
	std::string minutes = std::to_string(currentTime.tm_min);

	if (seconds.size() == 1)
		seconds = "0" + seconds;
	if (minutes.size() == 1)
		minutes = "0" + minutes;

	return  std::to_string(currentTime.tm_hour) + ":" + minutes + ":" + seconds;
}

void printmsg(GGeneral::Logger::Message msg) {
	if ((int)msg.sev >= (int)severityFilter) {
		//Print everything
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SeverityColors[(int)msg.sev]);
		std::cout << "[" << getSystemTime() << "|" << GEnumString::enumToString(msg.sev);
		if (msg.ID != -1 && msg.ID < (int)userNames.size())
			std::cout << "|" << userNames[msg.ID];
		std::cout << "]: " << msg.msg << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}

void t_process() {
	while (shouldThreadWork) {
		auto it = msgBuffer.cbegin();
		while (it != msgBuffer.cend()) {
			if (shouldThreadTerminate)
				return;
			if (discardAllMsg)
				break;
			while (threadBufferClearLock);

			printmsg(*it);
			it++;
			msgBuffer.erase(msgBuffer.begin());
		}
		//Maybe fix...this function may discard messages sometimes
		/*
		//Clear the buffer if everything is done and noone is adding to it
		//Technically useless
		if (!threadBufferClearLock)
			msgBuffer.clear();
			*/
	}
}

void GGeneral::Logger::printMessage(Message in) {
	if (maxBufferSize > 0)
		while (maxBufferSize > (int)msgBuffer.size());
	threadBufferClearLock = true;
	msgBuffer.push_back(in);
	threadBufferClearLock = false;
}

void GGeneral::Logger::setSeverityFilter(Severity filter) {
	severityFilter = filter;
}

GGeneral::Logger::Severity GGeneral::Logger::getSeverityFilter() {
	return severityFilter;
}

int GGeneral::Logger::addUserName(std::string name) {
	for (unsigned int i = 0; i < userNames.size(); i++) {
		if (userNames[i].compare(name) == 0)
			return -1;
	}
	auto id = userNames.size();
	userNames.push_back(name);
	return id;
}

bool GGeneral::Logger::init() {
	if (isInit)
		return false;
	workerThread = std::thread(t_process);
	return true;
}

void GGeneral::Logger::wait() {
	while (msgBuffer.size() != 0);
}

void GGeneral::Logger::terminateThread() {
	isInit = false;
	shouldThreadTerminate = true;
	shouldThreadWork = false;

	workerThread.join();

	shouldThreadTerminate = false;
	shouldThreadWork = true;
	msgBuffer.clear();
}