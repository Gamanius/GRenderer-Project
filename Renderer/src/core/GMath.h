#pragma once

#include <cmath>

/*! Just a typedef so the code is better to read */
typedef unsigned char byte;

#define A_OPERATION(type, op)                                                      \
							  type <T> returnValue;                                \
							  for (unsigned int i = 0; i < this->getVectorAmount(); i++) \
							  {                                                    \
							    returnValue[i] = this->operator[](i) + a[i];             \
							  }                                                    \
							  return returnValue;

#define A_OPERATION_BODY(type, op)         \
type <T> operator op (const type <T>& a) { \
	A_OPERATION(type, op);                 \
}

/**
 * The approx value of Pi used in this renderer
 */
#define G_PI 3.14159265359f;

#define TO_RAD(deg) deg * (G_PI / 180.0f)
#define TO_DEG(rad) rad * (180.0f / G_PI);

 /**
  * This namespace includes the most important OpenGL math functions needed. It can be also used outside the engine and/or without OpenGL.
  * The Renderer doesn't need to be initialized to use the functions
  */
namespace GMath {
	//Some definitions
	template<typename T>
	struct vec2;
	template<typename T>
	struct vec3;
	template<typename T>
	struct vec4;

	/**
	 * Simple vector with two members. Can be used to set a uniform in a shader
	 */
	template<typename T>
	struct vec2 {
	private:
		/** Amount of values */
		byte size;
		virtual byte getVectorAmount() const { return size; };
		friend struct vec3<T>;
		friend struct vec4<T>;
	public:
		/** The first value */
		T x;
		/** The second value */
		T y;

		/**
		 * Creates a new Vector with given values
		 * @param x - the first value
		 * @param y - the second value
		 */
		vec2(T x, T y) : x(x), y(y), size(2) {}

		/**
		 * Creates a new vector with all values being x
		 * @param x - All values to be set
		 */

		vec2(T x) : x(x), y(x), size(2) {}

		/**
		 * Creates a new vector with all values being 0
		 */
		vec2() : vec2(0) {}

		/**
		 * Return the value of the given index
		 * @param i - the index. Is not allowed to be lower than 0 or higher than 1
		 * @return The value
		 */
		virtual T& operator[](const byte i) {
			auto mem = &x;
			mem += i;
			return *mem;
		}

		/**
		 * Return the value of the given index
		 * @param i - the index. Is not allowed to be lower than 0 or higher than 1
		 * @return The value
		 */
		virtual const T& operator[](const byte i) const {
			auto mem = &x;
			mem += i;
			return *mem;
		}

		/** Plus operation */
		A_OPERATION_BODY(vec2, +);
		/** Minus operation */
		A_OPERATION_BODY(vec2, -);
		/** Multiply operation */
		A_OPERATION_BODY(vec2, *);
		/** Divide operation */
		A_OPERATION_BODY(vec2, / );

		/**
		 * Compares the current vector with another one
		 * @param a - The other vector
		 * @return true - If all values match
		 * @return false - If one or more don't match
		 */
		virtual bool operator==(const vec2<T>& a) {
			for (unsigned int i = 0; i < getVectorAmount(); i++) {
				if (operator[](i) != a[i])
					return false;
			}
			return true;
		}

		/**
		 * Compares the current vector with another one
		 * @param a - The other vector
		 * @return true - If one or more don't match
		 * @return false - If all values match
		 */
		virtual bool operator!=(const vec2<T>& a) {
			for (unsigned int i = 0; i < getVectorAmount(); i++) {
				if (operator[](i) != a[i])
					return true;
			}
			return false;
		}

		/**
		 * Returns a pointer to the memory address of the saved values
		 * @return
		 */
		virtual T* memadd() { return &x; }
	};

	/**
	 * Simple vector with three members. Can be used to set a uniform in a shader
	 */
	template<typename T>
	struct vec3 : public vec2<T> {
		/** The third value */
		T z;

		/**
		 * Creates a new Vector with given values
		 * @param x - the first value
		 * @param y	- the second value
		 * @param z - the third value
		 */
		vec3(T x, T y, T z) : vec2<T>(x, y), z(z) {
			this->size = 3;
		}

		/**
		 * Creates a new vector with all values being x
		 * @param x - All values to be set
		 */
		vec3(T x) : vec2<T>(x), z(x) {
			this->size = 3;
		}

		/**
		 * Creates a new vector with all values being 0
		 */
		vec3() : vec3(0) {}

		/** Plus operation */
		A_OPERATION_BODY(vec3, +);
		/** Minus operation */
		A_OPERATION_BODY(vec3, -);
		/** Multiply operation */
		A_OPERATION_BODY(vec3, *);
		/** Divide operation */
		A_OPERATION_BODY(vec3, / );
	};

	/**
	 * Simple vector with four members. Can be used to set a uniform in a shader
	 */
	template<typename T>
	struct vec4 : public vec3<T> {
		/**
		 * The fourth value
		 */
		T w;

		/**
		 * Creates a new Vector with given values
		 * @param x - the first value
		 * @param y	- the second value
		 * @param z - the third value
		 * @param w - the fourth value
		 */
		vec4(T x, T y, T z, T w) : vec3<T>(x, y, z), w(w) {
			this->size = 4;
		}

		/**
		 * Creates a new vector with all values being x
		 * @param x - All values to be set
		 */
		vec4(T x) : vec3<T>(x), w(x) {
			this->size = 4;
		}

		/**
		 * Creates a new vector with all values being 0
		 */
		vec4() : vec4(0) {}

		/** Plus operation */
		A_OPERATION_BODY(vec4, +);
		/** Minus operation */
		A_OPERATION_BODY(vec4, -);
		/** Multiply operation */
		A_OPERATION_BODY(vec4, *);
		/** Divide operation */
		A_OPERATION_BODY(vec4, / );
	};

	/**
	 * A 4x4 Matrix. Comloum Major
	 */
	template<typename T>
	struct mat4x4 {
		vec4<T> x;
		vec4<T> y;
		vec4<T> z;
		vec4<T> w;

		vec4<T>& operator[](byte i) {
			auto mem = &x;
			mem += i;
			return *mem;
		}

		mat4x4() {
			x = vec4<T>(0);
			y = vec4<T>(0);
			z = vec4<T>(0);
			w = vec4<T>(0);
		}

		template<typename V>
		void translate(vec3<V> dir) {
			operator[](0)[3] += dir[0];
			operator[](1)[3] += dir[1];
			operator[](2)[3] += dir[2];
		}

		/**
		 * Creates an array containing all values and return the memory address
		 * @return The memory address
		 */
		T* memadd() const {
			static T copy[16];
			for (unsigned int i = 0; i < 4; i++) {
				copy[i] = x[i];
				copy[i + 4] = y[i];
				copy[i + 8] = z[i];
				copy[i + 12] = w[i];
			}
			return &copy[0];
		}
	};

	/**
	 * Creates a new Identity Matrix 4x4
	 * @return a mat4x4
	 */
	template<typename T>
	mat4x4<T> mat4x4Identity() {
		mat4x4<T> returnValue;
		returnValue[0][0] = 1;
		returnValue[1][1] = 1;
		returnValue[2][2] = 1;
		returnValue[3][3] = 1;
		return returnValue;
	}
}

#undef A_OPERATION
#undef A_OPERATION_BODY