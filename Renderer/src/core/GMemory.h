#pragma once
#include <mutex>
#include <atomic>

#ifndef G_MEMORY
#define G_MEMORY
#endif // !G_MEMORY

#ifdef _DEBUG
#define EXTENDED_MEMORYTRACKING
#endif // _DEBUG

#define GET_ALLOC_INFO_COUNT(pointer) reinterpret_cast<unsigned int*>(pointer)[-1]

/**
 * A class whose main purpose is to track memory. It will process all allocation done with the MALLOC/FREE define or with the
 * new/delete operator. Note that every allocation will allocate 4 more bytes than needed to save the size.
 */
class GMemory {
private:
	inline static std::atomic_uint32_t memoryUsage = 0;
	inline static std::atomic_uint32_t allocations = 0, deallocations = 0;
public:
	/**
	 * Will fetch the current Memory usage
	 * @return The amount of memory used in bytes
	 */
	static const size_t getMemory() { return memoryUsage; }

	static const size_t getCurrentAllocationCount() { return allocations - deallocations; }
	static const size_t getAllocation() { return allocations; }
	static const size_t getDeAllocation() { return deallocations; }

#ifndef EXTENDED_MEMORYTRACKING
	/**
	 * @return nullptr
	 */
	static void** getAllocInfo() {
		auto temp = reinterpret_cast<unsigned int*>(malloc(2 * sizeof(unsigned int)));
		temp[0] = 0;
		temp++;
		return (void**)temp;
	}
#endif
	/** This class can be used to check how much memory has been allocated on the heap since construction of this class */
	class MemoryTracker {
		size_t start = getMemory();
		size_t allocations = getAllocation();
	public:
		/**
		 * @return The difference in allocation count since construction of this class
		 */
		const int getAllocationDifference() const { return getCurrentAllocationCount() - allocations; }
		/**
		 * @return The difference in memory usage since construction of this class
		 */
		const int getMemoryDifference() const { return  getMemory() - start; }
	};

#ifdef EXTENDED_MEMORYTRACKING
public:
	/** This struct holds basic information of allocation happening during a program */
	struct AllocInfo {
		/** The memory address */
		void* address;
		/** Amount of bytes allocated */
		size_t size;
		/** The file path to the file in which the allocation happened */
		const char* fileName;
		/** The signature of the function */
		const char* functionSig;
		/** The line in which the allocation happened */
		unsigned int line;

		/**
		 * Will only compare the two memory addresses
		 */
		bool operator==(void* b) { return address == b; }
	};
private:
	struct List {
		AllocInfo* address;
		List* next;
	};
	inline static List* extendedAllocations = nullptr;
	inline static std::mutex globalMutex;

public:

	/**
	 * Will return a pointer array of AllocInfo structs and the amount of pointers. This array hold information of any allocation made with the new operator or the macro TMALLOC (not included). The amount of AllocInfo Pointers can be fetches by reading 4 bytes before of this pointer
	 * or by using the GET_ALLOC_INFO_COUNT macro.
	 * @return An AllocInfo Pointer array
	 */
	static AllocInfo** getAllocInfo() {
		globalMutex.lock();
		auto temp = reinterpret_cast<unsigned int*>(malloc(getCurrentAllocationCount() * sizeof(AllocInfo**) + sizeof(unsigned int)));
		auto add = extendedAllocations;
		temp++;
		auto alloc = reinterpret_cast<AllocInfo**>(temp);

		unsigned int amount = 0;
		while (add != nullptr) {
			alloc[amount] = add->address;
			add = add->next;
			amount++;
		}
		temp[-1] = amount;
		globalMutex.unlock();
		return alloc;
	}

	/**
	 * Override for the new operator
	 */
	static void* alloc(size_t size, const char* file, const char* function, unsigned int line) {
		globalMutex.lock();
		//std::cout << "Allocated " << size << " bytes\n";
		AllocInfo* mem = reinterpret_cast<AllocInfo*>(malloc(size + sizeof(AllocInfo)));
		auto info = mem;
		mem++;
		info[0] = { mem, size, file, function, line };
		if (extendedAllocations == nullptr) {
			extendedAllocations = reinterpret_cast<List*>(malloc(sizeof(List)));
			extendedAllocations->address = info;
			extendedAllocations->next = nullptr;
		}
		else {
			auto temp = extendedAllocations;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = reinterpret_cast<List*>(malloc(sizeof(List)));
			auto last = temp;
			temp = temp->next;
			temp->address = info;
			temp->next = nullptr;
		}
		memoryUsage += size;
		allocations++;
		globalMutex.unlock();
		return reinterpret_cast<void*>(mem);
	}

	/**
	 * Override for the delete operator
	 */
	static void dele(void* p) {
		if (p == nullptr)
			return;
		globalMutex.lock();
		AllocInfo info = (reinterpret_cast<AllocInfo*>(p) - 1)[0];
		//std::cout << "Deleted " << info.size << " bytes\n";
		memoryUsage -= info.size;
		deallocations++;

		auto temp = extendedAllocations;
		auto last = temp;
		while (temp->address->address != p && temp->next != nullptr) {
			last = temp;
			temp = temp->next;
		}
		last->next = temp->next;
		globalMutex.unlock();
		free(reinterpret_cast<void*>((reinterpret_cast<AllocInfo*>(p) - 1)));
	}
#else

public:
	/**
	 * Override for the new operator
	 */
	static void* alloc(size_t size) {
		//std::cout << "Allocated " << size << " bytes\n";
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
		if (p == nullptr)
			return;
		unsigned int size = (reinterpret_cast<unsigned int*>(p) - 1)[0];
		//std::cout << "Deleted " << size << " bytes\n";
		memoryUsage -= size;
		deallocations++;
		auto del = reinterpret_cast<unsigned int*>(p) - 1;
		free((void*)del);
	}
#endif // EXTENDED_MEMORYTRACKING
};

#ifndef EXTENDED_MEMORYTRACKING
inline void* operator new(size_t size) {
	return GMemory::alloc(size);
}
#define TMALLOC(type, size) reinterpret_cast<type>(GMemory::alloc(size))
#else
inline void* operator new(size_t size) {
	return GMemory::alloc(size, "UNKNOWN", "UNKNOWN", 0);
}
inline void* operator new(size_t size, const char* file, const char* function, unsigned int line) {
	return GMemory::alloc(size, file, function, line);
}
inline void operator delete(void* p, const char* file, const char* function, unsigned int line) {
	GMemory::dele(p);
}
#define new new(__FILE__,  __FUNCSIG__, __LINE__)
#define TMALLOC(type, size) reinterpret_cast<type>(GMemory::alloc(size, __FILE__,  __FUNCSIG__, __LINE__))
#endif // !EXTENDED_MEMORYTRACKING

inline void operator delete(void* p) {
	GMemory::dele(p);
}

inline void operator delete[](void* p) {
	GMemory::dele(p);
}