#include "vli.h"
#include "read.h"
#include <stdint.h>
#include <iostream>
#include <cstdint>

uint64_t io::read_variable_length_integer(std::istream& in) {
	//You can assume that the result will fit in a uint64_t.
	uint64_t vli = 0;
	byte b = read<byte>(in);
	vli += b & 127;
	//This means you need to keep reading bytes as long as the most significant bit is 1.
	while (b > 127) {
		b = read<byte>(in);
		//For each byte that you read, you need to extract the 7 least significant bits and build one large integer with it.
		vli <<= 7;
		vli += b & 127;
	}
	return vli;
}
