#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

#include <st_texture.h>

namespace ST {
	class RenderTarget {
	public:
		RenderTarget(int w, int h);

		~RenderTarget();
	private:
		int width_;
		int height_;

		unsigned int internalID;

		ST::Texture textureToRender_;
		RenderTarget(const RenderTarget& o);
	};
}

#endif