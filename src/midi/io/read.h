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
			T read;
			in.read(reinterpret_cast<char*> (&read), sizeof(T));
			CHECK(!in.fail()) << "failed";
			buffer[i] = read;
		}
	}

	// read a single T from in and return it
	// more user - friendly version of read_to for reading a single value
	template<typename T, typename std::enable_if<std::is_fundamental<T>::value, T>::type* = nullptr>
	T read(std::istream& in) {
		T read;
		io::read_to(in, &read);
		return read;
	}

	// more user - friendly version of read_to for reading multiple values
	// returning an array
	template<typename T>
	std::unique_ptr<T[]> read_array(std::istream& in, size_t n = 1) {
		std::unique_ptr<T[]> pointer = std::make_unique<T[]>(n);
		for (int i = 0; i < n; i++) {
			T read;
			in.read(reinterpret_cast<char*> (&read), sizeof(T));
			pointer[i] = read;
		}
		return pointer;
	}

}

#endif
