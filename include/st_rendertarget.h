#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

#include <st_texture.h>
#include <memory>


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
			ST::Texture::Format f = ST::Texture::Format::F_RGBA,
			ST::Texture::DataType dt = ST::Texture::DT_U_BYTE,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);

		GLuint getID();
		GLuint textureID();

		RenderType renderType_;

		void start();
		void end();

		std::shared_ptr<ST::Texture> textureToRender_;

		RenderTarget(const RenderTarget& o);
		~RenderTarget();
	private:
		int width_;
		int height_;

		GLint last_viewport[4];

		GLuint internalID;
		unsigned int rbo;

	};
}

#endif