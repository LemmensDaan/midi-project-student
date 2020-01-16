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

}
