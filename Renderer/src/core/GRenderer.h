#pragma once
#pragma comment(lib, "opengl32.lib")

#include <initializer_list>
#include <vector>

#include "GMath.h"
#pragma warning(disable : 4595)
#include "GMemory.h"

#ifndef G_RENDERER
#define G_RENDERER
#endif // !G_RENDERER

//Documentation can be (and is) created using doxygen

/** \mainpage <strong>The SREP </strong>
 *  <p> This project is just a simple a try to create a Renderer that can, given the right data, make some beautiful pictures.The hope is that it can be used to create simple games and visualizations.The Renderer can only be used on Windows machines because of the inclusion of the <em>Win32</em> API. </p>
 */

 /**
  * This namespace holds all function, namespaces, structs and classes that are not directly part of the Renderer but still integrated. Meaning with a rewrite the Renderer would still work but with the expense that everything is more or less unreadable and
  * very untidy.
  */
namespace GGeneral {
	struct BaseObject;
	class String {
	private:
		/** Amount of chars without \0!! */
		size_t size;
		size_t bytesize;
		char* buffer;
		bool precise = false;
	public:
		//TODO fix this
		static const size_t npos = SIZE_MAX;

		/** Creates an empty string */
		String();
		/**
		 * Will copy the const char* into an internal buffer.
		 * @param c - The content of the String
		 */
		String(const char* c);
		/**
		 * Will copy the char* into an internal buffer
		 * @param c - The content of the String
		 */
		String(const unsigned char* c);
		/**
		 * Will allocate memory with the given size. May be useful if know how much chars are going to be appended.
		 * @param size - The size of the buffer
		 */
		String(size_t size);
		/**
		 * Move constructor
		 * @param other - The other string
		 */
		String(String&& other) noexcept;
		/**
		 * Copy constructor. Will not copy the memory address. It will allocated the size of the other buffer!
		 * @param other - The other string
		 */
		String(const String& other);

		/**
		 * Will append the chars given. If buffer is not big enough it will allocate a new one.
		 * @param c - The chars to append
		 * @return this string
		 */
		String& append(const char* c);
		/**
		 * Will call the toString() method and append the chars given. If buffer is not big enough it will allocate a new one.
		 * @param obj - The object to append
		 * @return this string
		 */
		String& append(BaseObject& obj);

