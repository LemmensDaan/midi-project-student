#include "util/tagged.h"

namespace midi {
	// Channels
	// new type channel that onbly supports == and !=
	struct Channel : tagged<uint8_t, Channel>, equality<Channel> {
		using tagged::tagged;
	};
}