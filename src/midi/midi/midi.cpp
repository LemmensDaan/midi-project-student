#include "midi.h"
#include <io\read.h>
#include <io\endianness.h>

namespace midi {

	/*-------------
	| CHUNK HEADER |
	 -------------*/

	void midi::read_chunk_header(std::istream& in, CHUNK_HEADER* header)
	{
		io::read_to(in, header);
		io::switch_endianness(&header->size);
	}

	std::string header_id(const CHUNK_HEADER header)
	{
		return std::string(header.id, 4);
	}


	/*------------
	| -- MTHD -- |
	 -----------*/

	void read_mthd(std::istream& in, MTHD* chunk)
	{
		io::read_to(in, chunk);
		io::switch_endianness(&chunk->header.size);
		io::switch_endianness(&chunk->type);
		io::switch_endianness(&chunk->ntracks);
		io::switch_endianness(&chunk->division);

	}

	/*------------
	| -- MTRK -- |
	 -----------*/

	bool is_sysex_event(uint8_t byte)
	{
		return byte == 0xF0 || byte == 0xF7;
	}

	bool is_meta_event(uint8_t byte)
	{
		return  byte == 0xFF;
	}

	bool is_midi_event(uint8_t byte)
	{
		return byte == 0x80 || byte == 0x81 || byte == 0x8F || byte == 0x95 || byte == 0xA3 || byte == 0xB8 || byte == 0xC3 || byte == 0xD1 || byte == 0xE7;
	}

	bool is_running_status(uint8_t byte)
	{
		return (byte & (1 << 7)) == 0;
	}

	uint8_t extract_midi_event_type(uint8_t status)
	{
		return status >> 4;
	}

	Channel extract_midi_event_channel(uint8_t status)
	{
		return Channel(status & 0x0F);
	}

	bool is_note_off(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0x80;
	}

	bool is_note_on(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0x90;
	}

	bool is_polyphonic_key_pressure(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0xA0;
	}

	bool is_control_change(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0xB0;
	}

	bool is_program_change(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0xC0;
	}

	bool is_channel_pressure(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0xD0;;
	}

	bool is_pitch_wheel_change(uint8_t status)
	{
		return (((status & 0xF0) >> 4) | ((status & 0x0F) << 4)) == 0xE0;
	}
}
