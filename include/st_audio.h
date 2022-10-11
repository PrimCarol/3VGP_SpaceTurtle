#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace ST {


	// ************* Test *************
	//ma_engine engine;
	//ma_engine_init(nullptr, &engine);
	//ma_sound sound;

	//auto result =
	//	ma_sound_init_from_file(&engine, "../others/pepe.wav",
	//		MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_NO_PITCH |
	//		MA_SOUND_FLAG_NO_SPATIALIZATION,
	//		nullptr, nullptr, &sound);
	//if (result != MA_SUCCESS) return result;

	//ma_sound_start(&sound);

	//while (!ma_sound_at_end(&sound)) {
	//	// Nothing
	//}

	//ma_sound_uninit(&sound);
	//ma_engine_uninit(&engine);

	// ************* Test *************

	class Audio {
	public:

		Audio();
		//std::weak_ptr<Sound> playSound(std:)



		~Audio();
	private:

		//std::unordered_map<std : string, ma_codec> m_sampleMap;
		//std::vector<std::shared_ptr<Sound>> m_playingSound;


		Audio(const Audio& o);
	};
}

#endif