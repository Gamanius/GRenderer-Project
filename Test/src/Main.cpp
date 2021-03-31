#include <GRenderer.h>

const size_t size = 4;
struct Object {
	bool* data = nullptr;

	/** Default Constructor */
	Object() {}

	/**
	 * Copy constructor will only copy the memory address
	 */
	Object(const Object& other) {
		data = other.data;
	}

	/**
	 * Move constructor
	 */
	Object(Object&& other) noexcept {
		data = other.data;

		other.data = nullptr;
	}

	/**
	 * Mover operator. Will dereference the other Object
	 */
	Object& operator=(Object&& other) noexcept {
		data = other.data;

		other.data = nullptr;

		return *this;
	}

	/**
	 * Will copy the memory address
	 */
	Object& operator= (const Object& other) {
		data = other.data;

		return *this;
	}

	bool operator()(const Object& lhs, const Object& rhs) const {
		return memcmp(lhs.data, rhs.data, size) == 0;
	}

	~Object() {
		delete data;
	}
};

template<typename key>
bool compare(const key& a, const key& b) {
	return true;
}

std::map<Object, int, Object> test;


Object a;
Object b;
Object c;

int main() {
	a.data = (bool*)calloc(1, size);
	b.data = (bool*)calloc(1, size);
	c.data = (bool*)calloc(1, size);

	a.data[0] = 1;
	b.data[1] = 1;
	c.data[1] = 1;

	test[a] = 10;
	test[b] = 0;
	
	if(test.find(c) == test.end()) {
		LOG("no");
	} else
		LOG("yes");
}