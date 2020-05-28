#pragma once
#pragma comment(lib, "opengl32.lib")

#include <string>
#include <sstream>
#include <initializer_list>
#include <vector>

#ifndef _WIN32
#error Only Windows is Supported!
#elif _WIN64
#error There is no 64x support!
#endif

#ifndef NO_LOGGER_DEF
//Logger macros
#define LOG(x)      GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_MSG, -1);
#define LOGI(x)     GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_INFO, -1);
#define LOGS(x)     GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_SUCCESS, -1);
#define LOGW(x)     GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_WARNING, -1);
#define LOGE(x)     GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_ERROR, -1);
#define LOGF(x)     GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_FATAL, -1);

#define ULOG(x, y)  GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_MSG, y);
#define ULOGI(x, y) GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_INFO, y);
#define ULOGS(x, y) GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_SUCCESS, y);
#define ULOGW(x, y) GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_WARNING, y);
#define ULOGE(x, y) GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_ERROR, y);
#define ULOGF(x, y) GGeneral::Logger::printMessage(x, GGeneral::Logger::Severity::S_FATAL, y);
#endif //NO_LOGGER_DEF

typedef unsigned char byte;

//Documentation can be created using doxygen

/** \mainpage <strong>The SREP </strong>
 *  <p> This project is just a simple a try to create a Renderer that can, given the right data, make some beautiful pictures.The hope is that it can be used to create simple games and visualizations.The Renderer can only be used on Windows machines because of the inclusion of the <em>Win32</em> API. </p>
 */

 /**
  * This namespace holds all function, namespaces, structs and classes that are not directly part of the Renderer but still integrated. Meaning with a rewrite the Renderer would still work but with the expense that everything is more or less unreadable and
  * very untidy.
  */
namespace GGeneral {
	namespace Time {
		struct Timer {
			unsigned long long int startTime;
			Timer();
			unsigned long long int stop() const;
		};
}
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
		template<typename T_TYPE>
		void printMessage(T_TYPE message, Severity sev, int ID) {
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

	/**
	 * A struct containing tow values representing the dimension of anything in 2D.
	 */
	template<typename T>
	struct Dimension {
		/*! The width component of the Dimension */
		T width;
		/*! The height component of the Dimension */
		T height;
		/*! Creates a new Dimension with the given width and height. The type is up to the user but floats and doubles are recommended. Default values are 0 */
		Dimension(T w = 0, T h = 0) : width(w), height(h) {}

		/**
		 * @return A string with the current values of the Dimension struct
		 */
		virtual const std::string toString() const {
			std::stringstream s;
			s << "[width: " << width << ", height: " << height << "]";
			return s.str();
		}
	};

	template<typename T>
	struct Dimension3D : public Dimension<T> {
		/*! The depth component of the Dimension */
		T depth;
		/*! Creates a new Dimension with the given width, depth and height. The type is up to the user but floats and doubles are recommended. Default values are 0 */
		Dimension3D(T w = 0, T h = 0, T d = 0) : depth(d) {
			this->width = w;
			this->height = h;
		}

		/**
		 * @return A string with the current values of the Point struct
		 */
		const std::string toString() const override {
			std::stringstream s;
			s << "[width: " << this->width << ", height: " << this->height << ", depth: " << depth << "]";
			return s.str();
		}
	};

	/**
	 * A struct containing two values representing a point in 2D space.
	 */
	template<typename T>
	struct Point {
		/*! The x coordinate*/
		T x;
		/*! The y coordinate*/
		T y;
		/*! Creates a new Point with the given coordinates. The type is up to the user but floats and doubles are recommended. Default values are 0*/
		Point(T x = 0, T y = 0) : x(x), y(y) {}

		/**
		 * @return A string with the current values of the Point struct
		 */
		virtual const std::string toString() const {
			std::stringstream s;
			s << "[x: " << x << ", y: " << y << "]";
			return s.str();
		}
	};

	/**
	 * A struct extending the Point struct. This struct adds one more coordinate to define Points in 3D space.
	 */
	template<typename T>
	struct Point3D : public Point<T> {
		/*! The z coordinate*/
		T z;
		/*! Creates a new Point with the given coordinates. The type is up to the user but floats and doubles are recommended. Default values are 0*/
		Point3D(T x = 0, T y = 0, T z = 0) : z(z) {
			this->x = x;
			this->y = y;
		}

		/**
		 * @return A string with the current values of the Point struct
		 */
		const std::string toString() const override {
			std::stringstream s;
			s << "[x: " << this->x << ", y: " << this->y << ", z: " << z << "]";
			return s.str();
		}
	};
}

namespace GRenderer {
	namespace Primitives {
		enum class VertexTypes {
			BYTE, SHORT, INT
		};
		struct IndexBuffer {
		private:
			unsigned int amount;
			VertexTypes element;
		public:
			unsigned int ID;

