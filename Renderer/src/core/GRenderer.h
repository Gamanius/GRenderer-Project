#pragma once

#include <string>
#include <sstream>

namespace GGeneral {
	/**
	 *
	 */
	namespace Logger {
		static long maxBufferSize = -1;

		enum class Severity {
			S_MSG, S_INFO, S_SUCCESS, S_WARNING, S_ERROR, S_FATAL
		};

		struct Message {
			std::string msg;
			Severity sev;
			int ID;
		};

		bool init();

		void printMessage(Message in);

		template<typename T_T>
		void printMessage(T_T message, Severity sev, int ID) {
			std::ostringstream stream;
			stream << message;
			printMessage({ stream.str(), sev, ID });
		}

		void wait();
	};
}

namespace GRenderer {
}
