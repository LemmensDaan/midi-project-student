#ifndef READ_H
#define READ_H
#include <iostream>
#include <logging.h>
namespace io
{
	// read_to<T>(in, buffer, n) reads in n T values from the in. 
	// It does this by reading raw bytes from the istream and reinterpreting these bytes as a n consecutive Ts.
	template <typename T>
	void read_to(std::istream& in, T* buffer, size_t n = 1) {
		for (int i = 0; i < n; i++) {
			T readTo;
			in.read(reinterpret_cast<char*> (&readTo), sizeof(T));
			CHECK(!in.fail()) << "failed";
			buffer[i] = readTo;
		}
	}
}

#endif
