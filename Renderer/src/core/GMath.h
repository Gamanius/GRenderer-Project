#pragma once

#ifndef G_MATH
#define G_MATH
#endif // !G_MATH

#include "Defines.h"
#include "GMemory.h"
#include <cmath>

/*! Just a typedef so the code is better to read */
typedef unsigned char byte;
/**
 * This namespace includes the most important OpenGL math functions needed. It can be also used outside the engine and/or without OpenGL.
 * The Renderer doesn't need to be initialized to use the functions
 */
namespace GMath {
	template<typename T, size_t size>
	struct vec {
	private:
		T* data = nullptr;
	public:

		vec() {
			data = new T[size];
			memset(data, 0, sizeof(T) * size);
		}

		vec(T value) {
			data = new T[size];
			for (size_t i = 0; i < size; i++) {
				data[i] = value;
			}
		}

		vec(const vec<T, size>& other) {
			data = new T[size];
			memcpy(data, other.data, sizeof(T) * size);
		}

		vec(vec<T, size>&& other) {
			data = other.data;
			other.data = nullptr;
		}

		~vec() { delete[] data; }

		const T* const mem() const { return data; }

		template<typename V>
		vec<T, size> operator+(const vec<V, size>& other) {
			auto cpy = vec(*this);
			for (size_t i = 0; i < size; i++) {
				cpy[i] += other[i];
			}
			return cpy;
		}

		template<typename V>
		vec<T, size> operator+=(const vec<V, size>& other) {
			for (size_t i = 0; i < size; i++) {
				data[i] += other[i];
			}
			return *this;
		}

		T& operator[](size_t i) const {
			return data[i];
		}

		const size_t getSize() const { return size; }
	};

	template<typename T>
	using vec2 = vec<T, 2>;
	template<typename T>
	using vec3 = vec<T, 3>;
	template<typename T>
	using vec4 = vec<T, 4>;

	template<typename T, size_t row, size_t column>
	struct mat {
	private:
		/** Data */
		T* data = nullptr;//  new T[row * column];
	public:

		/** Will create a 2x2 Matrix.*/
		mat() {
			data = new T[row * column];
			memset(data, 0, sizeof(T) * row * column);
		}

		/**
		 * Will create a 2x2 Matrix
		 * @param value - The value the matrix should hold
		 */
		mat(T value) {
			data = new T[row * column];
			memset(data, value, sizeof(T) * row * column);
		}

		mat(const mat<T, row, column>& other) {
			data = new T[row * column];
			memcpy(data, other.data, sizeof(T) * row * column);
		}

		mat(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
		}

		mat& operator=(const mat<T, row, column>& other) {
			data = other.data;
			return *this;
		}

		mat& operator=(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
			return *this;
		}

		/** Destructor */
		~mat() { delete[] data; }

		const T* const mem() const { return data; }

		T* operator[](size_t i) {
			return &data[i * row];
		}
	};

#define USE_MAT(n)\
	template<typename T>\
	using mat##n##x##n = mat<T, n, n>;\
	template<typename T>\
	using mat##n = mat##n##x##n <T>;

	USE_MAT(2);
	USE_MAT(3);
	USE_MAT(4);

#undef USE_MAT

	/**
	 * Creates a new Identity Matrix 4x4
	 * @return a mat4x4
	 */
	template<typename T>
	mat4<T> mat4x4Identity() {
		mat4<T> returnValue;
		returnValue[0][0] = 1;
		returnValue[1][1] = 1;
		returnValue[2][2] = 1;
		returnValue[3][3] = 1;
		return returnValue;
	}

	template<typename T, size_t S>
	mat<T, S, S> matIdentity() {
		mat<T, S, S> returnValue;
		for (size_t i = 0; i < S; i++) {
			returnValue[i][i] = 1;
		}
		return returnValue;
	}

	/**
	 * Will create an orthographic projection matrix and return it
	 * @param left - Left coordinate of the frustum
	 * @param right - Right coordinate of the frustum
	 * @param bottom - Bottom coordinate of the frustum
	 * @param top - Top coordinate of the frustum
	 * @param _near - The near plane frustum
	 * @param _far - The far plane frustum
	 * @return An mat4x4
	 */
	template<typename T>
	mat4<T> ortho(T left, T right, T bottom, T top, T _near, T _far) {
		auto returnValue = mat4x4Identity<T>();
		returnValue[0][0] = 2 / (right - left);
		returnValue[1][1] = 2 / (top - bottom);
		returnValue[2][2] = -(2 / (_far - _near));
		returnValue[0][3] = -((right + left) / (right - left));
		returnValue[1][3] = -((top + bottom) / (top - bottom));
		returnValue[2][3] = -((_far + _near) / (_far - _near));
		return returnValue;
	}

	/**
	 * Will create an perspective projection matrix and return it
	 * @param FOV - The field of view in degrees
	 * @param aspect - The aspect ratio
	 * @param _near - Specifies the near plane frustum
	 * @param _far - Specifies the far plane frustum
	 * @return An mat4x4
	 */
	template<typename T>
	mat4<T> perpective(float FOV, T aspect, T _near, T _far) {
		mat4<T> returnValue;
		returnValue[0][0] = 1 / (aspect * tan(TO_RAD(FOV) / 2));
		returnValue[1][1] = 1 / (tan(TO_RAD(FOV) / 2));
		returnValue[2][2] = -((_far + _near) / (_far - _near));
		returnValue[3][2] = -1;
		returnValue[2][3] = -((2 * _far * _near) / (_far - _near));
		return returnValue;
	}
}

#undef A_OPERATION
#undef A_OPERATION_BODY