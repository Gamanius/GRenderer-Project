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
							  													 	
#define G_PI 3.14159265359f;

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

	//template<typename T>
	//T toRad(T deg) { return deg * (G_PI / 180.0f); }
	//template<typename T>
	//T toDeg(T rad) { return rad * (180.0f / G_PI); }

	template<typename T>
	struct vec2 {
		byte size;
		T x;
		T y;

		vec2(T x, T y) : x(x), y(y), size(2) {}
		vec2(T x) : x(x), y(x), size(2) {}
		vec2() : vec2(0) {}

		virtual T& operator[](const byte i) {
			auto mem = &x;
			mem += i;
			return *mem;
		}

		virtual const T& operator[](const byte i) const {
			auto mem = &x;
			mem += i;
			return *mem;
		}

		virtual byte getVectorAmount() const { return size; };
		
		A_OPERATION_BODY(vec2, +)
		A_OPERATION_BODY(vec2, -)
		A_OPERATION_BODY(vec2, *)
		A_OPERATION_BODY(vec2, /)

		virtual bool operator==(const vec2<T>& a) {
			for (unsigned int i = 0; i < getVectorAmount(); i++) {
				if (operator[](i) != a[i])
					return false;
			}
			return true;
		}

		virtual bool operator!=(const vec2<T>& a) {
			for (unsigned int i = 0; i < getVectorAmount(); i++) {
				if (operator[](i) != a[i])
					return true;
			}
			return false;
		}

		virtual T* memadd() { return &x; }
	};

	template<typename T>
	struct vec3 : public vec2<T> {
		T z;

		vec3(T x, T y, T z) : vec2<T>(x, y), z(z) {
			this->size = 3;
		}

		vec3(T x) : vec2<T>(x), z(x) {
			this->size = 3;
		}

		A_OPERATION_BODY(vec3, +)
		A_OPERATION_BODY(vec3, -)
		A_OPERATION_BODY(vec3, *)
		A_OPERATION_BODY(vec3, / )

		vec3() : vec3(0) {}
	};

	template<typename T>
	struct vec4 : public vec3<T> {
		T w;

		vec4(T x, T y, T z, T w) : vec3<T>(x, y, z), w(w) {
			this->size = 4;
		}

		vec4(T x) : vec3<T>(x), w(x) {
			this->size = 4;
		}

		A_OPERATION_BODY(vec4, +)
		A_OPERATION_BODY(vec4, -)
		A_OPERATION_BODY(vec4, *)
		A_OPERATION_BODY(vec4, / )

		vec4() : vec4(0) {}
	};


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
		void translate(vec3<V> dir){
			operator[](0)[3] += dir[0];
			operator[](1)[3] += dir[1];
			operator[](2)[3] += dir[2];
		}

		T* memadd() const {
			static T copy[16];
			for (unsigned int i = 0; i < 4; i++) {
				copy[i]      = x[i];
				copy[i + 4]  = y[i];
				copy[i + 8]	 = z[i];
				copy[i + 12] = w[i];
			}
			return &copy[0];
		}
	};

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