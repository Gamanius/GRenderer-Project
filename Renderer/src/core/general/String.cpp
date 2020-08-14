#include "../GRenderer.h"

GGeneral::String::String() {
	size = 0;
	buffer = nullptr;
	bytesize = 0;
}

GGeneral::String::String(const char* c) {
	size = strlen(c);
	buffer = new char[size + 1];//TMALLOC(char*, size + 1);
	memcpy(buffer, c, size + 1);
	bytesize = size + 1;
}

GGeneral::String::String(const unsigned char* c) : String(reinterpret_cast<const char*>(c)) {}

GGeneral::String::String(size_t size) {
	this->size = 0;
	bytesize = size;
	buffer = new char[size + 1];
}

GGeneral::String::String(String&& other) noexcept {
	buffer = other.buffer;
	size = other.size;
	bytesize = other.bytesize;

	other.buffer = nullptr;
	other.size = 0;
	other.bytesize = 0;
}

GGeneral::String::String(const String& other) {
	size = other.size;
	buffer = new char[size + 1];
	memcpy(buffer, other.buffer, size + 1);
	bytesize = size + 1;
}

GGeneral::String& GGeneral::String::append(const char* c) {
	if (bytesize > size + strlen(c) + 1) {
		memcpy(buffer + size, c, strlen(c) + 1);
	}
	else {
		auto temp = buffer;
		auto lastbytesize = bytesize;
		bytesize = size + strlen(c);
		if (!precise)
			bytesize *= 2;
		buffer = new char[bytesize + 1];

		if (temp != nullptr) {
			memcpy(buffer, temp, size);
			delete[] temp;
		}
		memcpy(buffer + size, c, strlen(c) + 1);
	}
	size += strlen(c);
	return *this;
}

GGeneral::String& GGeneral::String::append(GGeneral::BaseObject& obj) { return append(obj.toString()); }

char GGeneral::String::operator[](size_t i) {
	return buffer[i];
}

GGeneral::String& GGeneral::String::operator=(const String& s) {
	buffer = s.buffer;
	size = s.size;
	bytesize = s.bytesize;
	return *this;
}

GGeneral::String& GGeneral::String::operator=(String&& other) noexcept {
	if (other.buffer == buffer)
		return *this;
	delete[] buffer;

	buffer = other.buffer;
	size = other.size;
	bytesize = other.bytesize;

	other.buffer = nullptr;
	other.size = 0;
	other.bytesize = 0;
	return *this;
}

GGeneral::String GGeneral::operator+(const String& s, const String& s2) {
	String returnValue;
	returnValue.append(s).append(s2);
	return returnValue;
}

GGeneral::String GGeneral::operator+(const String& s, const char* c) {
	String returnValue;
	returnValue.append(s).append(c);
	return returnValue;
}

GGeneral::String GGeneral::operator+(const char* c, const String& s) {
	String returnValue;
	returnValue.append(c).append(s);
	return returnValue;
}

GGeneral::String& GGeneral::String::operator+=(const char* c) {
	return this->append(c);
}

GGeneral::String& GGeneral::String::operator<<(const char* c) {
	return this->append(c);
}

GGeneral::String& GGeneral::String::operator<<(const byte* b) {
	return this->append((const char*)b);
}

GGeneral::String& GGeneral::String::operator<<(const String& s) {
	return this->append(s);
}

GGeneral::String& GGeneral::String::operator<<(const BaseObject& obj) {
	return this->append(obj.toString());
}

#define FORMAT(format, varname)\
size_t size = _scprintf(format, varname) + 1;\
char* c = new char[size];/*TMALLOC(char*, size);*/\
snprintf(c, size, format, varname);\
this->append(c);\
delete[] c;\
return *this;

GGeneral::String& GGeneral::String::operator<<(const void* adress) {
	FORMAT("%p", adress);
}

GGeneral::String& GGeneral::String::operator<<(const byte b) {
	return this->operator<<((int)b);
}

GGeneral::String& GGeneral::String::operator<<(const int i) {
	size_t size = _scprintf("%i", i);
	char* c = new char[size + 1];//TMALLOC(char*, size + 1);
	snprintf(c, size + 1, "%i", i);
	this->append(c);
	delete[] c;
	return *this;
}

GGeneral::String& GGeneral::String::operator<<(uint64_t ui64) {
	FORMAT("%I64u", ui64);
}

GGeneral::String& GGeneral::String::operator<<(uint32_t ui32) {
	FORMAT("%u", ui32);
}

GGeneral::String& GGeneral::String::operator<<(uint16_t ui16) {
	FORMAT("%u", ui16);
}

GGeneral::String& GGeneral::String::operator<<(long l) {
	FORMAT("%i", l);
}

GGeneral::String& GGeneral::String::operator<<(unsigned long ul) {
	FORMAT("%u", ul);
}

GGeneral::String& GGeneral::String::operator<<(double d) {
	FORMAT("%f", d);
}

void GGeneral::String::setPrecise(const bool b) { precise = b; }

size_t GGeneral::String::find(const char* c) {
	bool found = false;
	int ssize = size;
	int csize = strlen(c);
	int dif = ssize - csize;
	if (dif < 0)
		return GGeneral::String::npos;
	for (size_t i = 0; i < size - strlen(c) + 1; i++) {
		for (size_t j = 0; j < strlen(c); j++) {
			if (buffer[i + j] != c[j]) {
				found = false;
				break;
			}
			else
				found = true;
		}
		if (found)
			return i;
	}
	return GGeneral::String::npos;
}

bool GGeneral::String::compare(const char* c) {
	if (strlen(c) != size)
		return false;
	return memcmp(c, buffer, size /*leaving the \0 out*/) == 0;
}

GGeneral::String& GGeneral::String::erase(size_t begining, size_t offset) {
	auto temp = buffer;
	buffer = new char[bytesize];//TMALLOC(char*, bytesize);
	if (begining > 0)
		memcpy(buffer, temp, begining);
	memcpy(buffer + begining, temp + offset + begining + 1, (size - (offset + begining)) + 1);
	size -= offset + 1;
	delete[]temp;// (temp, bytesize);
	return *this;
}

const char* GGeneral::String::cStr() const { return buffer; }
const size_t GGeneral::String::getSize() const { return size; }

GGeneral::String::operator const char* () const { return buffer; }
const char GGeneral::String::operator[](size_t i) const { return buffer[i]; }

GGeneral::String::~String() {
	if (bytesize > 0 && buffer != nullptr)
		delete[] buffer;
	//FREE(buffer, bytesize);
}