			IndexBuffer(unsigned int data[], unsigned int amount);
			~IndexBuffer();

			void bind();
			void unbind();
			friend struct VertexArray;
		};

		struct VertexBuffer {
			unsigned int ID;

			VertexBuffer(float data[], unsigned int amount);
			~VertexBuffer();

			void bind();
			void unbind();
		};

		struct VertexArray {
			struct VertexArrayLayout {
			private:
				std::vector<byte> layout;
				VertexTypes type;
			public:
				VertexArrayLayout(std::initializer_list<byte> data, VertexTypes type);

				const unsigned int getStride() const;
				const unsigned int getOffset(const unsigned int index) const;
				friend struct VertexArray;
			};
			unsigned int ID;
			bool isOnlyVertexBuffer = false;
			unsigned int amount;
			VertexTypes type;

			VertexArray() {
				ID = 0;
				amount = 0;
				type = VertexTypes::INT;
			}
			VertexArray(VertexBuffer vertex, IndexBuffer index, VertexArrayLayout layout);

			void bind();
			void unbind();
		};
	}
}

typedef void(*GWindowCallback)(int);

namespace GWindow {
	/*! An Enum describing the different states the window can be in */
	enum class WindowState {
		HIDDEN /*! The Window is not visible by the user nor is it in the taskbar*/
		, MAXIMIZED /*! The Window is maximized and visible*/
		, MINIMIZED /*! The Window is not visible by the user but the icon can be seen on the taskbar*/
		, NORMAL /*! The Window is visible but not maximized*/
	};

	/*! These are all Keys that the event system is tracking. All other keys that are pressed will be discarded*/
	enum class VK {
		LEFT_MB, RIGHT_MB, CANCEL, MIDDLE_MB, X1_MB, X2_MB,
		LEFT_SHIFT, RIGHT_SHIFT, LEFT_CONTROL, RIGHT_CONTROL, BACKSPACE, TAB,
		ENTER, ALT, PAUSE, CAPSLOCK, ESCAPE, SPACE, PAGE_UP, PAGE_DOWN, END, HOME, LEFTARROW, UPARROW, RIGHTARROW, DOWNARROW,
		SELECT, PRINT, EXECUTE, PRINT_SCREEN, INSERT, DEL, HELP,
		KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LEFT_WINDOWS, RIGHT_WINDOWS, APPLICATION, SLEEP, SCROLL_LOCK, LEFT_MENU, RIGHT_MENU,
		VOLUME_MUTE, VOLUME_DOWN, VOLUME_UP,
		MEDIA_NEXT, MEDIA_LAST, MEDIA_STOP, MEDIA_PLAY_PAUSE,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8, OEM_CLEAR, OEM_PLUS, OEM_COMMA, OEM_MINUS, OEM_PERIOD,
		NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9, NUMPAD_MULTIPLY, NUMPAD_ADD, NUMPAD_SEPERATOR, NUMPAD_SUBTRACT, NUMPAD_COMMA, NUMPAD_DIVIDE, NUMPAD_LOCK,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
		PLAY, ZOOM, UNKWON
	};

