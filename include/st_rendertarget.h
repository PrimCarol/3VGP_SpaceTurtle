#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

#include <st_texture.h>



namespace ST {
	class RenderTarget {
	public:

		enum RenderType {
			RT_Color,
			RT_Depth,
			RT_Stencil
		};

		RenderTarget();
		void setUp(int w, int h,
				   ST::Texture::TextType t = ST::Texture::TextType::T_2D,
				   ST::Texture::DataType dt = ST::Texture::DT_U_BYTE,
				   ST::Texture::Format f = ST::Texture::Format::F_RGBA);

		GLuint getID();
		GLuint textureID();

		RenderType renderType_;

		void start();
		void end();

		ST::Texture textureToRender_;
		~RenderTarget();
	private:
		int width_;
		int height_;

		GLuint internalID;
		unsigned int rbo;

		RenderTarget(const RenderTarget& o);
	};
}

#endif