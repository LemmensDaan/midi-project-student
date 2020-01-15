#include "vli.h"
#include "read.h"
#include <stdint.h>
#include <iostream>
#include <cstdint>

// documentation Variable Length Integers
uint64_t io::read_variable_length_integer(std::istream& in) {
	byte b = read<byte>(in);
	int64_t vli = 0;

	vli = (vli << 7) | (b & 0x7f);
	while ((b & 0x80) != 0) {
		b = read<byte>(in);
		vli = (vli << 7) | (b & 0x7f);
	}
	return vli;
}