	/**
	 * A class including all functions to create a window and fetch events from it using the WinAPI. When the class is constructed, it can only be accessed from the thread that constructed it.
	 * This also counts for the fetchEvents() function but not the init() function!
	 */
	class Window {
	private:
		/*! Window ID used to identify any window */
		int WindowID = -1;
	public:
		/*! Creates a new Window with default values */
		Window() : Window("G-Renderer Window Instance", { 50, 50 }, { 1280,  720 }) {}
		/**
		 * Creates a new window and enables input for it
		 * @param name - The name of the window to be displayed
		 * @param pos - The Position in screen space of the upper left corner
		 * @param dim - The dimension of the whole window
		 */
		Window(std::string name, GGeneral::Point<int> pos, GGeneral::Dimension<int> dim);

		/**
		 * TODO
		 */
		void static init();

		/**
		 * TODO
		 */
		bool initOpenGLContext();

		/**
		 * TODO
		 */
		void setOpenGLContextActive(bool b);

		void swapBuffers();

		/**
		 * Set the extended window state of the window instance. Is used to change the visibility of the window.
		 * @param state - The new State the window should take
		 */
		void setState(GWindow::WindowState state);

		/**
		 * Will retrieve all messages/events from the current queue from all Windows. It can only process all events from every window instance used owned/constructed from the current thread
		 */
		static void fetchEvents();

		/**
		 * Will fetch if there is a close request for the current window
		 * @return True if there is one. Otherwise it will return false
		 */
		const bool getCloseRequest() const;

		/**
		 * Will immediately sent a close request to the Window and wait until it processed it.
		 */
		void forceCloseRequest();

		/**
		 * TODO
		 * Will set the Mouse capture flag to true or false. If the mouse is captured, it cannot exit the window while the window has the focus. The mouse itself will be invisible and in a virtual window space
		 * @param capture - Set the capture
		 */
		void setCaptureMouseMode(bool capture);

		/**
		 * TODO
		 * Will fetch the current window state and return it
		 *
		 * @return The current Window state of the window
		 */
		WindowState getCurrentWindowState() const;

		/**
		 * TODO
		 *
		 */
		void addCallbackFunction(GWindowCallback fun);
	};

	/*! This namespace contains all important functions for getting informations of all virtual monitors. The init() function must be called before any other functions. if init() is not called before any other functions they will return 0*/
	namespace Monitor {
		/*! A struct containing all informations of a virtual monitor*/
		struct Screen {
			//Name of the screen
			std::string screenName;
			//The digital Position of the Screen relative to the primary Monitor
			GGeneral::Point<int> digitalPosition;
			//The Resolution of the Monitor
			GGeneral::Dimension<int> screenDimension;
			//The size the digital coordinate system.
			GGeneral::Dimension<int> workDimension;

			/**
			 * Creates a new Screen struct with given values
			 * @param name - The screenName
			 * @param pos - The digitalPosition
			 * @param sdim - The screenDimension
			 * @param wdim - The workDimension
			 */
			Screen(std::string name = "", GGeneral::Point<int> pos = { 0,0 }, GGeneral::Dimension<int> sdim = { 0,0 }, GGeneral::Dimension<int> wdim = {}) : screenName(name), digitalPosition(pos), screenDimension(sdim), workDimension(wdim) {}

			/**
			 * @return A string representing the Screen struct
			 */
			const std::string toString() const {
				return "[name: '" + screenName + "', digitalPos: " + digitalPosition.toString() + ", resolution: " + screenDimension.toString() + ", workDimension " + workDimension.toString() + "]";
			}
		};

		/**
		 * Fetches all Monitor Informations. Needs to be called before calling any other functions
		 *
		 * @return True if no error occurs
		 * @return False if an error occurs
		 */
		bool init();

