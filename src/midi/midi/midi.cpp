#include "midi.h"
#include <io\read.h>
#include <io\endianness.h>
#include "io/vli.h"

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

	// EVENTS

	bool is_sysex_event(uint8_t byte)
	{
		return byte == 0xF0 || byte == 0xF7;
	}

	bool is_meta_event(uint8_t byte)
	{
		return byte == 0xFF;
	}

	bool is_midi_event(uint8_t byte)
	{
		int b = byte & 0xF0;
		return ((b == 0x80) || (b == 0x90) || (b == 0xA0) || (b == 0xB0) || (b == 0xC0) || (b == 0xD0) || (b == 0xE0));
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


	// READ MTRK

	void read_mtrk(std::istream& in, EventReceiver& receiver)
	{
		bool running = true;

		while (running) {
			// read relative timestamp
			Duration dt = Duration(io::read_variable_length_integer(in));
			// read next byte
			uint8_t b = io::read<uint8_t>(in);

			if (is_meta_event(b)) {
				uint8_t type = io::read<uint8_t>(in);
				auto data_size = io::read_variable_length_integer(in);
				std::unique_ptr<byte[]> data = io::read_array<byte>(in, data_size);
				if (type == 0x2F) {
					running = false;
				}

				receiver.meta(dt, type, std::move(data), data_size);
			}

			else if (is_sysex_event(b)) {
				auto data_size = io::read_variable_length_integer(in);
				std::unique_ptr<byte[]> data = io::read_array<byte>(in, data_size);
				receiver.sysex(dt, std::move(data), data_size);
			}


		}
	}
}