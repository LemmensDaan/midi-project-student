#include "util/tagged.h"

namespace midi {
	// Channels
	// new type channel that only supports == and !=, (also << after channel show)
	struct __declspec(empty_bases)Channel : tagged<uint8_t, Channel>, equality<Channel>, show_value<Channel, int> {
		using tagged::tagged;
	};

	// Instruments
	// new type of instrument that supports ==, != and <<
	struct __declspec(empty_bases)Instrument : tagged<uint8_t, Instrument>, equality<Instrument>, show_value<Instrument, int> {
		using tagged::tagged;
	};

	// Note numbers
	// new type of note numbers that supports ==, !=, <, >, <=, >=, <<
	struct __declspec(empty_bases)NoteNumber : tagged<uint8_t, NoteNumber>, ordered<NoteNumber>, show_value<NoteNumber, int> {
		using tagged::tagged;
	};
}