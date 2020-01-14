#pragma once
#include <stdint.h>
#include <algorithm>
#include "endianness.h"

void io::switch_endianness(uint16_t* n) {
	uint16_t mirror = (*n >> 8) | (*n << 8);
	*n = mirror;
}
void io::switch_endianness(uint32_t* n) {
	uint32_t  mirror = ((*n >> 24)) |
		((*n << 8) & 0xff0000) |
		((*n >> 8) & 0xff00) |
		((*n << 24) & 0xff000000);
	*n = mirror;
}
void io::switch_endianness(uint64_t* n) {
	uint64_t m1 = (*n >> 32);
	uint64_t mirror_m1 = ((m1 >> 24)) |
		((m1 << 8) & 0xff0000) |
		((m1 >> 8) & 0xff00) |
		((m1 << 24) & 0xff000000);
	uint64_t m2 = (*n << 32);
	uint64_t m2a = (m2 >> 32);

	uint64_t mirror_m2a = ((m2a >> 24)) |
		((m2a << 8) & 0xff0000) |
		((m2a >> 8) & 0xff00) |
		((m2a << 24) & 0xff000000);
	*n = (mirror_m2a << 32) | mirror_m1;
}