		/**
		 * @param i - The index
		 * @return The char at this position
		 */
		char operator[](size_t i);
		/**
		 * Will just copy the String
		 * @param s - The other string
		 * @return A copy of the other string
		 */
		String& operator=(const String& s);
		/**
		 * Will just copy the String
		 * @param s - The other string
		 * @return A copy of the other string
		 */
		String& operator=(String&& other) noexcept;

		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const String& s, const String& s2);
		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const String& s, const char* c);
		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const char* c, const String& s);
		/**
		 * Will just call append
		 * @param c - The chars to append
		 * @return this string
		 */
		String& operator+=(const char* c);

		/**
		 * Will just call append
		 * @param c - The chars to append
		 * @return this string
		 */
		String& operator<< (const char* c);
		/**
		 * Will just call append
		 * @param s - The string to append
		 * @return this string
		 */
		String& operator<< (const String& s);
		/**
		 * Will just call append
		 * @param c - The obj to append
		 * @return this string
		 */
		String& operator<< (const BaseObject& obj);
		String& operator<< (const void* adress);
		/**
		 * Will format the number into a char* and will then call append
		 * @param b - The number to append
		 * @return this string
		 */
		String& operator<< (const byte b);
		/**
		 * Will format the number into a char* and will then call append
		 * @param i - The number to append
		 * @return this string
		 */
		String& operator<< (const int i);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui64 - The number to append
		 * @return this string
		 */
		String& operator<< (uint64_t ui64);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui32 - The number to append
		 * @return this string
		 */
		String& operator<< (uint32_t ui32);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui16 - The number to append
		 * @return this string
		 */
		String& operator<< (uint16_t ui16);

		/**
		 * Will set the precise flag. If the precise flag is set to true the string will be the most memory efficient. Every time something is append the buffer will only allocate just enough space for the chars given.
		 * If this flag is set to false the buffer will always allocate more space than needed for better performance.
		 * @param b The new precise flag
		 */
		void setPrecise(const bool b);

		/**
		 * Will search for the first occurrence of the string
		 * @param c - The string to search for
		 * @return The index if find is successful or npos if nothing has been found
		 */
		size_t find(const char* c);
		/**
		 * Will compare both string
		 * @param c - The char to compare with
		 * @return true - If the comparison was successful
		 * @return false - If the comparison was not successful
		 */
		bool compare(const char* c);
		/**
		 * Will erase part of the string.
		 * @param beginning - The starting index
		 * @param offset - The amount of chars to be deleted
		 * @return this string
		 */
		String& erase(size_t beginning, size_t offset);

		/**
		 * Will return the memory address of this buffer
		 * @return the memory address
		 */
		const char* cStr() const;
		/**
		 * Will return the size of the string without the null termination char
		 * @return The size
		 */
		const size_t getSize() const;

		/**
		 * @return The memory address of the buffer
		 */
		operator const char* () const;
		/**
		 * @param i - The index
		 * @return The char of the index
		 */
		const char operator[] (size_t i) const;

		/** Will delete the buffer */
		~String();
	};
	/**
	 * Will try to convert given argument into a string using stringstream
	 * @param arg - The argument to convert
	 * @return A string
	 */
	template<typename T>
	String toString(T arg) {
		String s;
		s << arg;

		return s;
	}

	/**
	 * Will try to convert given arguments using stringstream into a string
	 * @param arg - The first needed argument
	 * @param ...args - More arguments
	 * @return A combined string of all arguments
	 */
	template<typename T_FIRST, typename... T_MORE>
	String toString(T_FIRST arg, T_MORE... args) {
		String returnValue;
		returnValue += toString(arg);
		returnValue += toString(args...);
		return returnValue;
	}

	/** Every struct whose will inherit from this struct */
	struct BaseObject {
		virtual GGeneral::String toString() const = 0;
	};

	/**
	 * A struct containing Red Green and Blue values
	 */
	struct Color : public GGeneral::BaseObject {
		/** The red component */
		byte red;
		/** The green component */
		byte green;
		/** The blue component */
		byte blue;

		/**
		 * Creates a new Color struct with given values
		 * @param red - The red value
		 * @param green - The green value
		 * @param blue - The blue value
		 */
		Color(byte red = 0, byte green = 0, byte blue = 0);

		/**
		 * Returns the red, green or blue color values depending on the given index. Index may not be higher than 2 nor lower than 0
		 * @param i - The index
		 * @return A color value
		 */
		byte operator[](byte i);

		GGeneral::String toString() const override {
			return PRINT_VAR(red, green, blue);
		}
	};

	/** A namespace containing mostly time functions.*/
	namespace Time {
		/** This struct holds the information of any timepoint */
		struct TimePoint : public GGeneral::BaseObject {
			/** The time since 1980 in nanoseconds(?) */
			unsigned long long int timepoint = 0;
			/** Years since 0 */
			unsigned int year = 0;
			/** Amount of months */
			byte month = 0;
			/** Amount of days */
			byte day = 0;
			/** Amount of hours */
			byte hour = 0;
			/** Amount of minutes */
			byte minute = 0;
			/** Amount of seconds */
			byte seconds = 0;
			/** Amount of milliseconds */
			unsigned int millisecond = 0;
			/** Amount of microseconds */
			unsigned int microsecond = 0;
			/** Amount of nanoseconds */
			unsigned int nanosecond = 0;

			/**
			 * Will return the current timepoint
			 * @return The time since 1980
			 */
			operator unsigned long long int() {
				return timepoint;
			}

			GGeneral::String toString() const override {
				return PRINT_VAR(timepoint, year, month, day, hour, minute, seconds, millisecond, microsecond, nanosecond);
			}
		};

		/** Will return true if the year was a leap year */
		const bool isLeapYear(TimePoint& point);
		/** Will return true if the year was a leap year */
		const bool isLeapYear(const unsigned int year);

		/** On construction it will start an internal timer. If the stop method is called the timer will return the time sice its construction */
		struct Timer {
			/** The time the Time was constructed in nanoseconds */
			unsigned long long int startTime;
			/** Will start the timer */
			Timer();
			/**
			 * Will calculate the time since construction of this struct and return the time in nanoseconds
			 * @return The time sice constuction in nanoseconds
			 */
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
			GGeneral::String msg;
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
			String s;
			s << message;
			printMessage({ s, sev, ID });
		}

		/**
		 * Adds a new user name to the Logger. The int can be used in the printMessage() function to print the user name given. Every thread can use any User ID. there is no checking.
		 *
		 * @return The ID of the name
		 */
		int addUserName(GGeneral::String name);

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
	struct Dimension : public GGeneral::BaseObject {
		/*! The width component of the Dimension */
		T width;
		/*! The height component of the Dimension */
		T height;
		/*! Creates a new Dimension with the given width and height. The type is up to the user but floats and doubles are recommended. Default values are 0 */
		Dimension(T w = 0, T h = 0) : width(w), height(h) {}

		/**
		 * @return A string with the current values of the Dimension struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(width, height);
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
		GGeneral::String toString() const override {
			return PRINT_VAR(this->width, this->height, depth);
		}
	};

	/**
	 * A struct containing two values representing a point in 2D space.
	 */
	template<typename T>
	struct Point : public GGeneral::BaseObject {
		/*! The x coordinate*/
		T x;
		/*! The y coordinate*/
		T y;
		/*! Creates a new Point with the given coordinates. The type is up to the user but floats and doubles are recommended. Default values are 0*/
		Point(T x = 0, T y = 0) : x(x), y(y) {}

		/**
		 * @return A string with the current values of the Point struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(x, y);
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
		GGeneral::String toString() const override {
			return PRINT_VAR(this->x, this->y, z);
		}
	};

	/**
	 * This namespace contains some Win32 API calls that dont fit the GWindow namespace.
	 */
	namespace OS {
		/**
		 * Will fetch the current computer name and return it
		 * @returns The computer name
		 */
		GGeneral::String getComputerName();

		/**
		 * Will fetch the current user name and return it
		 * @returns The user name
		 */
		GGeneral::String getUserName();

		/**
		 * Will move the mouse cursor to the given screen space coordinates. Please note that the cursor is a shared recourse.
		 * @param newPos - The new position of the cursor
		 */
		void moveMouse(GGeneral::Point<int> newPos);
	}
}

/**
 * A namespace containing all function around file loading and reading.
 */
namespace GIO {
	/**
	 * A struct containing the most important information about a file. All classes that are loading in files should derive from it
	 */
	struct File : public GGeneral::BaseObject {
		/**
		 * The data of the file
		 */
		byte* data = nullptr;
		/**
		 * The size of data in bytes
		 */
		unsigned int size = 0;

		File() {}

		File(byte* data, unsigned int size) : data(data), size(size) {}

		/**
		 * Returns the data of the given index. The index may not be higher than the size nor lower than 0
		 * @param i -  The index
		 * @return The data
		 */
		virtual byte operator[](unsigned int i) {
			return data[i];
		}

		GGeneral::String toString() const override {
			return PRINT_VAR(size);
		}

		/** Deletes all data allocated */
		~File() { delete[] data; }
	};

	/**
	 * Loads in the file and return the file size. If an error occurs the returned value is 0
	 * @returns The file size in bytes
	 */
	unsigned long long int getFileSize(GGeneral::String& filepath);

	/**
	 * Will create a file, load and allocated the memory for the data. If an error occurs the returned value will be a nullptr
	 * @returns A Pointer to a file struct
	 */
	File* loadFile(GGeneral::String filepath);

	/**
	 * Fetches and returns the filepath of the executable
	 * @returns The file path of the .exe file
	 */
	GGeneral::String getWorkingDirectionary();

	/**
	 * This namespace contains all functions to load in images
	 */
	namespace Graphics {
		/**
		 * A struct containing information about a image. The data will always be:
		 * RED, GREEN, BLUE, (if available) ALPHA
		 */
		struct Image : public File {
			/**
			 * The size of the image
			 */
			GGeneral::Dimension<unsigned int> dim;
			/**
			 * Does the image contain alpha values
			 */

			GGeneral::String toString() const override {
				return PRINT_VAR(this->size, dim);
			}
			bool hasAlpha = false;
		};
		/**
		 * Check if there is an implementation to load the image. Will return false if an error occurs
		 * @return true - The image can be parsed
		 * @return false - An error occurred and/or the image cannot be parsed
		 */
		bool isParseble(GGeneral::String& filepath);
		/**
		 * Check if there is an implementation to load the image. Will return false if an error occurs
		 * @return true - The image can be parsed
		 * @return false - An error occurred and/or the image cannot be parsed
		 */
		bool isParseble(byte* data);

		/**
		 * Will check if the image can be parsed. If the image can be parse it will load in the image, parse it and return a pointer to a created image struct with all information about the image
		 * @returns If successful a image struct
		 */
		Image* loadImage(GGeneral::String filepath);
	}
}

namespace GRenderer {
	/**
	 * Will initialize the renderer
	 */
	const bool init();
	/**
	 * Fetches the current OpenGL Version
	 */
	GGeneral::String getCurentOpenGLVersion();

	/**
	 * Clears the current active OpenGL context with the given color
	 */
	void clear(GGeneral::Color& color);

	//definition for shaderprogram so friendships work
	class ShaderProgram;
	namespace Primitives {
		/**
		 * The type used by the IndexBuffer. No other types are allowed
		 */
		enum class IndexTypes {
			UNSIGNED_BYTE, UNSIGNED_SHORT, UNSIGNED_INT
		};

		/**
		 * The type used of the VertexBuffer. Other types can be used if the size of the type is the same like one of the given onces
		 */
		enum class VertexTypes {
			BYTE, SHORT, INT, FLOAT, DOUBLE
		};

		/**
		 * Class wrapper for the OpenGL IndexBuffer
		 */
		struct IndexBuffer {
		private:
			unsigned int amount;
			IndexTypes element;
			/**
			 * Internal OpenGL ID
			 */
			unsigned int ID;
		public:
			IndexBuffer() = default;

			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(unsigned int data[], unsigned int amount);
			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(byte data[], unsigned int amount);
			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(unsigned short data[], unsigned int amount);

			/**
			 * Deletes the IndexBuffer
			 */
			~IndexBuffer();

			/**
			 * Binds the current IndexBuffer
			 */
			void bind();
			/**
			 * Unbind the current IndexBuffer
			 */
			void unbind();

			friend struct VertexArray;
		};

		/**
		 * Class wrapper for the OpenGL VertexBuffer
		 */
		struct VertexBuffer {
		private:
			/**
			 * Internal OpenGL ID
			 */
			unsigned int ID;
			unsigned int amount = 0;

		public:
			VertexBuffer() = default;
			//TODO: correct documentation
			/**
			 * Creates a new VertexBuffer
			 * @param data - All the data
			 * @param amount - !PLEASE CHECK THIS IS NOT CORRECT! The amount of values to be used
			 */
			VertexBuffer(char data[], unsigned int amount, unsigned int count);
			/**
			 * Creates a new VertexBuffer
			 * @param data - All data
			 * @param amount - The amount of values to be used
			 */
			VertexBuffer(short data[], unsigned int amount, unsigned int count);
			/**
			 * Creates a new VertexBuffer
			 * @param data - All data
			 * @param amount - The amount of value to be used
			 */
			VertexBuffer(int data[], unsigned int amount, unsigned int count);
			/**
			 * Creates a new VertexBuffer
			 * @param data - All data
			 * @param amount - The amount of value to be used
			 */
			VertexBuffer(float data[], unsigned int amount, unsigned int count);
			/**
			 * Creates a new VertexBuffer
			 * @param data - All data
			 * @param amount - The amount of value to be used
			 */
			VertexBuffer(double data[], unsigned int amount, unsigned int count);
			/**
			 * Deletes the VertexBuffer
			 */
			~VertexBuffer();

			/**
			 * Binds the current VertexBuffer
			 */
			void bind();
			/**
			 * Unbinds the curernt VertexBuffer
			 */
			void unbind();

			friend struct VertexArray;
		};

		/**
		 * Class wrapper and manager for the OpenGL VertexArray class
		 */
		struct VertexArray {
			/**
			 * A struct that hold the information about the layout of any VertexBuffer. Is most likely needed for the VertexArray construction
			 */
			struct VertexArrayLayout {
			private:
				std::vector<byte> layout;
				byte size;
			public:
				VertexArrayLayout() = default;
				/**
				 * Creates a new VertexArrayLayout. This is used for the VertexArray to identify how big the VertexBuffer is and how many elements it has
				 * @param data - All elements e.g.: {3, 2, 1}
				 * @param type - The type of the VertexBuffer used
				 */
				VertexArrayLayout(std::initializer_list<byte> data, VertexTypes type);

				/**
				 * Calculates the Stride
				 * @return The stride
				 */
				const unsigned int getStride() const;

				/**
				 * Calculates the offset of the given element index
				 * @param index - The element
				 * @return The offset
				 */
				const unsigned int getOffset(const unsigned int index) const;

				friend struct VertexArray;
			};
		private:
			bool isOnlyVertexBuffer = false;
			unsigned int amount;
			IndexTypes type = IndexTypes::UNSIGNED_BYTE;
			/**
			 * Internal OpenGL ID
			 */
			unsigned int ID;

		public:
			VertexArray();
			/**
			 * Creates a new VertexArray Object.
			 * @param vertex - The vertexes used by the VertexArray
			 * @param index - The indexes used by the VertexArray
			 * @param layout - The layout of the VertexBuffer
			 */
			VertexArray(VertexBuffer vertex, IndexBuffer index, VertexArrayLayout layout);

			VertexArray(VertexBuffer vertex, VertexArrayLayout layout);

			~VertexArray();

			/**
			 * Binds the current VertexArray
			 */
			void bind();
			/**
			 * Unbinds the current VertexArray
			 */
			void unbind();

			/**
			 * @return True if there is no IndexBuffer in this VertexArray
			 */
			bool isOnlyVertex() const { return isOnlyVertexBuffer; }

			/**
			 * Will return the amount of indexes or the amount of vertexes (to be rendered). The return value will depend if there is an IndexBuffer in this VertexArray (see isOnlyVertex())
			 */
			unsigned int getAmount() const { return amount; }

			IndexTypes getIndexType() const { return type; }
		};

		/**
		 * All possible shaders
		 */
		enum class ShaderTypes {
			COMPUTE_SHADER,          /*! A COMPUTE_SHADER*/
			VERTEX_SHADER,			 /*! A VERTEX_SHADER*/
			TESS_CONTROL_SHADER,	 /*! A TESS_CONTROL_SHADER*/
			TESS_EVALUATION_SHADER,	 /*! A TESS_EVALUATION_SHADER*/
			GEOMETRY_SHADER,		 /*! A GEOMETRY_SHADER*/
			FRAGMENT_SHADER,		 /*! A FRAGMENT_SHADER*/
			UNKOWN_SHADER			 /*! If the shader is unknown or cannot be parsed it is an UNKOWN_SHADER*/
		};

		/**
		 * A class wrapper for an shader
		 */
		class Shader {
		private:
			/**
			 * Internal OpenGL ID
			 */
			unsigned int ID;
			/**
			 * The source code
			 */
			GGeneral::String sourceCode;
			ShaderTypes type = ShaderTypes::UNKOWN_SHADER;
			bool fail = true;
		public:
			/**
			 * Will create an invalid shader
			 */
			Shader() = default;

			/**
			 * Will try to guess the Shader and load it in
			 * @param filepath - The filepath to the shader
			 */
			Shader(GGeneral::String filepath);

			/**
			 * Will load in the shader and set the shader type
			 * @param filepath - The filepath to the shader
			 * @param type - The type of the shader
			 */
			Shader(GGeneral::String filepath, ShaderTypes type);

			~Shader();

			/**
			 * Will load in the shader and try to guess it's type
			 * @param filepath - The filepath to the shader
			 * @return true If successful and no errors occurred
			 * @return false If an error occurred
			 */
			bool loadShader(GGeneral::String filepath);

			/**
			 * Will try to compile the shader
			 * @return true If the shader compilation was successful
			 * @return false If the shader type is not know or and error occurred while trying to compile it
			 */
			bool compileShader();

			/**
			 * @return true If no errors occurred
			 * @return false If an error occurred and the fail bit is set to true
			 */
			bool failed() const;

			/**
			 * Returns an info message of the shader if any errors occurred
			 * @return A string of the info message
			 */
			GGeneral::String getInfoMessage();

			friend class GRenderer::ShaderProgram;
		};
	}

	/**
	 * A class wrapper for OpenGL textures
	 */
	class Texture {
		unsigned int ID;
		unsigned int textureSlot = 0;

	public:
		/**
		 * Default constructor. The texture is invalid
		 */
		Texture() = default;

		Texture(const Texture& t);

		Texture(Texture&& t) noexcept;

		/**
		 * Will create a new Texture with the given image
		 * @param i
		 */
		Texture(GIO::Graphics::Image& i);

		Texture& operator=(const Texture& other);

		Texture& operator=(Texture&& t) noexcept;

		/**
		 * Will create the shader
		 * @param i - The Image to convert to a texture
		 * @return Always true
		 */
		const bool createTexture(GIO::Graphics::Image& i);

		/**
		 * Deconstructor
		 */
		~Texture();

		/**
		 * Will bind the texture to the given texture slot
		 * @param slot - The texture slot to bind to
		 */
		void bind(unsigned int slot);

		/**
		 * Will bind the texture to the last texture slot given
		 */
		void bind();

		void setTextureSlot(unsigned int slot);

		/**
		 * Will unbind the current texture from the texture slot
		 */
		void unbind();
	};

	/**
	 * A class wrapper for a Shader program
	 */
	class ShaderProgram {
	private:
		unsigned int ID;
		std::vector<unsigned int*> shaderIDs;
		bool fail = true;
	public:
		/**
		 * Default shader program constructor. The program is invalid
		 */
		ShaderProgram() = default;
		/**
		 * Will try to link all given shaders and create a shader program
		 * @param shaders - All shaders to bind
		 */
		ShaderProgram(std::initializer_list<Primitives::Shader*> shaders);

		~ShaderProgram();

		/**
		 * Will link the shaders
		 * @return true - If linking was successful
		 * @return false - If an error occured while linking
		 */
		bool link();

		/**
		 * Returns an info message of the shader program if any errors occurred
		 * @return A string of the info message
		 */
		GGeneral::String getInfoMessage();

		/**
		 * Will fetch the uniform location.
		 * @param name - The name of the uniform
		 * @return If successful the location of the uniform
		 */
		const unsigned int getUniformLocation(const GGeneral::String& name) const;

		//TODO: setter

		/**
		 * Will bind the shader program
		 */
		void bind();

		/**
		 * Will unbind the shader program
		 */
		void unbind();

		/**
		 * @return The internal OpenGL Shaderprogram ID
		 */
		unsigned int getID() const { return ID; }
	};

	struct Mesh {
		Texture tex;
		Primitives::VertexArray vertex;
	};

	void draw(Mesh& m);
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
		Window(GGeneral::String name, GGeneral::Point<int> pos, GGeneral::Dimension<int> dim);

		~Window();

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
		struct Screen : public GGeneral::BaseObject {
			/*!Name of the screen*/
			GGeneral::String screenName;
			/*!The digital Position of the Screen relative to the primary Monitor*/
			GGeneral::Point<int> digitalPosition;
			/*!The Resolution of the Monitor*/
			GGeneral::Dimension<int> screenDimension;
			/*!The size the digital coordinate system.*/
			GGeneral::Dimension<int> workDimension;

			/**
			 * Creates a new Screen struct with given values
			 * @param name - The screenName
			 * @param pos - The digitalPosition
			 * @param sdim - The screenDimension
			 * @param wdim - The workDimension
			 */
			Screen(GGeneral::String name = "", GGeneral::Point<int> pos = { 0,0 }, GGeneral::Dimension<int> sdim = { 0,0 }, GGeneral::Dimension<int> wdim = {}) : screenName(name), digitalPosition(pos), screenDimension(sdim), workDimension(wdim) {}

			/**
			 * @return A string representing the Screen struct
			 */
			GGeneral::String toString() const override {
				return PRINT_VAR(screenName, digitalPosition, screenDimension, workDimension);
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

		/**
		 * Will return the maximum amount of supported Monitor devices
		 *
		 * @return The amount of monitors supported by the users GPU
		 */
		const unsigned int getSupportedAmountOfMonitorDevices();
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GGeneral::Logger::Severity e) {
	switch (e) {
	case GGeneral::Logger::Severity::S_MSG:                     return s.append("MESSAGE");
	case GGeneral::Logger::Severity::S_INFO:                    return s.append("INFO");
	case GGeneral::Logger::Severity::S_SUCCESS:                 return s.append("SUCCESS");
	case GGeneral::Logger::Severity::S_WARNING:                 return s.append("WARNING");
	case GGeneral::Logger::Severity::S_ERROR:	                return s.append("ERROR");
	case GGeneral::Logger::Severity::S_FATAL:                   return s.append("FATAL");
	default:													return s.append("UNKNOWN");
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::IndexTypes e) {
	switch (e) {
	case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:	 return s.append("UNSIGNED BYTE");
	case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT:	 return s.append("UNSIGNED SHORT");
	case GRenderer::Primitives::IndexTypes::UNSIGNED_INT:	 return s.append("UNSIGNED INT");
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::VertexTypes e) {
	switch (e) {
	case GRenderer::Primitives::VertexTypes::BYTE:		return s.append("BYTE");
	case GRenderer::Primitives::VertexTypes::SHORT:		return s.append("SHORT");
	case GRenderer::Primitives::VertexTypes::INT:		return s.append("INT");
	case GRenderer::Primitives::VertexTypes::FLOAT:		return s.append("FLOAT");
	case GRenderer::Primitives::VertexTypes::DOUBLE:	return s.append("DOUBLE");
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::ShaderTypes e) {
	switch (e) {
	case GRenderer::Primitives::ShaderTypes::COMPUTE_SHADER:					return s.append("COMPUTE SHADER");
	case GRenderer::Primitives::ShaderTypes::VERTEX_SHADER:						return s.append("VERTEX SHADER");
	case GRenderer::Primitives::ShaderTypes::TESS_CONTROL_SHADER:				return s.append("TESS CONTROL SHADER");
	case GRenderer::Primitives::ShaderTypes::TESS_EVALUATION_SHADER:			return s.append("TESS EVALUATION SHADER");
	case GRenderer::Primitives::ShaderTypes::GEOMETRY_SHADER:					return s.append("GEOMETRY SHADER");
	case GRenderer::Primitives::ShaderTypes::FRAGMENT_SHADER:					return s.append("FRAGMENT SHADER");
	case GRenderer::Primitives::ShaderTypes::UNKOWN_SHADER:						return s.append("UNKOWN SHADER");
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GWindow::WindowState e) {
	switch (e) {
	case GWindow::WindowState::HIDDEN:                          return s.append("HIDDEN");
	case GWindow::WindowState::MAXIMIZED:						return s.append("MAXIMIZED");
	case GWindow::WindowState::MINIMIZED:						return s.append("MINIMIZED");
	case GWindow::WindowState::NORMAL:							return s.append("NORMAL");
	}
}

inline GGeneral::String& operator<<(GGeneral::String& s, GWindow::VK e) {
	switch (e) {
	case GWindow::VK::LEFT_MB:		           return s.append("Left Mouse Button");
	case GWindow::VK::RIGHT_MB:		           return s.append("Right Mouse Button");
	case GWindow::VK::CANCEL:		           return s.append("Cancel Key");
	case GWindow::VK::MIDDLE_MB:		       return s.append("Middle Mouse Button");
	case GWindow::VK::X1_MB:			       return s.append("X1 Mouse Button");
	case GWindow::VK::X2_MB:			       return s.append("X2 Mouse Button");
	case GWindow::VK::LEFT_SHIFT:	           return s.append("Left Shift");
	case GWindow::VK::RIGHT_SHIFT:	           return s.append("Right Shift");
	case GWindow::VK::LEFT_CONTROL:	           return s.append("Left Control");
	case GWindow::VK::RIGHT_CONTROL:	       return s.append("Right Control");
	case GWindow::VK::BACKSPACE:		       return s.append("Backspace");
	case GWindow::VK::TAB:			           return s.append("Tab");
	case GWindow::VK::ENTER:			       return s.append("Enter");
	case GWindow::VK::ALT:			           return s.append("Alt");
	case GWindow::VK::PAUSE:			       return s.append("Pause");
	case GWindow::VK::CAPSLOCK:		           return s.append("Capslock");
	case GWindow::VK::ESCAPE:		           return s.append("Escape");
	case GWindow::VK::SPACE:			       return s.append("Space");
	case GWindow::VK::PAGE_UP:		           return s.append("Page Up");
	case GWindow::VK::PAGE_DOWN:		       return s.append("Page Down");
	case GWindow::VK::END:			           return s.append("End");
	case GWindow::VK::HOME:			           return s.append("Home");
	case GWindow::VK::LEFTARROW:		       return s.append("Left Arrow");
	case GWindow::VK::UPARROW:		           return s.append("Up Arrow");
	case GWindow::VK::RIGHTARROW:	           return s.append("Right Arrow");
	case GWindow::VK::DOWNARROW:		       return s.append("Down Arrow");
	case GWindow::VK::SELECT:		           return s.append("Select");
	case GWindow::VK::PRINT:			       return s.append("Print");
	case GWindow::VK::EXECUTE:		           return s.append("Execute");
	case GWindow::VK::PRINT_SCREEN:	           return s.append("Print Screen");
	case GWindow::VK::INSERT:		           return s.append("Insert");
	case GWindow::VK::DEL:			           return s.append("Delete");
	case GWindow::VK::HELP:			           return s.append("Help");
	case GWindow::VK::KEY_0:			       return s.append("0");
	case GWindow::VK::KEY_1:			       return s.append("1");
	case GWindow::VK::KEY_2:			       return s.append("2");
	case GWindow::VK::KEY_3:			       return s.append("3");
	case GWindow::VK::KEY_4:			       return s.append("4");
	case GWindow::VK::KEY_5:			       return s.append("5");
	case GWindow::VK::KEY_6:			       return s.append("6");
	case GWindow::VK::KEY_7:			       return s.append("7");
	case GWindow::VK::KEY_8:			       return s.append("8");
	case GWindow::VK::KEY_9:			       return s.append("9");
	case GWindow::VK::A:				       return s.append("A");
	case GWindow::VK::B:				       return s.append("B");
	case GWindow::VK::C:				       return s.append("C");
	case GWindow::VK::D:				       return s.append("D");
	case GWindow::VK::E:				       return s.append("E");
	case GWindow::VK::F:				       return s.append("F");
	case GWindow::VK::G:				       return s.append("G");
	case GWindow::VK::H:				       return s.append("H");
	case GWindow::VK::I:				       return s.append("I");
	case GWindow::VK::J:				       return s.append("J");
	case GWindow::VK::K:				       return s.append("K");
	case GWindow::VK::L:				       return s.append("L");
	case GWindow::VK::M:				       return s.append("M");
	case GWindow::VK::N:				       return s.append("N");
	case GWindow::VK::O:				       return s.append("O");
	case GWindow::VK::P:				       return s.append("P");
	case GWindow::VK::Q:				       return s.append("Q");
	case GWindow::VK::R:				       return s.append("R");
	case GWindow::VK::S:				       return s.append("S");
	case GWindow::VK::T:				       return s.append("T");
	case GWindow::VK::U:				       return s.append("U");
	case GWindow::VK::V:				       return s.append("V");
	case GWindow::VK::W:				       return s.append("W");
	case GWindow::VK::X:				       return s.append("X");
	case GWindow::VK::Y:				       return s.append("Y");
	case GWindow::VK::Z:				       return s.append("Z");
	case GWindow::VK::LEFT_WINDOWS:	           return s.append("Left Windows");
	case GWindow::VK::RIGHT_WINDOWS:	       return s.append("Right Windows");
	case GWindow::VK::APPLICATION:	           return s.append("Application");
	case GWindow::VK::SLEEP:			       return s.append("Sleep");
	case GWindow::VK::SCROLL_LOCK:	           return s.append("Scroll Lock");
	case GWindow::VK::LEFT_MENU:		       return s.append("Left Alt");
	case GWindow::VK::RIGHT_MENU:	           return s.append("Right Alt");
	case GWindow::VK::VOLUME_MUTE:	           return s.append("Volume Mute");
	case GWindow::VK::VOLUME_DOWN:	           return s.append("Volume Down");
	case GWindow::VK::VOLUME_UP:		       return s.append("Volume Up");
	case GWindow::VK::MEDIA_NEXT:	           return s.append("Media Next Track");
	case GWindow::VK::MEDIA_LAST:	           return s.append("Media Previous Track");
	case GWindow::VK::MEDIA_STOP:	           return s.append("Media Stop");
	case GWindow::VK::MEDIA_PLAY_PAUSE:        return s.append("Media Pause / Play");
	case GWindow::VK::OEM_1:			       return s.append("Oem 1");
	case GWindow::VK::OEM_2:			       return s.append("Oem 2");
	case GWindow::VK::OEM_3:			       return s.append("Oem 3");
	case GWindow::VK::OEM_4:			       return s.append("Oem 4");
	case GWindow::VK::OEM_5:			       return s.append("Oem 5");
	case GWindow::VK::OEM_6:			       return s.append("Oem 6");
	case GWindow::VK::OEM_7:			       return s.append("Oem 7");
	case GWindow::VK::OEM_8:			       return s.append("Oem 8");
	case GWindow::VK::OEM_CLEAR:		       return s.append("Clear");
	case GWindow::VK::OEM_PLUS:		           return s.append("Plus");
	case GWindow::VK::OEM_COMMA:		       return s.append("Comma");
	case GWindow::VK::OEM_MINUS:		       return s.append("Minus");
	case GWindow::VK::OEM_PERIOD:	           return s.append("Period");
	case GWindow::VK::NUMPAD_0:		           return s.append("Numpad 0");
	case GWindow::VK::NUMPAD_1:		           return s.append("Numpad 1");
	case GWindow::VK::NUMPAD_2:		           return s.append("Numpad 2");
	case GWindow::VK::NUMPAD_3:		           return s.append("Numpad 3");
	case GWindow::VK::NUMPAD_4:		           return s.append("Numpad 4");
	case GWindow::VK::NUMPAD_5:		           return s.append("Numpad 5");
	case GWindow::VK::NUMPAD_6:		           return s.append("Numpad 6");
	case GWindow::VK::NUMPAD_7:		           return s.append("Numpad 7");
	case GWindow::VK::NUMPAD_8:		           return s.append("Numpad 8");
	case GWindow::VK::NUMPAD_9:		           return s.append("Numpad 9");
	case GWindow::VK::NUMPAD_MULTIPLY:         return s.append("Numpad Multiply");
	case GWindow::VK::NUMPAD_ADD:	           return s.append("Numpad Add");
	case GWindow::VK::NUMPAD_SEPERATOR:        return s.append("Numpad Separator");
	case GWindow::VK::NUMPAD_SUBTRACT:         return s.append("Numpad Subtract");
	case GWindow::VK::NUMPAD_COMMA:	           return s.append("Numpad Comma");
	case GWindow::VK::NUMPAD_DIVIDE:	       return s.append("Numpad Divide");
	case GWindow::VK::NUMPAD_LOCK:	           return s.append("Numpad Lock");
	case GWindow::VK::F1:			           return s.append("F1");
	case GWindow::VK::F2:			           return s.append("F2");
	case GWindow::VK::F3:			           return s.append("F3");
	case GWindow::VK::F4:			           return s.append("F4");
	case GWindow::VK::F5:			           return s.append("F5");
	case GWindow::VK::F6:			           return s.append("F6");
	case GWindow::VK::F7:			           return s.append("F7");
	case GWindow::VK::F8:			           return s.append("F8");
	case GWindow::VK::F9:			           return s.append("F9");
	case GWindow::VK::F10:			           return s.append("F10");
	case GWindow::VK::F11:			           return s.append("F11");
	case GWindow::VK::F12:			           return s.append("F12");
	case GWindow::VK::F13:			           return s.append("F13");
	case GWindow::VK::F14:			           return s.append("F14");
	case GWindow::VK::F15:			           return s.append("F15");
	case GWindow::VK::F16:			           return s.append("F16");
	case GWindow::VK::F17:			           return s.append("F17");
	case GWindow::VK::F18:			           return s.append("F18");
	case GWindow::VK::F19:			           return s.append("F19");
	case GWindow::VK::F20:			           return s.append("F20");
	case GWindow::VK::F21:			           return s.append("F21");
	case GWindow::VK::F22:			           return s.append("F22");
	case GWindow::VK::F23:			           return s.append("F23");
	case GWindow::VK::F24:			           return s.append("F24");
	case GWindow::VK::PLAY:			           return s.append("Play");
	case GWindow::VK::ZOOM:			           return s.append("Zoom");
	case GWindow::VK::UNKWON:                  return s.append("Unknown Key");
	}
}