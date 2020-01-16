#pragma once
#ifndef MIDI_H
#define MIDI_H
#include <iostream>
namespace midi
{

	/*-------------
	| CHUNK HEADER |
	 -------------*/

	struct CHUNK_HEADER {
		char id[4];
		uint32_t size;
	};
}
#endif
