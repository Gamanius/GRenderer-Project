#pragma once

namespace GMath {
	template<typename T>
	struct vec2 {
		T x;
		T y;
	};

	template<typename T>
	struct vec3 : public vec2<T> {
		T z;
	};

	template<typename T>
	struct vec4 : public vec3<T> {
		T w;
	};
}