		/**
		 * Returns a bool
		 *
		 * @return True if the information is already fetched
		 * @return False if the information is not fetched or an error occurred
		 */
		const bool isInit();

		/*
		 * Returns a screen struct with the information of the primary Monitor
		 *
		 * @returns a Screen struct
		 */
		Screen const* getPrimaryMonitorInformation();

		/**
		 * @return an integer with the amount of virtual monitors
		 */
		const unsigned int getAmountOfMonitors();

		/**
		 * @return the index of the primary monitor
		 */
		const unsigned int getPrimaryMonitorIndex();

		/**
		 * Will return the information of the monitor with the given index.
		 *
		 * @return a monitor struct
		 */
		Screen const* getMonitorInformation(unsigned int i);
	}

	/*! This namespace can be used to change some OS depending options */
	namespace OS {
		void moveMouse(GGeneral::Point<int> pos);
	}
}

/**
 * This namespace holds just one function called enumToString. It's sole purpose is to take any Enum defined in the Renderer and return a string representing the name of the enum.
 */
namespace GEnumString {
#define CHECK_ENUM(x) typeid(decltype(GEnum)) == typeid(x)
	/**
	 * This function will take in any enum defined in the renderer and return its corresponding string. Note that this function is not type safe. If any other enums or values are passed in, it will just return "UNKNOWN ENUM"
	 *
	 *  @param GEnum - Any Enum defined in the renderer
	 *  @return A string with the same name as the Enum
	 */
	template<typename E>
	std::string enumToString(E GEnum) {
		auto enumMember = (int)GEnum;

		if (CHECK_ENUM(GGeneral::Logger::Severity)) {
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

		if (CHECK_ENUM(GWindow::WindowState)) {
			auto sev = (GWindow::WindowState) enumMember;
			switch (sev) {
			case GWindow::WindowState::HIDDEN:                          return "HIDDEN";
			case GWindow::WindowState::MAXIMIZED:						return "MAXIMIZED";
			case GWindow::WindowState::MINIMIZED:						return "MINIMIZED";
			case GWindow::WindowState::NORMAL:							return "NORMAL";
			}
		}

		if (CHECK_ENUM(GWindow::VK)) {
			auto vk = (GWindow::VK)enumMember;
			switch (vk) {
			case GWindow::VK::LEFT_MB:		           return "Left Mouse Button";
			case GWindow::VK::RIGHT_MB:		           return "Right Mouse Button";
			case GWindow::VK::CANCEL:		           return "Cancel Key";
			case GWindow::VK::MIDDLE_MB:		       return "Middle Mouse Button";
			case GWindow::VK::X1_MB:			       return "X1 Mouse Button";
			case GWindow::VK::X2_MB:			       return "X2 Mouse Button";
			case GWindow::VK::LEFT_SHIFT:	           return "Left Shift";
			case GWindow::VK::RIGHT_SHIFT:	           return "Right Shift";
			case GWindow::VK::LEFT_CONTROL:	           return "Left Control";
			case GWindow::VK::RIGHT_CONTROL:	       return "Right Control";
			case GWindow::VK::BACKSPACE:		       return "Backspace";
			case GWindow::VK::TAB:			           return "Tab";
			case GWindow::VK::ENTER:			       return "Enter";
			case GWindow::VK::ALT:			           return "Alt";
			case GWindow::VK::PAUSE:			       return "Pause";
			case GWindow::VK::CAPSLOCK:		           return "Capslock";
			case GWindow::VK::ESCAPE:		           return "Escape";
			case GWindow::VK::SPACE:			       return "Space";
			case GWindow::VK::PAGE_UP:		           return "Page Up";
			case GWindow::VK::PAGE_DOWN:		       return "Page Down";
			case GWindow::VK::END:			           return "End";
			case GWindow::VK::HOME:			           return "Home";
			case GWindow::VK::LEFTARROW:		       return "Left Arrow";
			case GWindow::VK::UPARROW:		           return "Up Arrow";
			case GWindow::VK::RIGHTARROW:	           return "Right Arrow";
			case GWindow::VK::DOWNARROW:		       return "Down Arrow";
			case GWindow::VK::SELECT:		           return "Select";
			case GWindow::VK::PRINT:			       return "Print";
			case GWindow::VK::EXECUTE:		           return "Execute";
			case GWindow::VK::PRINT_SCREEN:	           return "Print Screen";
			case GWindow::VK::INSERT:		           return "Insert";
			case GWindow::VK::DEL:			           return "Delete";
			case GWindow::VK::HELP:			           return "Help";
			case GWindow::VK::KEY_0:			       return "0";
			case GWindow::VK::KEY_1:			       return "1";
			case GWindow::VK::KEY_2:			       return "2";
			case GWindow::VK::KEY_3:			       return "3";
			case GWindow::VK::KEY_4:			       return "4";
			case GWindow::VK::KEY_5:			       return "5";
			case GWindow::VK::KEY_6:			       return "6";
			case GWindow::VK::KEY_7:			       return "7";
			case GWindow::VK::KEY_8:			       return "8";
			case GWindow::VK::KEY_9:			       return "9";
			case GWindow::VK::A:				       return "A";
			case GWindow::VK::B:				       return "B";
			case GWindow::VK::C:				       return "C";
			case GWindow::VK::D:				       return "D";
			case GWindow::VK::E:				       return "E";
			case GWindow::VK::F:				       return "F";
			case GWindow::VK::G:				       return "G";
			case GWindow::VK::H:				       return "H";
			case GWindow::VK::I:				       return "I";
			case GWindow::VK::J:				       return "J";
			case GWindow::VK::K:				       return "K";
			case GWindow::VK::L:				       return "L";
			case GWindow::VK::M:				       return "M";
			case GWindow::VK::N:				       return "N";
			case GWindow::VK::O:				       return "O";
			case GWindow::VK::P:				       return "P";
			case GWindow::VK::Q:				       return "Q";
			case GWindow::VK::R:				       return "R";
			case GWindow::VK::S:				       return "S";
			case GWindow::VK::T:				       return "T";
			case GWindow::VK::U:				       return "U";
			case GWindow::VK::V:				       return "V";
			case GWindow::VK::W:				       return "W";
			case GWindow::VK::X:				       return "X";
			case GWindow::VK::Y:				       return "Y";
			case GWindow::VK::Z:				       return "Z";
			case GWindow::VK::LEFT_WINDOWS:	           return "Left Windows";
			case GWindow::VK::RIGHT_WINDOWS:	       return "Right Windows";
			case GWindow::VK::APPLICATION:	           return "Application";
			case GWindow::VK::SLEEP:			       return "Sleep";
			case GWindow::VK::SCROLL_LOCK:	           return "Scroll Lock";
			case GWindow::VK::LEFT_MENU:		       return "Left Alt";
			case GWindow::VK::RIGHT_MENU:	           return "Right Alt";
			case GWindow::VK::VOLUME_MUTE:	           return "Volume Mute";
			case GWindow::VK::VOLUME_DOWN:	           return "Volume Down";
			case GWindow::VK::VOLUME_UP:		       return "Volume Up";
			case GWindow::VK::MEDIA_NEXT:	           return "Media Next Track";
			case GWindow::VK::MEDIA_LAST:	           return "Media Previous Track";
			case GWindow::VK::MEDIA_STOP:	           return "Media Stop";
			case GWindow::VK::MEDIA_PLAY_PAUSE:        return "Media Pause / Play";
			case GWindow::VK::OEM_1:			       return "Oem 1";
			case GWindow::VK::OEM_2:			       return "Oem 2";
			case GWindow::VK::OEM_3:			       return "Oem 3";
			case GWindow::VK::OEM_4:			       return "Oem 4";
			case GWindow::VK::OEM_5:			       return "Oem 5";
			case GWindow::VK::OEM_6:			       return "Oem 6";
			case GWindow::VK::OEM_7:			       return "Oem 7";
			case GWindow::VK::OEM_8:			       return "Oem 8";
			case GWindow::VK::OEM_CLEAR:		       return "Clear";
			case GWindow::VK::OEM_PLUS:		           return "Plus";
			case GWindow::VK::OEM_COMMA:		       return "Comma";
			case GWindow::VK::OEM_MINUS:		       return "Minus";
			case GWindow::VK::OEM_PERIOD:	           return "Period";
			case GWindow::VK::NUMPAD_0:		           return "Numpad 0";
			case GWindow::VK::NUMPAD_1:		           return "Numpad 1";
			case GWindow::VK::NUMPAD_2:		           return "Numpad 2";
			case GWindow::VK::NUMPAD_3:		           return "Numpad 3";
			case GWindow::VK::NUMPAD_4:		           return "Numpad 4";
			case GWindow::VK::NUMPAD_5:		           return "Numpad 5";
			case GWindow::VK::NUMPAD_6:		           return "Numpad 6";
			case GWindow::VK::NUMPAD_7:		           return "Numpad 7";
			case GWindow::VK::NUMPAD_8:		           return "Numpad 8";
			case GWindow::VK::NUMPAD_9:		           return "Numpad 9";
			case GWindow::VK::NUMPAD_MULTIPLY:         return "Numpad Multiply";
			case GWindow::VK::NUMPAD_ADD:	           return "Numpad Add";
			case GWindow::VK::NUMPAD_SEPERATOR:        return "Numpad Seperator";
			case GWindow::VK::NUMPAD_SUBTRACT:         return "Numpad Subtract";
			case GWindow::VK::NUMPAD_COMMA:	           return "Numpad Comma";
			case GWindow::VK::NUMPAD_DIVIDE:	       return "Numpad Divide";
			case GWindow::VK::NUMPAD_LOCK:	           return "Numpad Lock";
			case GWindow::VK::F1:			           return "F1";
			case GWindow::VK::F2:			           return "F2";
			case GWindow::VK::F3:			           return "F3";
			case GWindow::VK::F4:			           return "F4";
			case GWindow::VK::F5:			           return "F5";
			case GWindow::VK::F6:			           return "F6";
			case GWindow::VK::F7:			           return "F7";
			case GWindow::VK::F8:			           return "F8";
			case GWindow::VK::F9:			           return "F9";
			case GWindow::VK::F10:			           return "F10";
			case GWindow::VK::F11:			           return "F11";
			case GWindow::VK::F12:			           return "F12";
			case GWindow::VK::F13:			           return "F13";
			case GWindow::VK::F14:			           return "F14";
			case GWindow::VK::F15:			           return "F15";
			case GWindow::VK::F16:			           return "F16";
			case GWindow::VK::F17:			           return "F17";
			case GWindow::VK::F18:			           return "F18";
			case GWindow::VK::F19:			           return "F19";
			case GWindow::VK::F20:			           return "F20";
			case GWindow::VK::F21:			           return "F21";
			case GWindow::VK::F22:			           return "F22";
			case GWindow::VK::F23:			           return "F23";
			case GWindow::VK::F24:			           return "F24";
			case GWindow::VK::PLAY:			           return "Play";
			case GWindow::VK::ZOOM:			           return "Zoom";
			case GWindow::VK::UNKWON:                  return "Unknown Key";
			}
		}

		return "UNKNOWN ENUM";
	}
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const GGeneral::Dimension<T>& p) {
	os << p.toString();
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const GGeneral::Point<T>& p) {
	os << p.toString();
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const GWindow::Monitor::Screen& p) {
	os << p.toString();
	return os;
}
