#pragma once
#ifndef MIDI_H
#define MIDI_H
#include <iostream>
namespace midi
{
	// Explanation of MTHD / MTRK chunk headers
	// https://github.com/LemmensDaan/midi-project-student/blob/master/docs/background-information/midi.md
	// MTHD chunk comes first -- (description of MIDI file)
	// MTRK chunks after that -- (track)

	/*-------------
	| CHUNK HEADER |
	 -------------*/

	struct CHUNK_HEADER {
		// id is 4 bytes long (type chunk)
		char id[4];
		// size is also 4 bytes long
		uint32_t size;
	};

	void read_chunk_header(std::istream& in, CHUNK_HEADER* header);

	std::string header_id(const CHUNK_HEADER header);
}
#endif
