//#include "GRenderer.h"
#include <iostream>

//#define EXTENDED_MEMORYTRACKING
class Memory {
private:
	inline static size_t memoryUsage = 0;
	inline static size_t allocations = 0, deallocations = 0;
#ifndef EXTENDED_MEMORYTRACKING
public:
	/**
	 * Override for the new operator
	 */
	static void* alloc(size_t size) {
		std::cout << "Allocated " << size << " bytes\n";
		memoryUsage += size;
		allocations++;
		unsigned int* mem = reinterpret_cast<unsigned int*>(malloc(size + 4));
		mem[0] = size;
		mem++;
		return (void*)mem;
	}

	/**
	 * Override for the delete operator
	 */
	static void dele(void* p) {
		unsigned int size = (reinterpret_cast<unsigned int*>(p) - 1)[0];
		std::cout << "Deleted " << size << " bytes\n";
		memoryUsage -= size;
		deallocations++;
		auto del = reinterpret_cast<unsigned int*>(p) - 1;
		free((void*)del);
	}
#else
public:
	struct AlloInfo {
		void* address;
		size_t size;
		const char* fileName;
		const char* functionSig;
		unsigned int line;
	};
private:
	inline static AlloInfo* extendedAllocations = nullptr;
	static void add(void* address, size_t size, const char* file, const char* function, unsigned int line) {
		auto allocaters = allocations - deallocations;
		if (allocaters > 0 && extendedAllocations != nullptr) {
			auto temp = extendedAllocations;
			extendedAllocations = reinterpret_cast<AlloInfo*>(malloc((sizeof(AlloInfo) * allocaters) + 1));
			memcpy(extendedAllocations, temp, (sizeof(AlloInfo) * allocaters) + 1);
			extendedAllocations[allocaters] = { address, size, file, function, line };
		}
		else {
			extendedAllocations = reinterpret_cast<AlloInfo*>(malloc(sizeof(AlloInfo)));
			extendedAllocations[0] = { address, size, file, function, line };
		}
	}
public:
	/**
	 * Override for the new operator
	 */
	static void* alloc(size_t size, const char* file, const char* function, unsigned int line) {
		std::cout << "Allocated " << size << " bytes\n";
		unsigned int* mem = reinterpret_cast<unsigned int*>(malloc(size + 4));
		mem[0] = size;
		mem++;
		add(mem, size, file, function, line);
		memoryUsage += size;
		allocations++;
		return (void*)mem;
	}

	/**
	 * Override for the delete operator
	 */
	static void dele(void* p) {
		unsigned int size = (reinterpret_cast<unsigned int*>(p) - 1)[0];
		std::cout << "Deleted " << size << " bytes\n";
		memoryUsage -= size;
		deallocations++;
		auto del = reinterpret_cast<unsigned int*>(p) - 1;
		free((void*)del);
	}

	static const AlloInfo* const getAllAllocations() { return extendedAllocations; }
#endif
};

#ifndef EXTENDED_MEMORYTRACKING
void* operator new(size_t size) {
	return Memory::alloc(size);
}
#else
void* operator new(size_t size, const char* file, const char* function, unsigned int line) {
	return Memory::alloc(size, file, function, line);
}
#define new new(__FILE__,  __FUNCSIG__, __LINE__)
#endif // !EXTENDED_MEMORYTRACKING

void operator delete(void* p) {
	Memory::dele(p);
}

int main() {
	auto i = new int[1000];
	//const Memory::AlloInfo* a = Memory::getAllAllocations();
	//std::cout << a[0].address;
	delete[] i;
}