#pragma once
#ifndef MIDI_H
#define MIDI_H
#include <iostream>
#include "midi/primitives.h"
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

	void read_mthd(std::istream& in, MTHD* chunk);

	/*------------
	| -- MTRK -- |
	 -----------*/

	// Each event starts with a variable length integer designated the time elapsed since the previous event, followed by a byte that identifies the event. In the case of running status, the status byte can be missing.
	bool is_sysex_event(uint8_t byte);
	bool is_meta_event(uint8_t byte);
	bool is_midi_event(uint8_t byte);
	bool is_running_status(uint8_t byte);


	// MIDI EVENTS 

	// Returns the 4 upper bits of status.
	uint8_t extract_midi_event_type(uint8_t status);
	// Returns the 4 lower bits of status.
	Channel extract_midi_event_channel(uint8_t status);

	// Given the midi event type nibble, check whether it identifies a MIDI event of a specific type.
	bool is_note_off(uint8_t status);
	bool is_note_on(uint8_t status);
	bool is_polyphonic_key_pressure(uint8_t status);
	bool is_control_change(uint8_t status);
	bool is_program_change(uint8_t status);
	bool is_channel_pressure(uint8_t status);
	bool is_pitch_wheel_change(uint8_t status);


	// EVENT RECEIVER

	class EventReceiver
	{
	public:
		virtual void meta(Duration dt, uint8_t type, std::unique_ptr<uint8_t[]> data, uint64_t data_size);
		virtual void sysex(Duration dt, std::unique_ptr<uint8_t[]> data, uint64_t data_size);
		virtual void note_on(Duration dt, Channel channel, NoteNumber note, uint8_t velocity);
		virtual void note_off(Duration dt, Channel channel, NoteNumber note, uint8_t velocity);
		virtual void polyphonic_key_pressure(Duration dt, Channel channel, NoteNumber note, uint8_t pressure);
		virtual void control_change(Duration dt, Channel channel, uint8_t controller, uint8_t value);
		virtual void program_change(Duration dt, Channel channel, Instrument program);
		virtual void channel_pressure(Duration dt, Channel channel, uint8_t pressure);
		virtual void pitch_wheel_change(Duration dt, Channel channel, uint16_t value);
	};

	/*void read_file(Receiver& receiver)
	{
		while (file_not_ended())
		{
			char c = read_next_char();

			switch (c)
			{
			case 'A':
				receiver.process_a();
				break;

			case 'B':
				receiver.process_b();
				break;
			}
		}
	}*/
}
#endif
