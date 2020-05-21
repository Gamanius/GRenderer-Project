#include "../GRenderer.h"

#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <WinUser.h>
#include <array>

//Some general Vars
std::list<GGeneral::Logger::Message> msgBuffer;
std::thread workerThread;

std::vector<std::string> userNames;

const std::array<unsigned int, 6> SeverityColors = { 8, 9, 10, 6, 4, 64 };

bool isInit = false;
bool shouldThreadWork = true;
bool shouldThreadTerminate = false;
bool threadBufferClearLock = false;
bool discardAllMsg = false;

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
	//if ((int)msg.sev >= (int)severityFilter) {
		//Print everything
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SeverityColors[(int)msg.sev]);
	std::cout << "[" << getSystemTime() << "|" << "dwa";
	if (msg.ID != -1 && msg.ID < userNames.size())
		std::cout << "|" << userNames[msg.ID];
	std::cout << "]: " << msg.msg << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//}
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

		//Clear the buffer if everything is done and noone is adding to it
		//Technically useless
		if (!threadBufferClearLock)
			msgBuffer.clear();
	}
}

void GGeneral::Logger::printMessage(Message in) {
	msgBuffer.push_back(in);
}

bool GGeneral::Logger::init() {
	if (isInit)
		return false;
	workerThread = std::thread(t_process);
	return true;
}

void GGeneral::Logger::wait() {}