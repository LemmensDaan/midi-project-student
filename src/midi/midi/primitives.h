#include "util/tagged.h"

namespace midi {
	// Channels
	// new type channel that onbly supports == and !=
	struct __declspec(empty_bases)Channel : tagged<uint8_t, Channel>, equality<Channel>, show_value<Channel, int> {
		using tagged::tagged;
	};
}