#include "GRenderer.h"

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
std::mutex _globalMutex;

std::vector<GGeneral::String> userNames;

const std::array<uint32_t, 6> SeverityColors = {8, 9, 10, 6, 4, 64};

volatile GGeneral::Logger::Severity severityFilter = GGeneral::Logger::Severity::S_MSG;

volatile bool isInit = false;
volatile bool wasInit = false;
volatile bool shouldThreadTerminate = false;
volatile bool threadBufferClearLock = false;

inline std::ostream& operator<<(std::ostream& os, const GGeneral::BaseObject& obj) {
	os << obj.toString();
	return os;
}

void processMsg(GGeneral::Logger::Message msg) {
	if ((int)msg.sev >= (int)severityFilter) {
		//Print everything
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SeverityColors[(int)msg.sev]);

		GGeneral::Time::TimePoint time(msg.time);
		GGeneral::Time::fillTimePoint(time);
		std::cout << "[" << time.hour << ":" << time.minute << ":" << time.seconds << ":" << time.microsecond << "|";
		switch (msg.sev) {
		case GGeneral::Logger::Severity::S_MSG:       std::cout << "MESSAGE";  break;
		case GGeneral::Logger::Severity::S_INFO:      std::cout << "INFO";	   break;
		case GGeneral::Logger::Severity::S_SUCCESS:   std::cout << "SUCCESS";  break;
		case GGeneral::Logger::Severity::S_WARNING:   std::cout << "WARNING";  break;
		case GGeneral::Logger::Severity::S_ERROR:	  std::cout << "ERROR";	   break;
		case GGeneral::Logger::Severity::S_FATAL:     std::cout << "FATAL";	   break;
		}
		std::cout << "]: " << msg.msg << "\n";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}

void t_process() {
	while (!shouldThreadTerminate) {
		auto it = msgBuffer.cbegin();
		_globalMutex.lock();
		while (it != msgBuffer.cend()) {
			if (shouldThreadTerminate)
				return;

			processMsg(*it);
			it++;
			msgBuffer.pop_front();
		}
		_globalMutex.unlock();
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10ms);
	}
}

void GGeneral::Logger::printMessage(Message in) {
	if (isInit) {
		if (maxBufferSize > 0)
			while (maxBufferSize > (int)msgBuffer.size());
		//testing without any locks
		_globalMutex.lock();
		msgBuffer.push_back(in);
		_globalMutex.unlock();
	}
	else {
		_globalMutex.lock();
		processMsg(in);
		_globalMutex.unlock();
	}
}

void GGeneral::Logger::setSeverityFilter(Severity filter) {
	severityFilter = filter;
}

GGeneral::Logger::Severity GGeneral::Logger::getSeverityFilter() {
	return severityFilter;
}

void stop() {
	//Threads need to be terminated to not cause a crash
	GGeneral::Logger::terminateThread();
}

bool GGeneral::Logger::init() {
	if (isInit)
		return false;

	int result;
	if (!wasInit) {
		result = std::atexit(stop);
		if (result != 0) {
			THROW("Logger couldn't set custom exit function");
			return false;
		}
	}

	wasInit = true;
	isInit = true;
	workerThread = std::thread(t_process);
	return true;
}

void GGeneral::Logger::wait() {
	volatile size_t s = msgBuffer.size();
	while (s != 0) {
		_globalMutex.lock();
		s = msgBuffer.size();
		_globalMutex.unlock();
	}
}

void GGeneral::Logger::terminateThread() {
	//Dont try to terminate if there is no thread
	if (isInit) {
		isInit = false;
		shouldThreadTerminate = true;

		workerThread.join();
		workerThread.~thread();

		shouldThreadTerminate = false;
		msgBuffer.clear();
	}
}