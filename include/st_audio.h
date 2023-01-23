#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

//#define MINIAUDIO_IMPLEMENTATION
//#include <miniaudio.h>

namespace ST {
	class Audio {
	public:
		Audio();

		~Audio();
	private:

		Audio(const Audio& o);
	};
}

#endif