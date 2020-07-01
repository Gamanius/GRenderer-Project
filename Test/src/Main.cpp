#include "GRenderer.h"

template<typename T>
class ArrayList {
private:
	T* buffer = nullptr;
	size_t size = 0;
public:
	ArrayList(size_t size = 0) {
		this->size = size;
		if (size != 0)
			buffer = TMALLOC(T*, size);
	}

	void add(T obj) {
		auto d = buffer;
		buffer = static_cast<T*>(MALLOC((size + 1) * sizeof(T)));
		if (d != nullptr)
			memcpy(buffer, d, sizeof(T) * size);
		buffer[size] = obj;
		FREE(d, sizeof(T) * size);
		size++;
	}

	size_t getSize() const { return size; }
};

class String {
private:
	size_t size;
	size_t bytesize;
	char* buffer;
	bool precise = false;
public:
	String(const char* c) {
		size = strlen(c);
		buffer = TMALLOC(char*, size + 1);
		memcpy(buffer, c, size + 1);
		bytesize = size + 1;
	}

	String(const String& other) {
		size = other.size;
		buffer = TMALLOC(char*, size + 1);
		memcpy(buffer, other.buffer, size + 1);
		bytesize = size + 1;
	}

	String& append(const char* c) {
		if (bytesize > size + strlen(c) + 1) {
			memcpy(buffer + size, c, strlen(c) + 1);
		}
		else {
			auto temp = buffer;
			auto lastbytesize = bytesize;
			bytesize = size + strlen(c);
			if (!precise)
				bytesize *= 2;
			buffer = TMALLOC(char*, bytesize);

			memcpy(buffer, temp, size);
			memcpy(buffer + size, c, strlen(c) + 1);

			FREE(temp, lastbytesize);
		}
		size += strlen(c);
		return *this;
	}

	void setPrecise(const bool b) { precise = b; }
	//
	//const char* cStr() const { return buffer; }
	//const size_t size() const { return size; }
	//
	//operator const char* () const { return cStr(); }
	//const char operator[] (size_t i) const { return buffer[i]; }

	~String() {
		FREE(buffer, bytesize);
	}
};

int main() {
	GGeneral::Logger::init();

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}