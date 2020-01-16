#include "util/tagged.h"

namespace midi {
	// Operators for time and duration
	template<typename Result, typename L, typename R>
	struct add {
		friend Result operator +(const L& x, const R& y) {
			return Result(value(x) + value(y));
		}
	};

	template<typename Result, typename L, typename R>
	struct sub {
		friend Result operator -(const L& x, const R& y) {
			return Result(value(x) - value(y));
		}
	};

	template<typename L, typename R>
	struct assignment_add {
		friend L& operator +=(L& x, const R& y) {
			x = x + y;
			return x;
		}
	};

	template<typename L, typename R>
	struct assignment_sub {
		friend L& operator -=(L& x, const R& y) {
			x = x - y;
			return x;
		}
	};
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

	// Declare Duration for Time
	struct __declspec(empty_bases)Duration;

	// Time: represents an absolute moment in time.
	// Apart from these + and - operators, this also supports ==, !=, <, >, <=, >= and <<.
	struct __declspec(empty_bases)Time : tagged<uint64_t, Time>, ordered<Time>, show_value<Time, int>,
		add<Time, Time, Duration>,
		add<Time, Duration, Time>,
		sub<Duration, Time, Time>,
		assignment_add<Time, Duration> {
			using tagged::tagged;
	};

	// Duration: represents the difference between two Times.
	struct __declspec(empty_bases)Duration : tagged<uint64_t, Duration>, ordered<Duration>, show_value<Duration, int>,
		add<Duration, Duration, Duration>,
		sub<Duration, Time, Time>,
		sub<Duration, Duration, Duration>,
		assignment_add<Duration, Duration>,
		assignment_sub<Duration, Duration> {
			using tagged::tagged;
	};






}