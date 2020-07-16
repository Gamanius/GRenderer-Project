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
	/**
	 * This structure hold information of a vector.
	 */
	template<typename T, size_t size>
	struct vec {
	private:
		T* data = nullptr;
	public:

		/**
		 * Constructor for the vector. Will set all values to 0
		 */
		vec() {
			data = new T[size];
			memset(data, 0, sizeof(T) * size);
		}

		/**
		 * Will construct the vector and set all values to the given value
		 * @param value - The value of the vector
		 */
		vec(T value) {
			data = new T[size];
			for (size_t i = 0; i < size; i++) {
				data[i] = value;
			}
		}

		/**
		 * Will copy the contents of another vector
		 * @param other - The vector to copy
		 */
		vec(const vec<T, size>& other) {
			data = new T[size];
			memcpy(data, other.data, sizeof(T) * size);
		}

		/**
		 * Will move the vector
		 * @param other - The other vector
		 */
		vec(vec<T, size>&& other) {
			data = other.data;
			other.data = nullptr;
		}

		/** Destructor */
		~vec() { delete[] data; }

		/**
		 * @return A memory address of the data
		 */
		const T* const mem() const { return data; }

		/**
		 * Will perform normal vector to vector addition
		 * @param other - The other vector to add
		 * @return A new vector
		 */
		template<typename V>
		vec<T, size> operator+(const vec<V, size>& other) {
			auto cpy = vec(*this);
			for (size_t i = 0; i < size; i++) {
				cpy[i] += other[i];
			}
			return cpy;
		}

		/**
		 * Will perform normal vector to vector addition
		 * @param other - The other vector
		 * @return This vector
		 */
		template<typename V>
		vec<T, size> operator+=(const vec<V, size>& other) {
			for (size_t i = 0; i < size; i++) {
				data[i] += other[i];
			}
			return *this;
		}

		/**
		 * Will return a reference to the value of the index
		 * @param i - The index
		 * @return The value at this place
		 */
		T& operator[](size_t i) const {
			return data[i];
		}

		/**
		 * @return The size of the vector
		 */
		const size_t getSize() const { return size; }
	};

	/** Vector with 2 elements */
	template<typename T>
	using vec2 = vec<T, 2>;
	/** Vector with 3 elements */
	template<typename T>
	using vec3 = vec<T, 3>;
	/** Vector with 4 elements */
	template<typename T>
	using vec4 = vec<T, 4>;

	/** This struct hold the information of a matrix. All matrices are column major */
	template<typename T, size_t row, size_t column>
	struct mat {
	private:
		/** Data */
		T* data = nullptr;//  new T[row * column];
	public:

		/** Will create a Matrix.*/
		mat() {
			data = new T[row * column];
			memset(data, 0, sizeof(T) * row * column);
		}

		/**
		 * Will create a Matrix
		 * @param value - The value the matrix should hold
		 */
		mat(T value) {
			data = new T[row * column];
			memset(data, value, sizeof(T) * row * column);
		}

		/**
		 * Will copy the other matrix
		 * @param other - The other matrix to copy
		 */
		mat(const mat<T, row, column>& other) {
			data = new T[row * column];
			memcpy(data, other.data, sizeof(T) * row * column);
		}

		/**
		 * Will move the matrix
		 * @param other - The other matrix to move
		 */
		mat(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
		}

		/**
		 * Will copy the matrix
		 * @param other - The other matrix to copy
		 * @return This matrix
		 */
		mat& operator=(const mat<T, row, column>& other) {
			data = other.data;
			return *this;
		}

		/**
		 * Will move the matrix
		 * @param other - The other matrix to move
		 * @return This matrix
		 */
		mat& operator=(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
			return *this;
		}

		/** Destructor */
		~mat() { delete[] data; }

		/**
		 * @return The memory address of the first element
		 */
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

	/** definition of a 2x2 Matrix */
	USE_MAT(2);
	/** definition of a 3x3 Matrix */
	USE_MAT(3);
	/** definition of a 4x4 Matrix */
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