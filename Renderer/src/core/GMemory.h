#pragma once
#include <iostream>

#ifndef G_MEMORY
#define G_MEMORY
#endif // !G_MEMORY

class GMemory {
private:
	inline static size_t allocated = 0;
	size_t allocatedStart = 0;
public:
	/**
	 * Override for the new operator
	 */
	static void* alloc(size_t size) {
		std::cout << "Allocated " << size << " bytes\n";
		allocated += size;
		return malloc(size);
	}

	/**
	 * Override for the delete operator
	 */
	static void dele(void* p, size_t size) {
		std::cout << "Deleted " << size << " bytes\n";
		allocated -= size;
		free(p);
	}

	/**
	 * Will fetch the current Memory usage
	 * @return The amount of memory used in bytes
	 */
	static const size_t getMemory() { return allocated; }

	/**
	 * Will return the amount of bytes that has been allocated in bytes since construction of this class
	 * @return Amount of memory in bytes
	 */
	const long stop() const {
		return getMemory() - allocatedStart;
	}

	/**
	 * Will return the amount of bytes that has been allocated in bytes since construction of this class and reset the starting values to 0
	 * @return Amount of memory in bytes
	 */
	const long reset() {
		auto m = stop();
		allocatedStart = 0;
		return m;
	}
};

inline void* operator new(size_t size) {
	return GMemory::alloc(size);
}

inline void operator delete(void* p, size_t size) {
	GMemory::dele(p, size);
}

inline void operator delete[](void* p, size_t size) {
	GMemory::dele(p, size);
}