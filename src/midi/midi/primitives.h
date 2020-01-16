#include "util/tagged.h"

namespace midi {
	// Channels
	// new type channel that only supports == and !=
	struct __declspec(empty_bases)Channel : tagged<uint8_t, Channel>, equality<Channel>, show_value<Channel, int> {
		using tagged::tagged;
	};

	// Instruments
	// supports == and != and <<
	struct __declspec(empty_bases)Instrument : tagged<uint8_t, Instrument>, equality<Instrument>, show_value<Instrument, int> {
		using tagged::tagged;
	};
}