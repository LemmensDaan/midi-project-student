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


	/*------------
	| -- MTHD -- |
	 -----------*/

	#pragma pack(push,1)
	struct MTHD {
		// chunk header				-- 8 bytes
		CHUNK_HEADER header;
		// type of MIDI file		-- 2 bytes
		uint16_t type;
		// number of tracks			-- 2 bytes
		// 0 or 1 (0 = single track, 1 = multiple tracks that form single piece of music)
		uint16_t ntracks;
		// number of units per beat	-- 2 bytes
		uint16_t division;
	};
	#pragma pack(pop)
}
#endif
