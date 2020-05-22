#pragma once

#include <string>
#include <sstream>

/**
 * This namespace holds all function, namespaces, structs and classes that are not directly part of the Renderer but still integrated. Meaning with a rewrite the Renderer would still work but with the expense that everything is more or less unreadable and
 * very untidy.
 */
namespace GGeneral {
	/**
	 * This Logger class needs to be initialized manually before calling the printMessage() function.
	 * The class is multi threaded meaning that there is a buffer all messages will go into. All message in the buffer thread are being read from the worker thread, formatted and in the end printed to the console.
	 * You can set the maximum size of the buffer via setMaxBufferSize variable. If you try to send a message into the buffer, while the buffer size is larger or the same size as the maximum buffer size, the program will halt until there is enough free space to add new message
	 * Before the normal program termination you should always call terminateThread() to end the worker thread correctly.
	 * If you font want to use multi threading you can deactivate it by defining LOGGER_NO_MULTITHREAD (WIP).
	 * NOTE: There is a really small chance that a message will get deleted
	 */
	namespace Logger {
		/**
		 * Max Buffer Size is a variable that can be set to any number. If set to a number larger than 0 and the message buffer size is bigger than the max buffer size the function will halt until the message buffer has a smaller size.
		 */
		volatile static long maxBufferSize = -1;

		/**
		 * The Severity is an Enum that can indicate how important a message sent to the message buffer may be.
		 */
		enum class Severity {
			S_MSG /*! A plain message in gray. Used for unimportant messages*/
			, S_INFO /*! A info message in blue. Should be used for somewhat important messages*/
			, S_SUCCESS /*! A success message in green. Should be used to indicate that some process with somewhat importance was successful*/
			, S_WARNING /*! A warning message in yellow/orange. Should be used to warn the people*/
			, S_ERROR /*! A error message in red. Should be used to indicate that something went wrong*/
			, S_FATAL /*! A fatal error message in background red. Should be used to indicate that something really went wrong*/
		};

		/**
		 * A struct that holds all informations of a Message used in the worker thread-
		 */
		struct Message {
			std::string msg;
			Severity sev;
			int ID;
		};

		/**
		 * Needs to be called before sending any messages to the message buffer. It will create a worker thread that will print all messages from the buffer.
		 *
		 * @return A bool indicating if the initialization was successful
		 */
		bool init();

		/**
		 * Will add the given message to the buffer to be printed in the console when the thread is ready
		 *
		 * @param in - The Message to print
		 */
		void printMessage(Message in);

		/**
		 * Will create a new Message and then add it to the message buffer
		 *
		 * @param message - The message to print
		 * @param sev - The severity of the message
		 * @param ID - the user ID to be printed with the message
		 */
		template<typename T_T>
		void printMessage(T_T message, Severity sev, int ID) {
			std::ostringstream stream;
			stream << message;
			printMessage({ stream.str(), sev, ID });
		}

		/**
		 * Adds a new user name to the Logger. The int can be used in the printMessage() function to print the user name given. Every thread can use any User ID. there is no checking.
		 *
		 * @return The ID of the name
		 */
		int addUserName(std::string name);

		/**
		 * Sets the SeverityFilter to the given filter. All message that have a lower value of the filter will be discarded.
		 *
		 * @param filter - The new filter level
		 */
		void setSeverityFilter(Severity filter);

		/**
		 * Will return the current used filter level
		 *
		 * @return The current filter
		 */
		Severity getSeverityFilter();

		/**
		 * Will halt the thread that called that function until all message from the message buffer have been printed to the console.
		 */
		void wait();

		/**
		 * Will try to terminate the thread as early as possible. The message buffer will be cleared and the init function needs to be called if one wants to log messages again.
		 */
		void terminateThread();
	};
}

namespace GRenderer {
}

/**
 * This namespace holds just one function called enumToString. It's sole purpose is to take any Enum defined in the Renderer and return a string representing the name of the enum.
 */
namespace GEnumString {
	/**
	 * This function will take in any enum defined in the renderer and return its corresponding string. Note that this function is not type safe. If any other enums or values are passed in, it will just return "UNKNOWN ENUM"
	 *
	 *  @param GEnum - Any Enum defined in the renderer
	 *  @return A string with the same name as the Enum
	 */
	template<typename E>
	std::string enumToString(E GEnum) {
		auto enumMember = (int)GEnum;

		if (typeid(decltype(GEnum)) == typeid(GGeneral::Logger::Severity)) {
			auto sev = (GGeneral::Logger::Severity) enumMember;
			switch (sev) {
			case GGeneral::Logger::Severity::S_MSG:                     return "MESSAGE";
			case GGeneral::Logger::Severity::S_INFO:                    return "INFO";
			case GGeneral::Logger::Severity::S_SUCCESS:                 return "SUCCESS";
			case GGeneral::Logger::Severity::S_WARNING:                 return "WARNING";
			case GGeneral::Logger::Severity::S_ERROR:	                return "ERROR";
			case GGeneral::Logger::Severity::S_FATAL:                   return "FATAL";
			}
		}

		return "UNKNOWN ENUM";
	}
}